#ifndef SFMLUTIL_H
#define SFMLUTIL_H

#include "engine/gamecolor.h"

#include <SFML/Graphics.hpp>

namespace gincu {

inline sf::Color gameColorToSfml(const GameColor color)
{
	return sf::Color(((color & 0xff000000) >> 24) | ((color & 0xffffff) << 8));
}

inline GameColor sfmlColorToGame(const sf::Color & color)
{
	return gameColorMakeARGB(color.a, color.r, color.g, color.b);
}


} //namespace gincu



#endif

