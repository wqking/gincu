#include "engine/gametext.h"
#include "engine/renderengine.h"
#include "engine/errorhandler.h"
#include "engine/resourcemanager.h"
#include "engine/gametransform.h"
#include "engine/sfml/sfmlutil.h"
#include "engine/sfml/gametextresource.h"
#include "engine/sfml/gamefontresource.h"

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

void GameText::draw(const GameTransform & transform)
{
	RenderEngine::getInstance()->draw(*this, transform);
}

GameSize GameText::getSize() const
{
	auto rect = this->resource->text.getLocalBounds();
	return { rect.width, rect.height };
}


} //namespace gincu
