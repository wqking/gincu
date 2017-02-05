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
#include "engine/renderinfo.h"

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
	const GameConfigInfo & configInfo = GameApplication::getInstance()->getConfigInfo();

	int flags = 0;
	if(configInfo.fullScreenMode) {
		flags = sf::Style::Fullscreen;
	}
	else {
		flags = sf::Style::Titlebar | sf::Style::Close;
		if(configInfo.resizable) {
			flags |= sf::Style::Resize;
		}
	}

	this->windowSize = configInfo.windowSize;
	this->resource->window.reset(new sf::RenderWindow(
		sf::VideoMode((int)this->windowSize.width, (int)this->windowSize.height),
		configInfo.caption,
		flags
	));

	this->doFitView();
}

void RenderEngine::render()
{
	this->resource->window->clear(gameColorToSfml(GameApplication::getInstance()->getConfigInfo().backgroundColor));
	
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

void RenderEngine::draw(const GameImage & image, const GameTransform & transform, const RenderInfo * renderInfo)
{
	if(image.isValid()) {
		const GameRect & rect = image.getRect();
		const sf::Transform & sfmlTransform = transform.getSfmlTransform();
		if(! this->resource->inBatchDraw) {
			sf::Sprite sprite(image.getResource()->texture, { (int)rect.x, (int)rect.y, (int)rect.width, (int)rect.height });
			sf::RenderStates renderStates(sfmlTransform);
			copyBlendAndShaderToSfml(&renderStates, renderInfo);
			this->resource->window->draw(sprite, renderStates);
		}
		else {
			this->resource->batchDrawRenderInfo = *renderInfo;
			this->resource->batchDrawRenderInfo.texture = image.getResource().get();

			sf::VertexArray & vertexArray = this->resource->batchDrawVertexArray;
			std::size_t count = vertexArray.getVertexCount();
			vertexArray.resize(count + 6);

			vertexArray[count].position = sfmlTransform.transformPoint({ 0, 0 });
			vertexArray[count].texCoords = { rect.x, rect.y };
			++count;
			vertexArray[count].position = sfmlTransform.transformPoint({ rect.width, 0 });
			vertexArray[count].texCoords = { rect.x + rect.width, rect.y };
			++count;
			vertexArray[count].position = sfmlTransform.transformPoint({ rect.width, rect.height });
			vertexArray[count].texCoords = { rect.x + rect.width, rect.y + rect.height };
			++count;

			vertexArray[count].position = sfmlTransform.transformPoint({ rect.width, rect.height });
			vertexArray[count].texCoords = { rect.x + rect.width, rect.y + rect.height };
			++count;
			vertexArray[count].position = sfmlTransform.transformPoint({ 0, rect.height });
			vertexArray[count].texCoords = { rect.x, rect.y + rect.height };
			++count;
			vertexArray[count].position = sfmlTransform.transformPoint({ 0, 0 });
			vertexArray[count].texCoords = { rect.x, rect.y };
		}
	}
}

void RenderEngine::draw(const GameText & text, const GameTransform & transform, const RenderInfo * renderInfo)
{
	sf::RenderStates renderStates(transform.getSfmlTransform());
	copyBlendAndShaderToSfml(&renderStates, renderInfo);
	this->resource->window->draw(text.getResource()->text, renderStates);
}

void RenderEngine::draw(const RectRender & rect, const GameTransform & transform, const RenderInfo * renderInfo)
{
	sf::RenderStates renderStates(transform.getSfmlTransform());
	copyBlendAndShaderToSfml(&renderStates, renderInfo);
	this->resource->window->draw(rect.getResource()->rectangle, renderStates);
}

void RenderEngine::beginBatchDraw()
{
	this->resource->clearBatchDrawState();
	this->resource->inBatchDraw = true;
}

void RenderEngine::endBatchDraw()
{
	if(this->resource->batchDrawRenderInfo.texture != nullptr && this->resource->inBatchDraw) {
		sf::RenderStates renderStates(&this->resource->batchDrawRenderInfo.texture->texture);
		copyBlendAndShaderToSfml(&renderStates, &this->resource->batchDrawRenderInfo);
		this->resource->window->draw(this->resource->batchDrawVertexArray, renderStates);
	}

	this->resource->clearBatchDrawState();
}

GamePoint RenderEngine::mapWindowToView(const GamePoint & point) const
{
	auto pt = this->resource->window->mapPixelToCoords({(int)point.x, (int)point.y});
	return {pt.x, pt.y};
}

void RenderEngine::onWindowResized(const GameSize & newSize)
{
	this->windowSize = newSize;
	this->doFitView();
}

void RenderEngine::doFitView()
{
	const GameConfigInfo & configInfo = GameApplication::getInstance()->getConfigInfo();

	switch(configInfo.viewFitStrategy) {
	case ViewFitStrategy::scaleFit: {
		this->resource->view.reset(sf::FloatRect(0, 0, configInfo.viewSize.width, configInfo.viewSize.height));
		float viewportX = 0;
		float viewportY = 0;
		const float xRatio = (float)configInfo.viewSize.width / (float)this->windowSize.width;
		const float yRatio = (float)configInfo.viewSize.height / (float)this->windowSize.height;
		if(xRatio > yRatio) {
			viewportY = (1.0f - yRatio / xRatio) / 2.0f;
		}
		else {
			viewportX = (1.0f - xRatio / yRatio) / 2.0f;
		}
		this->resource->view.setViewport(sf::FloatRect(viewportX, viewportY, 1.0f - viewportX * 2.0f, 1.0f - viewportY * 2.0f));
	}
		break;

	case ViewFitStrategy::fitWindow:
		this->resource->view.reset(sf::FloatRect(0, 0, this->windowSize.width, this->windowSize.height));
		this->resource->view.setViewport(sf::FloatRect(0, 0, 1, 1));
		break;

	case ViewFitStrategy::stretch:
		this->resource->view.reset(sf::FloatRect(0, 0, configInfo.viewSize.width, configInfo.viewSize.height));
		this->resource->view.setViewport(sf::FloatRect(0, 0, 1, 1));
		break;
	}

	this->resource->window->setView(this->resource->view);
}

} //namespace gincu
