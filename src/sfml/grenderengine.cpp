#include "gincu/grenderengine.h"
#include "gincu/gtransform.h"
#include "gincu/gimage.h"
#include "gincu/gspritesheetrender.h"
#include "gincu/gtext.h"
#include "gincu/grectrender.h"
#include "gincu/gapplication.h"
#include "gincu/grenderinfo.h"
#include "gincu/sfml/gsfmlutil.h"
#include "gincu/sfml/gimageresource.h"
#include "gincu/sfml/gtextresource.h"
#include "gincu/sfml/grectrenderresource.h"
#include "gincu/sfml/grenderengineresource.h"

#include <cassert>

namespace gincu {

namespace {

GRenderEngine * instance = nullptr;

} //unnamed namespace

GRenderEngine * GRenderEngine::getInstance()
{
	return instance;
}

GRenderEngine::GRenderEngine()
	:
		resource(std::make_shared<GRenderEngineResource>())
{
	assert(instance == nullptr);

	instance = this;
}

GRenderEngine::~GRenderEngine()
{
}

void GRenderEngine::inititialize()
{
	const GConfigInfo & configInfo = GApplication::getInstance()->getConfigInfo();

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

void GRenderEngine::render()
{
	this->resource->window->clear(gameColorToSfml(GApplication::getInstance()->getConfigInfo().backgroundColor));
	
	this->renderList();

	this->resource->window->display();
}

void GRenderEngine::appendRender(const cpgf::GCallback<void ()> & render)
{
	this->renderList.add(render);
}

void GRenderEngine::removeRender(const cpgf::GCallback<void ()> & render)
{
	this->renderList.remove(render);
}

bool GRenderEngine::isAlive() const
{
	return this->resource->window->isOpen();
}

void GRenderEngine::draw(const GImage & image, const GTransform & transform, const GRenderInfo * renderInfo)
{
	this->doDrawTexture(image.getResource().get(), image.getRect(), transform, renderInfo);
}

void GRenderEngine::draw(const GSpriteSheetRender & spriteSheetRender, const GTransform & transform, const GRenderInfo * renderInfo)
{
	this->doDrawTexture(spriteSheetRender.getSpriteSheet().getImageResource().get(), spriteSheetRender.getRect(), transform, renderInfo);
}

void GRenderEngine::draw(const GText & text, const GTransform & transform, const GRenderInfo * renderInfo)
{
	sf::RenderStates renderStates(transform.getSfmlTransform());
	copyBlendAndShaderToSfml(&renderStates, renderInfo);
	this->resource->window->draw(text.getResource()->text, renderStates);
}

void GRenderEngine::draw(const GRectRender & rect, const GTransform & transform, const GRenderInfo * renderInfo)
{
	sf::RenderStates renderStates(transform.getSfmlTransform());
	copyBlendAndShaderToSfml(&renderStates, renderInfo);
	this->resource->window->draw(rect.getResource()->rectangle, renderStates);
}

void GRenderEngine::beginBatchDraw()
{
	this->resource->clearBatchDrawState();
	this->resource->inBatchDraw = true;
}

void GRenderEngine::endBatchDraw()
{
	if(this->resource->batchDrawRenderInfo.texture != nullptr && this->resource->inBatchDraw) {
		sf::RenderStates renderStates(&this->resource->batchDrawRenderInfo.texture->texture);
		copyBlendAndShaderToSfml(&renderStates, &this->resource->batchDrawRenderInfo);
		this->resource->window->draw(this->resource->batchDrawVertexArray, renderStates);
	}

	this->resource->clearBatchDrawState();
}

GPoint GRenderEngine::mapWindowToView(const GPoint & point) const
{
	auto pt = this->resource->window->mapPixelToCoords({(int)point.x, (int)point.y});
	return {pt.x, pt.y};
}

void GRenderEngine::onWindowResized(const GSize & newSize)
{
	this->windowSize = newSize;
	this->doFitView();
}

void GRenderEngine::doDrawTexture(const GImageResource * texture, const GRect & rect, const GTransform & transform, const GRenderInfo * renderInfo)
{
	if(texture != nullptr) {
		const sf::Transform & sfmlTransform = transform.getSfmlTransform();
		if(! this->resource->inBatchDraw) {
			sf::Sprite sprite(texture->texture, { (int)rect.x, (int)rect.y, (int)rect.width, (int)rect.height });
			sf::RenderStates renderStates(sfmlTransform);
			copyBlendAndShaderToSfml(&renderStates, renderInfo);
			this->resource->window->draw(sprite, renderStates);
		}
		else {
			this->resource->batchDrawRenderInfo = *renderInfo;
			this->resource->batchDrawRenderInfo.texture = texture;

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

void GRenderEngine::doFitView()
{
	const GConfigInfo & configInfo = GApplication::getInstance()->getConfigInfo();

	switch(configInfo.viewFitStrategy) {
	case GViewFitStrategy::scaleFit: {
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

	case GViewFitStrategy::fitWindow:
		this->resource->view.reset(sf::FloatRect(0, 0, this->windowSize.width, this->windowSize.height));
		this->resource->view.setViewport(sf::FloatRect(0, 0, 1, 1));
		break;

	case GViewFitStrategy::stretch:
		this->resource->view.reset(sf::FloatRect(0, 0, configInfo.viewSize.width, configInfo.viewSize.height));
		this->resource->view.setViewport(sf::FloatRect(0, 0, 1, 1));
		break;
	}

	this->resource->window->setView(this->resource->view);
}

} //namespace gincu
