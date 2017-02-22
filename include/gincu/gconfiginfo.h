#ifndef GGAMECONFIGINFO_H
#define GGAMECONFIGINFO_H

#include "gincu/ggeometry.h"
#include "gincu/gcolor.h"

#include <string>

namespace gincu {

struct GConfigInfo
{
	std::string engine;
	std::string caption;
	int framesPerSecond;
	int renderFramesPerSecond; // -1 will use framesPerSecond
	GSize windowSize; // the initial window size
	GSize targetViewSize;
	bool fullScreenMode;
	bool resizable;
	GColor backgroundColor;
};

inline GConfigInfo createDefaultConfigInfo()
{
	return {
		"",
		"",
		60,
		-1,
		{ 800, 600 },
		{ 800, 600 },
		false,
		true,
		colorWhite
	};
}


} //namespace gincu




#endif

