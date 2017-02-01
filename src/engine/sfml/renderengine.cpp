#include "engine/renderengine.h"
#include "engine/renderable.h"
#include "engine/gametransform.h"
#include "engine/gameimage.h"
#include "engine/gametext.h"
#include "engine/rectrender.h"
#include "engine/sfml/sfmlutil.h"
#include "engine/sfml/gameimageresource.h"
#include "engine/sfml/gametextresource.h"
#include "engine/sfml/rectrenderresource.h"
#include "engine/sfml/renderengineresource.h"
#include "framework/gameapplication.h"

#include <cassert>

namespace gincu {

namespace {

RenderEngine * instance = nullptr;

} //unnamed namespace

RenderEngine * RenderEngine::getInstance()
{
	return instance;
}

RenderEngine::RenderEngine()
	:
		resource(std::make_shared<RenderEngineResource>())
{
	assert(instance == nullptr);

	instance = this;
}

RenderEngine::~RenderEngine()
{
}

void RenderEngine::inititialize()
{
	const GameSize viewSize = GameApplication::getInstance()->getViewSize();
	this->resource->window.reset(new sf::RenderWindow(sf::VideoMode((int)viewSize.width, (int)viewSize.height), "Gincu"));
}

void RenderEngine::render()
{
	this->resource->window->clear(sf::Color(0xee, 0xee, 0xee, 0xff));
	
	for(auto it = this->renderableList.rbegin(); it != this->renderableList.rend(); ++it) {
		(*it)->render();
	}

	this->resource->window->display();
}

void RenderEngine::appendRenderable(Renderable * renderable)
{
	this->renderableList.push_back(renderable);
}

void RenderEngine::removeRenderable(Renderable * renderable)
{
	auto it = std::find(this->renderableList.begin(), this->renderableList.end(), renderable);
	if(it != this->renderableList.end()) {
		this->renderableList.erase(it);
	}
}

bool RenderEngine::isAlive() const
{
	return this->resource->window->isOpen();
}

void RenderEngine::draw(const GameImage & image, const GameTransform & transform)
{
	sf::Sprite sprite(image.getResource()->texture);
	this->resource->window->draw(sprite, transform.getSfmlTransform());
}

void RenderEngine::draw(const GameText & text, const GameTransform & transform)
{
	this->resource->window->draw(text.getResource()->text, transform.getSfmlTransform());
}

void RenderEngine::draw(const RectRender & rect, const GameTransform & transform)
{
	this->resource->window->draw(rect.getResource()->rectangle, transform.getSfmlTransform());
}


} //namespace gincu
