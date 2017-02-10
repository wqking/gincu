#include "gincu/gtextrender.h"
#include "gincu/grenderengine.h"
#include "gincu/gerrorhandler.h"
#include "gincu/gresourcemanager.h"
#include "gincu/gtransform.h"
#include "gsfmlutil.h"
#include "gtextrenderdata.h"
#include "gfontdata.h"

#include <SFML/Graphics.hpp>

namespace gincu {

GTextRender::GTextRender()
	: GTextRender(16)
{
}

GTextRender::GTextRender(const int fontSize)
	:
		data(std::make_shared<GTextRenderData>())
{
	this->data->fontSize = fontSize;
}

GTextRender::~GTextRender()
{
}

void GTextRender::setText(const std::string & text)
{
	this->data->text.setFont(GResourceManager::getInstance()->getFont().getData()->font);
	this->data->text.setCharacterSize(this->data->fontSize);

	this->data->text.setString(text);
}

void GTextRender::setColor(const GColor textColor)
{
	this->data->text.setOutlineColor(gameColorToSfml(textColor));
	this->data->text.setFillColor(gameColorToSfml(textColor));
}

void GTextRender::setTextAndColor(const std::string & text, const GColor textColor)
{
	this->setText(text);
	this->setColor(textColor);
}

void GTextRender::draw(const GTransform & transform, const GRenderInfo * renderInfo)
{
	GRenderEngine::getInstance()->draw(*this, transform, renderInfo);
}

GSize GTextRender::getSize() const
{
	auto rect = this->data->text.getLocalBounds();
	return { rect.width, rect.height };
}


} //namespace gincu
