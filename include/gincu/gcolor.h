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

GColor gameColorSetAlpha(const GColor color, const int alpha);

inline GColor gameColorMakeARGB(const int a, const int r, const int g, const int b)
{
	return ((GColor)a << 24)
		+ ((GColor)r << 16)
		+ ((GColor)g << 8)
		+ ((GColor)b)
	;
}


} //namespace gincu


#endif
