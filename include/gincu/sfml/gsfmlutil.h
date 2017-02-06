#ifndef GSFMLUTIL_H
#define GSFMLUTIL_H

#include "gincu/gcolor.h"
#include "gincu/ggeometry.h"
#include "gincu/gblendmode.h"
#include "gincu/grenderinfo.h"

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

inline sf::Vector2f gameVector2ToSfml(const GameVector2 & v)
{
	return { v.x, v.y };
}

inline sf::BlendMode gameBlendModeToSfml(const GameBlendMode & blendMode)
{
	return sf::BlendMode(
		(sf::BlendMode::Factor)blendMode.colorChannel.source,
		(sf::BlendMode::Factor)blendMode.colorChannel.dest,
		(sf::BlendMode::Equation)blendMode.colorChannel.func,
		(sf::BlendMode::Factor)blendMode.alphaChannel.source,
		(sf::BlendMode::Factor)blendMode.alphaChannel.dest,
		(sf::BlendMode::Equation)blendMode.alphaChannel.func
	);
}

inline void copyBlendAndShaderToSfml(sf::RenderStates * renderStates, const RenderInfo * renderInfo)
{
	renderStates->blendMode = gameBlendModeToSfml(renderInfo->blendMode);
}


} //namespace gincu



#endif

