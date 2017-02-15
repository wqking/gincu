#include "gincu/grectrender.h"
#include "gincu/grenderengine.h"
#include "gincu/gtransform.h"
#include "gsfmlutil.h"
#include "grectrenderdata.h"

namespace gincu {

GRectRender::GRectRender()
	: data(std::make_shared<GRectRenderData>())
{

}

GRectRender::~GRectRender()
{

}

void GRectRender::draw(const GMatrix44 & matrix, const GRenderInfo * renderInfo)
{
	GRenderEngine::getInstance()->draw(*this, matrix, renderInfo);
}

void GRectRender::setColor(const GColor color)
{
	const sf::Color sfmlColor = gameColorToSfml(color);
	this->data->rectangle.setOutlineColor(sfmlColor);
	this->data->rectangle.setFillColor(sfmlColor);
}

GColor GRectRender::getColor() const
{
	return sfmlColorToGame(this->data->rectangle.getFillColor());
}

void GRectRender::setSize(const GSize & size)
{
	this->data->rectangle.setSize(sf::Vector2f(size.width, size.height));
}

GSize GRectRender::getSize() const
{
	const sf::Vector2f size = this->data->rectangle.getSize();
	return GSize{size.x, size.y};
}


} //namespace gincu
