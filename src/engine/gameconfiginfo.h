#ifndef GAMECONFIGINFO_H
#define GAMECONFIGINFO_H

#include "engine/geometry.h"
#include "engine/gamecolor.h"

#include <string>

namespace gincu {

enum class ViewFitStrategy
{
	scaleFit, // recommend, scale the view to fit the window and keep aspect ratio
	stretch, // always use the fixed size and cover the whole windows, doesn't keep aspect ratio
	fitWindow, // ignore view size, always fit to the window, i.e, the view size is always same as window size
};

struct GameConfigInfo
{
	std::string caption;
	int framesPerSecond;
	int renderFramesPerSecond; // -1 will use framesPerSecond
	GameSize windowSize; // the initial window size
	GameSize viewSize; // the virtual view size, no matter how the window resized
	bool fullScreenMode;
	bool resizable;
	ViewFitStrategy viewFitStrategy;
	GameColor backgroundColor;
};

inline GameConfigInfo createDefaultConfigInfo()
{
	return {
		"",
		60,
		-1,
		{ 800, 600 },
		{ 800, 600 },
		false,
		true,
		ViewFitStrategy::scaleFit,
		colorWhite
	};
}


} //namespace gincu




#endif

