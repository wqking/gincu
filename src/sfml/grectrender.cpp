#include "gincu/grectrender.h"
#include "gincu/grenderengine.h"
#include "gincu/gtransform.h"
#include "gincu/sfml/gsfmlutil.h"
#include "gincu/sfml/grectrenderresource.h"

namespace gincu {

GRectRender::GRectRender()
	: resource(std::make_shared<GRectRenderResource>())
{

}

GRectRender::~GRectRender()
{

}

void GRectRender::draw(const GTransform & transform, const GRenderInfo * renderInfo)
{
	GRenderEngine::getInstance()->draw(*this, transform, renderInfo);
}

void GRectRender::setColor(const GColor color)
{
	const sf::Color sfmlColor = gameColorToSfml(color);
	this->resource->rectangle.setOutlineColor(sfmlColor);
	this->resource->rectangle.setFillColor(sfmlColor);
}

GColor GRectRender::getColor() const
{
	return sfmlColorToGame(this->resource->rectangle.getFillColor());
}

void GRectRender::setSize(const GSize & size)
{
	this->resource->rectangle.setSize(sf::Vector2f(size.width, size.height));
}

GSize GRectRender::getSize() const
{
	const sf::Vector2f size = this->resource->rectangle.getSize();
	return GSize{size.x, size.y};
}


} //namespace gincu
