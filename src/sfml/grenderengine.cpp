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
	this->doDrawTexture(image.getData().get(), image.getRect(), transform, renderInfo);
}

void GRenderEngine::draw(const GSpriteSheetRender & spriteSheetRender, const GTransform & transform, const GRenderInfo * renderInfo)
{
	this->doDrawTexture(spriteSheetRender.getSpriteSheet().getImageData().get(), spriteSheetRender.getRect(), transform, renderInfo);
}

void GRenderEngine::draw(const GTextRender & text, const GTransform & transform, const GRenderInfo * renderInfo)
{
	sf::RenderStates renderStates(transform.getSfmlTransform());
	copyBlendAndShaderToSfml(&renderStates, renderInfo);
	this->data->window->draw(text.getData()->text, renderStates);
}

void GRenderEngine::draw(const GRectRender & rect, const GTransform & transform, const GRenderInfo * renderInfo)
{
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
	if(this->data->batchDrawRenderInfo.texture != nullptr && this->data->inBatchDraw) {
		sf::RenderStates renderStates(&this->data->batchDrawRenderInfo.texture->texture);
		copyBlendAndShaderToSfml(&renderStates, &this->data->batchDrawRenderInfo);
		this->data->window->draw(this->data->batchDrawVertexArray, renderStates);
	}

	this->data->clearBatchDrawState();
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

void GRenderEngine::doDrawTexture(const GImageData * texture, const GRect & rect, const GTransform & transform, const GRenderInfo * renderInfo)
{
	if(texture != nullptr) {
		const sf::Transform & sfmlTransform = transform.getSfmlTransform();
		if(! this->data->inBatchDraw) {
			sf::Sprite sprite(texture->texture, { (int)rect.x, (int)rect.y, (int)rect.width, (int)rect.height });
			sf::RenderStates renderStates(sfmlTransform);
			copyBlendAndShaderToSfml(&renderStates, renderInfo);
			this->data->window->draw(sprite, renderStates);
		}
		else {
			this->data->batchDrawRenderInfo = *renderInfo;
			this->data->batchDrawRenderInfo.texture = texture;

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
	}
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
