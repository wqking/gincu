#ifndef GGAMECONFIGINFO_H
#define GGAMECONFIGINFO_H

#include "gincu/ggeometry.h"
#include "gincu/gcolor.h"

#include <string>

namespace gincu {

enum class GViewFitStrategy
{
	scaleFit, // recommend, scale the view to fit the window and keep aspect ratio
	stretch, // always use the fixed size and cover the whole windows, doesn't keep aspect ratio
	fitWindow, // ignore view size, always fit to the window, i.e, the view size is always same as window size
};

struct GConfigInfo
{
	std::string caption;
	int framesPerSecond;
	int renderFramesPerSecond; // -1 will use framesPerSecond
	GSize windowSize; // the initial window size
	GSize viewSize; // the virtual view size, no matter how the window resized
	bool fullScreenMode;
	bool resizable;
	GViewFitStrategy viewFitStrategy;
	GColor backgroundColor;
};

inline GConfigInfo createDefaultConfigInfo()
{
	return {
		"",
		60,
		-1,
		{ 800, 600 },
		{ 800, 600 },
		false,
		true,
		GViewFitStrategy::scaleFit,
		colorWhite
	};
}


} //namespace gincu




#endif

