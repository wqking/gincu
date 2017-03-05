#include "gincu/gheappool.h"
#include "gincu/glog.h"

#include <algorithm>
#include <cassert>
#include <thread>

#ifndef GINCU_MEMORY_POOL_ALIGNMENT
#define GINCU_MEMORY_POOL_ALIGNMENT 64
#endif

#ifndef GINCU_MEMORY_POOL_BLOCK_COUNT_PER_TRUNK
#define GINCU_MEMORY_POOL_BLOCK_COUNT_PER_TRUNK 256
#endif

#ifndef GINCU_MEMORY_POOL_PURGE_STRATEGY
#define GINCU_MEMORY_POOL_PURGE_STRATEGY onSceneSwitched
#endif

namespace gincu {

constexpr std::size_t memoryPoolAlignment = GINCU_MEMORY_POOL_ALIGNMENT;
constexpr std::size_t memoryPoolBlockCountPerTrunk = GINCU_MEMORY_POOL_BLOCK_COUNT_PER_TRUNK;
constexpr GHeapPoolPurgeStrategy memoryPoolPurgeStrategy = GHeapPoolPurgeStrategy:: GINCU_MEMORY_POOL_PURGE_STRATEGY ;

namespace {

#pragma pack(push, 1)
struct BlockHeader
{
	std::size_t size;
};

struct ChunkHeader
{
	int usedCount;
	BlockHeader firstHeader; // must be last field.
};
#pragma pack(pop)


std::size_t alignSize(const std::size_t size, const std::size_t alignment, const std::size_t extraHead)
{
	return (size + extraHead + alignment - 1) & ~(alignment - 1);
}

void * alignPointer(void * p, const std::size_t alignment, const std::size_t extraHead)
{
	return (void *)(alignSize((std::size_t)p, alignment, extraHead));
}

BlockHeader * getBlockHeader(void * p)
{
	return (BlockHeader *)p - 1;
}

const BlockHeader * getBlockHeader(const void * p)
{
	return (BlockHeader *)p - 1;
}

void * setSize(void * p, const std::size_t size)
{
	getBlockHeader(p)->size = size;
	return p;
}

std::size_t getSize(const void * p)
{
	return getBlockHeader(p)->size;
}

void * getRawPointer(void * p)
{
	return p;
}

ChunkHeader * getChunkHeader(void * p)
{
	return (ChunkHeader *)p - 1;
}

std::thread::id createdThreadId;

} //unnamed namespace

GHeapSizedPool::GHeapSizedPool(
		const std::size_t blockSize,
		const std::size_t alignment,
		const std::size_t blockCountPerChunk,
		const GHeapPoolPurgeStrategy purgeStrategy
	)
	:
		blockSize(blockSize),
		blockTotalSize(alignSize(blockSize, alignment, sizeof(BlockHeader))),
		alignment(alignment),
		blockCountPerChunk(blockCountPerChunk),
		chunkSize(alignSize(blockTotalSize * blockCountPerChunk, alignment, sizeof(ChunkHeader))),
		purgeStrategy(purgeStrategy)
{
}

void * GHeapSizedPool::allocate()
{
	return this->allocate(this->blockSize);
}

void * GHeapSizedPool::allocate(const std::size_t size)
{
	assert(size <= this->blockSize);

	if(this->idleList.empty()) {
		const int chunkIndex = (int)this->chunkList.size();
		char * newChunk = (char *)malloc(this->chunkSize);
		this->chunkList.push_back(Chunk{
			std::unique_ptr<char>(newChunk),
			(char *)alignPointer(newChunk, this->alignment, sizeof(ChunkHeader))
		});
		this->chunkMap.insert(std::make_pair(ChunkRange{ this->chunkList.back().start, (char *)this->chunkList.back().start + this->chunkSize }, (int)this->chunkList.size() - 1));

		for(int i = 1; i < (int)this->blockCountPerChunk; ++i) {
			this->idleList.push_back({ chunkIndex, i });
		}
		
		void * chunk = this->chunkList.back().start;
		ChunkHeader * chunkHeader = getChunkHeader(chunk);
		chunkHeader->usedCount = 1;

//		G_LOG_DEBUG("Allocate new chunk: %p %p %u %u %p", chunk, (void *)this->chunkList.back().rawMemory.get(), size, this->blockTotalSize, this);

		return setSize(chunk, size);
	}
	else {
		const IdleIndex idleIndex = this->idleList.back();
		this->idleList.pop_back();

		void * chunk = this->chunkList[idleIndex.chunkIndex].start;
		ChunkHeader * chunkHeader = getChunkHeader(chunk);
		++chunkHeader->usedCount;
		return setSize((char *)chunk + idleIndex.blockIndex * this->blockTotalSize, size);
	}
}

void GHeapSizedPool::free(void * p)
{
	void * rawPointer = getRawPointer(p);

	auto it = this->chunkMap.find(ChunkRange(rawPointer));
	if(it != this->chunkMap.end()) {
		char * chunk = (char *)this->chunkList[it->second].start;
		const int blockIndex = ((char *)rawPointer - chunk) / this->blockTotalSize;
		this->idleList.push_back({it->second, blockIndex});

		ChunkHeader * chunkHeader = getChunkHeader(chunk);
		--chunkHeader->usedCount;

		if(chunkHeader->usedCount == 0 && this->purgeStrategy == GHeapPoolPurgeStrategy::onFree) {
			this->doPurgeChunk(it->second);
		}

	}
	else {
		G_LOG_ERROR("GHeapSizedPool: Can't find chunk.");
	}
return;

	for(int i = 0; i < (int)this->chunkList.size(); ++i) {
		char * chunk = (char *)this->chunkList[i].start;
		if(chunk <= rawPointer && rawPointer < chunk + this->chunkSize) {
			const int blockIndex = ((char *)rawPointer - chunk) / this->blockTotalSize;
			this->idleList.push_back({i, blockIndex});

			ChunkHeader * chunkHeader = getChunkHeader(chunk);
			--chunkHeader->usedCount;
			
			if(chunkHeader->usedCount == 0 && this->purgeStrategy == GHeapPoolPurgeStrategy::onFree) {
				this->doPurgeChunk(i);
			}

			break;
		}
	}
}

void GHeapSizedPool::purge()
{
	for(int i = (int)this->chunkList.size() - 1; i >= 0; --i) {
		char * chunk = (char *)this->chunkList[i].start;
		ChunkHeader * chunkHeader = getChunkHeader(chunk);
		if(chunkHeader->usedCount == 0) {
			this->doPurgeChunk(i);
		}
	}
}

void GHeapSizedPool::doPurgeChunk(const int index)
{
	for(auto it = this->idleList.begin(); it != this->idleList.end(); ) {
		if(it->chunkIndex == index) {
			it = this->idleList.erase(it);
		}
		else {
			if(it->chunkIndex > index) {
				--it->chunkIndex;
			}
			++it;
		}
	}

	auto itToErase = this->chunkMap.end();
	for(auto & it = this->chunkMap.begin(); it != this->chunkMap.end(); ++it) {
		if(it->second == index) {
			itToErase = it;
		}
		else {
			if(it->second > index) {
				--it->second;
			}
		}
	}
	if(itToErase != this->chunkMap.end()) {
		this->chunkMap.erase(itToErase);
	}

//	G_LOG_DEBUG("Purged one chunk %d %p %d remain: %d", index, this->chunkList[index].start, this->blockTotalSize, this->chunkList.size() - 1);

	this->chunkList.erase(this->chunkList.begin() + index);
}


GHeapPool * GHeapPool::getInstance()
{
	static GHeapPool instance(memoryPoolAlignment, memoryPoolBlockCountPerTrunk, memoryPoolPurgeStrategy);
	
	return &instance;
}

GHeapPool::GHeapPool(
		const std::size_t alignment,
		const std::size_t blockCountPerChunk,
		const GHeapPoolPurgeStrategy purgeStrategy
	)
	:
		alignment(alignment),
		blockCountPerChunk(blockCountPerChunk),
		purgeStrategy(purgeStrategy)
{
	createdThreadId = std::this_thread::get_id();
}

GHeapPool::~GHeapPool()
{
}

void * GHeapPool::allocate(const std::size_t size)
{
	G_LOG_IF(createdThreadId != std::this_thread::get_id(), G_LOG_FATAL("GHeapPool allocate in wrong thread!!!"));
//return malloc(size);

	GHeapSizedPool * pool = nullptr;

	const std::size_t alignedSize = alignSize(size, this->alignment, 0);

	auto it = this->poolMap.find(alignedSize);
	if(it != this->poolMap.end()) {
		pool = it->second.get();
	}
	else {
		pool = new GHeapSizedPool(alignedSize, this->alignment, this->blockCountPerChunk, this->purgeStrategy);
		this->poolMap.insert(std::make_pair(alignedSize, std::unique_ptr<GHeapSizedPool>(pool)));
	}
	
	return pool->allocate(size);
}

void GHeapPool::free(void * p)
{
	G_LOG_IF(createdThreadId != std::this_thread::get_id(), G_LOG_FATAL("GHeapPool free in wrong thread!!!"));
//free(p); return;

	const std::size_t size = getSize(p);
	const std::size_t alignedSize = alignSize(size, this->alignment, 0);
	
	auto it = this->poolMap.find(alignedSize);
	if(it != this->poolMap.end()) {
		it->second->free(p);
	}
	else {
		G_LOG_FATAL("ERROR: can't find memory pool to free buffer.");
	}
}

void GHeapPool::purge()
{
	for(auto it = this->poolMap.begin(); it != this->poolMap.end(); ++it) {
		it->second->purge();
	}
}


} //namespace gincu

