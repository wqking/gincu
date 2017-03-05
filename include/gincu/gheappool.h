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

	struct ChunkRange {
		ChunkRange(void * start) : start(start), end(nullptr) {
		}

		ChunkRange(void * start, void * end) : start(start), end(end) {
		}

		bool operator < (const ChunkRange & other) const {
			if(this->end == NULL) {
				return this->start < other.start;
			}
			else {
				if(other.end == NULL) {
					return other.start >= this->end;
				}
				else {
					return this->start < other.start;
				}
			}
		}

		void * start;
		void * end;
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
	std::map<ChunkRange, int> chunkMap;
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
T * allocateObjectOnHeapPool(Params && ... params)
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

template <class T>
struct GHeapPoolAllocator
{
	typedef T value_type;
	typedef T * pointer;

	GHeapPoolAllocator()
		: heapPool(GHeapPool::getInstance())
	{}

	template <class U>
	GHeapPoolAllocator(const GHeapPoolAllocator<U> & other)
		: heapPool(other.heapPool)
	{
	}
	
	T * allocate(std::size_t n)
	{
		return (T *)(this->heapPool->allocate(n));
	}
	
	void deallocate(T * p, std::size_t /*n*/)
	{
		this->heapPool->free(p);
	}
	
	GHeapPool * heapPool;
};

template <class T, class U>
bool operator == (const GHeapPoolAllocator<T> & a, const GHeapPoolAllocator<U> & b)
{
	return a.heapPool == b.heapPool;
}

template <class T, class U>
bool operator != (const GHeapPoolAllocator<T> & a, const GHeapPoolAllocator<U> & b)
{
	return ! operator == (a, b);
}

template <typename T, typename... Params>
std::shared_ptr<T>  createPooledSharedPtr(Params && ... params)
{
	return std::allocate_shared<T>(GHeapPoolAllocator<T>(), std::forward<Params>(params)...);
}


} //namespace gincu


#endif
