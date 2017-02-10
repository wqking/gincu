#include "gincu/grenderengine.h"
#include "gincu/gtransform.h"
#include "gincu/gimage.h"
#include "gincu/gspritesheetrender.h"
#include "gincu/gtextrender.h"
#include "gincu/grectrender.h"
#include "gincu/gapplication.h"
#include "gincu/grenderinfo.h"
#include "gincu/sfml/gsfmlutil.h"
#include "gincu/sfml/gimagedata.h"
#include "gincu/sfml/gtextrenderdata.h"
#include "gincu/sfml/grectrenderdata.h"
#include "gincu/sfml/grenderenginedata.h"

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
		data(std::make_shared<GRenderEngineData>())
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
	this->data->window.reset(new sf::RenderWindow(
		sf::VideoMode((int)this->windowSize.width, (int)this->windowSize.height),
		configInfo.caption,
		flags
	));

	this->doFitView();
}

void GRenderEngine::render()
{
	this->data->window->clear(gameColorToSfml(GApplication::getInstance()->getConfigInfo().backgroundColor));
	
	this->renderList();

	this->endBatchDraw();

	this->data->window->display();
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
	return this->data->window->isOpen();
}

void GRenderEngine::draw(const GImage & image, const GTransform & transform, const GRenderInfo * renderInfo)
{
	this->doDrawTexture(image.getData(), image.getRect(), transform, renderInfo);
}

void GRenderEngine::draw(const GSpriteSheetRender & spriteSheetRender, const GTransform & transform, const GRenderInfo * renderInfo)
{
	this->doDrawTexture(spriteSheetRender.getSpriteSheet().getImageData(), spriteSheetRender.getRect(), transform, renderInfo);
}

void GRenderEngine::draw(const GTextRender & text, const GTransform & transform, const GRenderInfo * renderInfo)
{
	this->endBatchDraw();

	sf::RenderStates renderStates(transform.getSfmlTransform());
	copyBlendAndShaderToSfml(&renderStates, renderInfo);
	this->data->window->draw(text.getData()->text, renderStates);
}

void GRenderEngine::draw(const GRectRender & rect, const GTransform & transform, const GRenderInfo * renderInfo)
{
	this->endBatchDraw();

	sf::RenderStates renderStates(transform.getSfmlTransform());
	copyBlendAndShaderToSfml(&renderStates, renderInfo);
	this->data->window->draw(rect.getData()->rectangle, renderStates);
}

void GRenderEngine::beginBatchDraw()
{
	this->data->clearBatchDrawState();
	this->data->inBatchDraw = true;
}

void GRenderEngine::endBatchDraw()
{
	this->flush();

	if(this->data->inBatchDraw) {
		if(this->data->batchDrawImageData) {
			sf::RenderStates renderStates(&this->data->batchDrawImageData->texture);
			copyBlendAndShaderToSfml(&renderStates, &this->data->batchDrawRenderInfo);
			this->data->window->draw(this->data->batchDrawVertexArray, renderStates);
		}

		this->data->clearBatchDrawState();
	}
}

GPoint GRenderEngine::mapWindowToView(const GPoint & point) const
{
	auto pt = this->data->window->mapPixelToCoords({(int)point.x, (int)point.y});
	return {pt.x, pt.y};
}

void GRenderEngine::onWindowResized(const GSize & newSize)
{
	this->windowSize = newSize;
	this->doFitView();
}

void GRenderEngine::flush()
{
	GCachedRenderItem & cachedItem = this->data->cachedRenderItem;
	switch(cachedItem.type) {
	case GCachedRenderType::texture:
		this->doDirectDrawTexture(cachedItem.imageData, cachedItem.imageRect, cachedItem.imageTransform, &cachedItem.imageRenderInfo);
		break;

	case GCachedRenderType::none:
		break;
	}

	cachedItem.reset();
}

void GRenderEngine::doDrawTexture(const std::shared_ptr<GImageData> & texture, const GRect & rect, const GTransform & transform, const GRenderInfo * renderInfo)
{
	if(! texture) {
		return;
	}

	GCachedRenderItem & cachedItem = this->data->cachedRenderItem;
	if(cachedItem.type != GCachedRenderType::none && cachedItem.type != GCachedRenderType::texture) {
		this->flush();
	}

	bool needCache = false;
	if(this->data->inBatchDraw) {
		if(texture == this->data->batchDrawImageData
			&& *renderInfo == this->data->batchDrawRenderInfo) {
			this->doBatchDrawTexture(texture, rect, transform, renderInfo);
		}
		else {
			this->endBatchDraw();
			needCache = true;
		}
	}
	else {
		if(texture == cachedItem.imageData
			&& *renderInfo == cachedItem.imageRenderInfo) {
			this->beginBatchDraw();
			this->doBatchDrawTexture(cachedItem.imageData, cachedItem.imageRect, cachedItem.imageTransform, &cachedItem.imageRenderInfo);
			this->doBatchDrawTexture(texture, rect, transform, renderInfo);
		}
		else {
			if(cachedItem.imageData) {
				this->flush();
			}
			needCache = true;
		}
	}
	if(needCache) {
		cachedItem.type = GCachedRenderType::texture;
		cachedItem.imageData = texture;
		cachedItem.imageRect = rect;
		cachedItem.imageTransform = transform;
		cachedItem.imageRenderInfo = *renderInfo;
	}
}

void GRenderEngine::doDirectDrawTexture(const std::shared_ptr<GImageData> & texture, const GRect & rect, const GTransform & transform, const GRenderInfo * renderInfo)
{
	const sf::Transform & sfmlTransform = transform.getSfmlTransform();

	sf::Sprite sprite(texture->texture, { (int)rect.x, (int)rect.y, (int)rect.width, (int)rect.height });
	sf::RenderStates renderStates(sfmlTransform);
	copyBlendAndShaderToSfml(&renderStates, renderInfo);
	this->data->window->draw(sprite, renderStates);
}

void GRenderEngine::doBatchDrawTexture(const std::shared_ptr<GImageData> & texture, const GRect & rect, const GTransform & transform, const GRenderInfo * renderInfo)
{
	const sf::Transform & sfmlTransform = transform.getSfmlTransform();

	this->data->batchDrawRenderInfo = *renderInfo;
	this->data->batchDrawImageData = texture;

	sf::VertexArray & vertexArray = this->data->batchDrawVertexArray;
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

void GRenderEngine::doFitView()
{
	const GConfigInfo & configInfo = GApplication::getInstance()->getConfigInfo();

	switch(configInfo.viewFitStrategy) {
	case GViewFitStrategy::scaleFit: {
		this->data->view.reset(sf::FloatRect(0, 0, configInfo.viewSize.width, configInfo.viewSize.height));
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
		this->data->view.setViewport(sf::FloatRect(viewportX, viewportY, 1.0f - viewportX * 2.0f, 1.0f - viewportY * 2.0f));
	}
		break;

	case GViewFitStrategy::fitWindow:
		this->data->view.reset(sf::FloatRect(0, 0, this->windowSize.width, this->windowSize.height));
		this->data->view.setViewport(sf::FloatRect(0, 0, 1, 1));
		break;

	case GViewFitStrategy::stretch:
		this->data->view.reset(sf::FloatRect(0, 0, configInfo.viewSize.width, configInfo.viewSize.height));
		this->data->view.setViewport(sf::FloatRect(0, 0, 1, 1));
		break;
	}

	this->data->window->setView(this->data->view);
}

} //namespace gincu
