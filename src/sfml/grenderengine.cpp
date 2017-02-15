#include "gincu/grenderengine.h"
#include "gincu/gtransform.h"
#include "gincu/gimage.h"
#include "gincu/gatlasrender.h"
#include "gincu/gtextrender.h"
#include "gincu/grectrender.h"
#include "gincu/gapplication.h"
#include "gincu/grenderinfo.h"
#include "gincu/gevent.h"
#include "gsfmlutil.h"
#include "gimagedata.h"
#include "gtextrenderdata.h"
#include "grectrenderdata.h"
#include "grenderenginedata.h"

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
	
	this->doInitialize();
}

bool GRenderEngine::peekEvent(GEvent * event)
{
	sf::Event e;

	if(! GRenderEngine::getInstance()->getData()->window->pollEvent(e)) {
		return false;
	}

	switch(e.type) {
	case sf::Event::Closed:
		event->type = GEventType::windowClosed;
		break;

	case sf::Event::MouseButtonPressed:
	case sf::Event::MouseButtonReleased: {
		event->touch = GTouchEvent();
		event->type = (e.type == sf::Event::MouseButtonPressed ? GEventType::touchPressed : GEventType::touchReleased);
		event->touch.down = (e.type == sf::Event::MouseButtonPressed);
		event->touch.position = {(GCoord)e.mouseButton.x, (GCoord)e.mouseButton.y};
		break;
	}

	case sf::Event::MouseMoved: {
		event->touch = GTouchEvent();
		event->type = GEventType::touchMoved;
		event->touch.down = sf::Mouse::isButtonPressed(sf::Mouse::Left);
		event->touch.position = {(GCoord)e.mouseMove.x, (GCoord)e.mouseMove.y};
		break;
	}

	case sf::Event::TouchBegan:
	case sf::Event::TouchEnded: {
		event->touch = GTouchEvent();
		event->type = (e.type == sf::Event::TouchBegan ? GEventType::touchPressed : GEventType::touchReleased);
		event->touch.finger = e.touch.finger;
		event->touch.down = (e.type == sf::Event::TouchBegan);
		event->touch.position = {(GCoord)e.touch.x, (GCoord)e.touch.y};

		break;
	}

	case sf::Event::TouchMoved: {
		event->touch = GTouchEvent();
		event->type = GEventType::touchMoved;
		event->touch.down = true;
		event->touch.position = {(GCoord)e.touch.x, (GCoord)e.touch.y};
		break;
	}

	case sf::Event::Resized: {
		event->type = GEventType::windowResized;
		event->resize = GResizeEvent{ (GCoord)e.size.width, (GCoord)e.size.height };
		break;
	}

	default:
		break;
	}

	return true;
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

void GRenderEngine::draw(const GImage & image, const GMatrix44 & matrix, const GRenderInfo * renderInfo)
{
	this->doDrawTexture(image.getData(), image.getRect(), matrix, renderInfo);
}

void GRenderEngine::draw(const GAtlasRender & atlasRender, const GMatrix44 & matrix, const GRenderInfo * renderInfo)
{
	this->doDrawTexture(atlasRender.getAtlas().getImageData(), atlasRender.getRect(), matrix, renderInfo);
}

void GRenderEngine::onWindowResized(const GSize & newSize)
{
	this->windowSize = newSize;
	this->doFitView();
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

#if GINCU_MULTI_THREAD_RENDER
#include "grenderenginemultithread.hxx"
#else
#include "grenderenginesinglethread.hxx"
#endif

