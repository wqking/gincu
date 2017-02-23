#include "gincu/gutil.h"

#include <cstdlib>
#include <ctime>
#include <chrono>
#include <thread>
#include <cstdint>

namespace gincu {

namespace {

bool needInitializeRandSeed = true;

}

int getRand()
{
	if(needInitializeRandSeed) {
		needInitializeRandSeed = false;
		srand((size_t)time(NULL));
	}

	return rand();
}

int getRand(const int min, const int max)
{
	if(min == max) {
		return min;
	}

	return min + getRand() % (max - min);
}

int getRand(const int max)
{
	return getRand(0, max);
}

void sleepMilliseconds(const unsigned int milliseconds)
{
	const auto start = std::chrono::high_resolution_clock::now();
	uint64_t nano = milliseconds * (1000 * 1000);
	if(nano) {
		--nano;
	}
	for(;;) {
		const auto now = std::chrono::high_resolution_clock::now();
		const std::chrono::nanoseconds diff = std::chrono::duration_cast<std::chrono::nanoseconds>(now - start);
		if((uint64_t)diff.count() >= nano) {
			break;
		}
		std::this_thread::sleep_for(std::chrono::microseconds(10));
	}
}

unsigned int getMilliseconds()
{
	static auto start = std::chrono::high_resolution_clock::now();
	const auto now = std::chrono::high_resolution_clock::now();
	const std::chrono::milliseconds diff = std::chrono::duration_cast<std::chrono::milliseconds>(now - start);
	return diff.count();
}


} //namespace gincu
