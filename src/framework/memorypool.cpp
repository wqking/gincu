#include "framework/memorypool.h"
#include "framework/configure.h"

#include <algorithm>
#include <cassert>
#include <iostream>

namespace gincu {

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


} //unnamed namespace

MemorySizedPool::MemorySizedPool(
		const std::size_t blockSize,
		const std::size_t alignment,
		const std::size_t blockCountPerChunk,
		const MemoryPoolPurgeStrategy purgeStrategy
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

void * MemorySizedPool::allocate()
{
	return this->allocate(this->blockSize);
}

void * MemorySizedPool::allocate(const std::size_t size)
{
	assert(size <= this->blockSize);

	if(this->idleList.empty()) {
		const int chunkIndex = (int)this->chunkList.size();
		char * newChunk = (char *)malloc(this->chunkSize);
		this->chunkList.push_back(Chunk{
			std::unique_ptr<char>(newChunk),
			(char *)alignPointer(newChunk, this->alignment, sizeof(ChunkHeader))
		});
		
		for(int i = 1; i < (int)this->blockCountPerChunk; ++i) {
			this->idleList.push_back({ chunkIndex, i });
		}
		
		void * chunk = this->chunkList.back().start;
		ChunkHeader * chunkHeader = getChunkHeader(chunk);
		chunkHeader->usedCount = 1;
std::cout << "MemoryPool: Allocate new chunk: " << chunk << " " << (void *)this->chunkList.back().rawMemory.get() << " " << size << " " << this->blockTotalSize << " " << this << std::endl;
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

void MemorySizedPool::free(void * p)
{
	void * rawPointer = getRawPointer(p);
	for(int i = 0; i < (int)this->chunkList.size(); ++i) {
		char * chunk = (char *)this->chunkList[i].start;
		if(chunk <= rawPointer && rawPointer < chunk + this->chunkSize) {
			const int blockIndex = ((char *)rawPointer - chunk) / this->blockTotalSize;
			this->idleList.push_back({i, blockIndex});

			ChunkHeader * chunkHeader = getChunkHeader(chunk);
			--chunkHeader->usedCount;
			
			if(chunkHeader->usedCount == 0 && this->purgeStrategy == MemoryPoolPurgeStrategy::onFree) {
				this->doPurgeChunk(i);
			}

			break;
		}
	}
}

void MemorySizedPool::purge()
{
	for(int i = (int)this->chunkList.size() - 1; i >= 0; --i) {
		char * chunk = (char *)this->chunkList[i].start;
		ChunkHeader * chunkHeader = getChunkHeader(chunk);
		if(chunkHeader->usedCount == 0) {
			this->doPurgeChunk(i);
		}
	}
}

void MemorySizedPool::doPurgeChunk(const int index)
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

std::cout << "MemoryPool: Purged one chunk " << index << " " << this->chunkList[index].start << " " << this->blockTotalSize << " remain: " << this->chunkList.size() - 1 << std::endl;
	this->chunkList.erase(this->chunkList.begin() + index);
}


MemoryPool * MemoryPool::getInstance()
{
	static MemoryPool instance(memoryPoolAlignment, memoryPoolBlockCountPerTrunk, memoryPoolPurgeStrategy);
	
	return &instance;
}

MemoryPool::MemoryPool(
		const std::size_t alignment,
		const std::size_t blockCountPerChunk,
		const MemoryPoolPurgeStrategy purgeStrategy
	)
	:
		alignment(alignment),
		blockCountPerChunk(blockCountPerChunk),
		purgeStrategy(purgeStrategy)
{
}

MemoryPool::~MemoryPool()
{
}

void * MemoryPool::allocate(const std::size_t size)
{
	MemorySizedPool * pool = nullptr;

	const std::size_t alignedSize = alignSize(size, this->alignment, 0);

	auto it = this->poolMap.find(alignedSize);
	if(it != this->poolMap.end()) {
		pool = it->second.get();
	}
	else {
		pool = new MemorySizedPool(alignedSize, this->alignment, this->blockCountPerChunk, this->purgeStrategy);
		this->poolMap.insert(std::make_pair(alignedSize, std::unique_ptr<MemorySizedPool>(pool)));
	}
	
	void * p = pool->allocate(size);
//std::cout << p << std::endl;
	return p;
}

void MemoryPool::free(void * p)
{
	const std::size_t size = getSize(p);
	const std::size_t alignedSize = alignSize(size, this->alignment, 0);
	
	auto it = this->poolMap.find(alignedSize);
	if(it != this->poolMap.end()) {
		it->second->free(p);
	}
	else {
		std::cerr << "ERROR: can't find memory pool to free buffer." << std::endl;
	}
}

void MemoryPool::purge()
{
	for(auto it = this->poolMap.begin(); it != this->poolMap.end(); ++it) {
		it->second->purge();
	}
}

void MemoryPool::sceneFreed()
{
	if(this->purgeStrategy == MemoryPoolPurgeStrategy::onSceneFreed) {
		this->purge();
	}
}

void MemoryPool::sceneSwitched()
{
	if(this->purgeStrategy == MemoryPoolPurgeStrategy::onSceneSwitched) {
		this->purge();
	}
}


} //namespace gincu

