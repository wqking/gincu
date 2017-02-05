#include "engine/rectrender.h"
#include "engine/renderengine.h"
#include "engine/gametransform.h"
#include "engine/sfml/sfmlutil.h"
#include "engine/sfml/rectrenderresource.h"

namespace gincu {

RectRender::RectRender()
	: resource(std::make_shared<RectRenderResource>())
{

}

RectRender::~RectRender()
{

}

void RectRender::draw(const GameTransform & transform, const RenderInfo * renderInfo)
{
	RenderEngine::getInstance()->draw(*this, transform, renderInfo);
}

void RectRender::setColor(const GameColor color)
{
	const sf::Color sfmlColor = gameColorToSfml(color);
	this->resource->rectangle.setOutlineColor(sfmlColor);
	this->resource->rectangle.setFillColor(sfmlColor);
}

GameColor RectRender::getColor() const
{
	return sfmlColorToGame(this->resource->rectangle.getFillColor());
}

void RectRender::setSize(const GameSize & size)
{
	this->resource->rectangle.setSize(sf::Vector2f(size.width, size.height));
}

GameSize RectRender::getSize() const
{
	const sf::Vector2f size = this->resource->rectangle.getSize();
	return GameSize{size.x, size.y};
}


} //namespace gincu
