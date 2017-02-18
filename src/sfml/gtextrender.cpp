#include "gincu/gtextrender.h"
#include "gincu/grendercontext.h"
#include "gincu/gerrorhandler.h"
#include "gincu/gresourcemanager.h"
#include "gincu/gtransform.h"
#include "gsfmlutil.h"
#include "gtextrenderdata.h"
#include "gfontdata.h"

#include <SFML/Graphics.hpp>

namespace gincu {

GTextRender::GTextRender()
	:
		data(std::make_shared<GTextRenderData>())
{
}

GTextRender::~GTextRender()
{
}

void GTextRender::setText(const std::string & text)
{
	this->checkCopyOnWrite();

	this->data->text.setFont(GResourceManager::getInstance()->getFont().getData()->font);

	this->data->text.setString(text);
}

void GTextRender::setColor(const GColor textColor)
{
	this->checkCopyOnWrite();

	this->data->text.setOutlineColor(gameColorToSfml(textColor));
	this->data->text.setFillColor(gameColorToSfml(textColor));
}

void GTextRender::setFontSize(const int fontSize)
{
	this->checkCopyOnWrite();

	this->data->text.setCharacterSize(fontSize);
}

void GTextRender::draw(GRenderContext * renderContext, const GMatrix44 & matrix, const GRenderInfo * renderInfo)
{
	renderContext->draw(*this, matrix, renderInfo);
}

GSize GTextRender::getSize() const
{
	auto rect = this->data->text.getLocalBounds();
	return { rect.width, rect.height };
}

void GTextRender::checkCopyOnWrite()
{
	// if use_count > 1 means the data is used by render engine, so we can't modify it because multi thread conflict,
	// thus we have to duplicate it.
	if(this->data.use_count() != 1) {
		this->data = std::make_shared<GTextRenderData>(*this->data);
	}
}


} //namespace gincu
