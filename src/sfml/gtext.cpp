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

GameText::GameText()
	: GameText(16)
{
}

GameText::GameText(const int fontSize)
	:
		resource(std::make_shared<GameTextResource>())
{
	this->resource->fontSize = fontSize;
}

GameText::~GameText()
{
}

void GameText::setText(const std::string & text)
{
	this->resource->text.setFont(ResourceManager::getInstance()->getFont().getResource()->font);
	this->resource->text.setCharacterSize(this->resource->fontSize);

	this->resource->text.setString(text);
}

void GameText::setColor(const GameColor textColor)
{
	this->resource->text.setOutlineColor(gameColorToSfml(textColor));
	this->resource->text.setFillColor(gameColorToSfml(textColor));
}

void GameText::setTextAndColor(const std::string & text, const GameColor textColor)
{
	this->setText(text);
	this->setColor(textColor);
}

void GameText::draw(const GameTransform & transform, const RenderInfo * renderInfo)
{
	RenderEngine::getInstance()->draw(*this, transform, renderInfo);
}

GameSize GameText::getSize() const
{
	auto rect = this->resource->text.getLocalBounds();
	return { rect.width, rect.height };
}


} //namespace gincu
