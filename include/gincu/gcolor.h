#ifndef GCOLOR_H
#define GCOLOR_H

namespace gincu {

typedef unsigned int GColor;

const GColor colorBlue = 0xff0000ff;
const GColor colorGreen = 0xff00ff00;
const GColor colorRed = 0xffff0000;
const GColor colorYellow = 0xffffff00;
const GColor colorPurple = 0xff800080;
const GColor colorBlack = 0xff000000;
const GColor colorWhite = 0xffffffff;

inline GColor colorSetAlpha(const GColor color, const unsigned int alpha)
{
	return (color & 0x00ffffff) | ((alpha & 0xff) << 24);
}

inline unsigned int colorGetAlpha(const GColor color)
{
	return (color & 0xff000000) >> 24;
}

inline unsigned int colorGetRed(const GColor color)
{
	return (color & 0x00ff0000) >> 16;
}

inline unsigned int colorGetGreen(const GColor color)
{
	return (color & 0x0000ff00) >> 8;
}

inline unsigned int colorGetBlue(const GColor color)
{
	return (color & 0x000000ff);
}

inline GColor colorMakeARGB(const int a, const int r, const int g, const int b)
{
	return ((GColor)a << 24)
		+ ((GColor)r << 16)
		+ ((GColor)g << 8)
		+ ((GColor)b)
	;
}


} //namespace gincu


#endif
