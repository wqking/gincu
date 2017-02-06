#ifndef GHEAPPOOL_H
#define GHEAPPOOL_H

#include <vector>
#include <map>
#include <memory>

namespace gincu {

enum class MemoryPoolPurgeStrategy
{
	never,
	onSceneFreed, // after previous scene is freed and next scene is not created yet
	onSceneSwitched, // after previous scene is freed and next scene has been created
	onFree
};

class MemorySizedPool
{
private:
	struct IdleIndex {
		int chunkIndex;
		int blockIndex;
	};
	
	struct Chunk {
		std::unique_ptr<char> rawMemory;
		void * start;
	};
	
public:
	MemorySizedPool(
			const std::size_t blockSize,
			const std::size_t alignment = 64,
			const std::size_t blockCountPerChunk = 256,
			const MemoryPoolPurgeStrategy purgeStrategy = MemoryPoolPurgeStrategy::onSceneSwitched
		);
	
	void * allocate();
	void * allocate(const std::size_t size);
	void free(void * p);
	
	void purge();

private:
	void doPurgeChunk(const int index);

private:
	std::size_t blockSize;
	std::size_t blockTotalSize;
	std::size_t alignment;
	std::size_t blockCountPerChunk;
	std::size_t chunkSize;
	MemoryPoolPurgeStrategy purgeStrategy;
	
	std::vector<Chunk> chunkList;
	std::vector<IdleIndex> idleList;
};

class MemoryPool
{
public:
	static MemoryPool * getInstance();
	
public:
	explicit MemoryPool(
			const std::size_t alignment = 64,
			const std::size_t blockCountPerChunk = 256,
			const MemoryPoolPurgeStrategy purgeStrategy = MemoryPoolPurgeStrategy::onSceneSwitched
		);
	~MemoryPool();
	
	void * allocate(const std::size_t size);
	void free(void * p);
	
	void purge();

	void sceneFreed();
	void sceneSwitched();

private:
	std::size_t alignment;
	std::size_t blockCountPerChunk;
	MemoryPoolPurgeStrategy purgeStrategy;
	std::map<std::size_t, std::unique_ptr<MemorySizedPool> > poolMap;
};


} //namespace gincu


#endif
