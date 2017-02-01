#ifndef GAMECOLOR_H
#define GAMECOLOR_H

namespace gincu {

typedef unsigned int GameColor;

const GameColor colorBlue = 0xff0000ff;
const GameColor colorGreen = 0xff00ff00;
const GameColor colorRed = 0xffff0000;
const GameColor colorYellow = 0xffffff00;
const GameColor colorPurple = 0xff800080;
const GameColor colorBlack = 0xff000000;
const GameColor colorWhite = 0xffffffff;

GameColor gameColorSetAlpha(const GameColor color, const int alpha);

inline GameColor gameColorMakeARGB(const int a, const int r, const int g, const int b)
{
	return ((GameColor)a << 24)
		+ ((GameColor)r << 16)
		+ ((GameColor)g << 8)
		+ ((GameColor)b)
	;
}


} //namespace gincu


#endif
