#ifndef GSFMLUTIL_H
#define GSFMLUTIL_H

#include "gincu/gcolor.h"
#include "gincu/ggeometry.h"
#include "gincu/gblendmode.h"
#include "gincu/grenderinfo.h"
#include "gincu/gmatrix.h"
#include "gincu/gprimitive.h"

#include <SFML/Graphics.hpp>

namespace gincu {

inline sf::Color gameColorToSfml(const GColor color)
{
	return sf::Color(((color & 0xff000000) >> 24) | ((color & 0xffffff) << 8));
}

inline GColor sfmlColorToGame(const sf::Color & color)
{
	return gameColorMakeARGB(color.a, color.r, color.g, color.b);
}

inline sf::Vector2f gameVector2ToSfml(const GVector2 & v)
{
	return { v.x, v.y };
}

inline sf::BlendMode gameBlendModeToSfml(const GBlendMode & blendMode)
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

inline void copyBlendAndShaderToSfml(sf::RenderStates * renderStates, const GRenderInfo * renderInfo)
{
	renderStates->blendMode = gameBlendModeToSfml(renderInfo->blendMode);
}

inline sf::Transform matrixToSfml(const glm::mat4 & matrix)
{
	sf::Transform transform;
	memcpy(const_cast<float *>(transform.getMatrix()), &matrix[0][0], 16 * sizeof(float));
	return transform;
}

inline void matrixToSfml(const sf::Transform * outputResult, const glm::mat4 & matrix)
{
	memcpy(const_cast<float *>(outputResult->getMatrix()), &matrix[0][0], 16 * sizeof(float));
}

inline sf::PrimitiveType gamePrimitiveToSfml(const GPrimitive primitive)
{
	return (sf::PrimitiveType)primitive;
}


} //namespace gincu



#endif

