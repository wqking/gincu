#ifndef CONFIGURE_H
#define CONFIGURE_H

#include "framework/memorypool.h"

#include <cstddef>

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
constexpr MemoryPoolPurgeStrategy memoryPoolPurgeStrategy = MemoryPoolPurgeStrategy:: GINCU_MEMORY_POOL_PURGE_STRATEGY ;


} //namespace gincu

#endif
