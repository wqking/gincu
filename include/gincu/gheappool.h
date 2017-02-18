#ifndef GHEAPPOOL_H
#define GHEAPPOOL_H

#include <deque>
#include <map>
#include <memory>

namespace gincu {

enum class GHeapPoolPurgeStrategy
{
	never,
	onSceneFreed, // after previous scene is freed and next scene is not created yet
	onSceneSwitched, // after previous scene is freed and next scene has been created
	onFree
};

class GHeapSizedPool
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
	GHeapSizedPool(
			const std::size_t blockSize,
			const std::size_t alignment = 64,
			const std::size_t blockCountPerChunk = 256,
			const GHeapPoolPurgeStrategy purgeStrategy = GHeapPoolPurgeStrategy::onSceneSwitched
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
	GHeapPoolPurgeStrategy purgeStrategy;
	
	std::deque<Chunk> chunkList;
	std::deque<IdleIndex> idleList;
};

class GHeapPool
{
public:
	static GHeapPool * getInstance();
	
public:
	explicit GHeapPool(
			const std::size_t alignment = 64,
			const std::size_t blockCountPerChunk = 256,
			const GHeapPoolPurgeStrategy purgeStrategy = GHeapPoolPurgeStrategy::onSceneSwitched
		);
	~GHeapPool();
	
	void * allocate(const std::size_t size);
	void free(void * p);
	
	void purge();

	GHeapPoolPurgeStrategy getPurgeStrategy() const { return this->purgeStrategy; }

private:
	std::size_t alignment;
	std::size_t blockCountPerChunk;
	GHeapPoolPurgeStrategy purgeStrategy;
	std::map<std::size_t, std::unique_ptr<GHeapSizedPool> > poolMap;
};

template <typename T, typename... Params>
T * allocateObjectOnHeapPool(Params... params)
{
	void * p = GHeapPool::getInstance()->allocate(sizeof(T));
	return new (p) T (std::forward<Params>(params)...);
}

template <typename T>
void freeObjectOnHeapPool(T * obj)
{
	obj->~T();
	GHeapPool::getInstance()->free(obj);
}


} //namespace gincu


#endif
