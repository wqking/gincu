#include "framework/util.h"

#include <cstdlib>
#include <ctime>

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


} //namespace gincu
