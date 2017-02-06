#include "gincu/gtext.h"
#include "gincu/grenderengine.h"
#include "gincu/gerrorhandler.h"
#include "gincu/gresourcemanager.h"
#include "gincu/gtransform.h"
#include "gincu/sfml/gsfmlutil.h"
#include "gincu/sfml/gtextresource.h"
#include "gincu/sfml/gfontresource.h"

#include <SFML/Graphics.hpp>

namespace gincu {

GText::GText()
	: GText(16)
{
}

GText::GText(const int fontSize)
	:
		resource(std::make_shared<GTextResource>())
{
	this->resource->fontSize = fontSize;
}

GText::~GText()
{
}

void GText::setText(const std::string & text)
{
	this->resource->text.setFont(GResourceManager::getInstance()->getFont().getResource()->font);
	this->resource->text.setCharacterSize(this->resource->fontSize);

	this->resource->text.setString(text);
}

void GText::setColor(const GColor textColor)
{
	this->resource->text.setOutlineColor(gameColorToSfml(textColor));
	this->resource->text.setFillColor(gameColorToSfml(textColor));
}

void GText::setTextAndColor(const std::string & text, const GColor textColor)
{
	this->setText(text);
	this->setColor(textColor);
}

void GText::draw(const GTransform & transform, const GRenderInfo * renderInfo)
{
	GRenderEngine::getInstance()->draw(*this, transform, renderInfo);
}

GSize GText::getSize() const
{
	auto rect = this->resource->text.getLocalBounds();
	return { rect.width, rect.height };
}


} //namespace gincu
