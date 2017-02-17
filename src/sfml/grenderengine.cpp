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

	this->data->window.reset(new sf::RenderWindow(
		sf::VideoMode((int)configInfo.windowSize.width, (int)configInfo.windowSize.height),
		configInfo.caption,
		flags
	));

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
		*event = GEvent(GEventType::windowClosed);
		break;

	case sf::Event::MouseButtonPressed:
	case sf::Event::MouseButtonReleased: {
		GTouchEvent touchEvent = GTouchEvent();
		touchEvent.down = (e.type == sf::Event::MouseButtonPressed);
		touchEvent.screenPosition = {(GCoord)e.mouseButton.x, (GCoord)e.mouseButton.y};
		*event = GEvent((e.type == sf::Event::MouseButtonPressed ? GEventType::touchPressed : GEventType::touchReleased), touchEvent);
	}
		break;

	case sf::Event::MouseMoved: {
		GTouchEvent touchEvent = GTouchEvent();
		touchEvent.down = sf::Mouse::isButtonPressed(sf::Mouse::Left);
		touchEvent.screenPosition = {(GCoord)e.mouseMove.x, (GCoord)e.mouseMove.y};
		*event = GEvent(GEventType::touchMoved, touchEvent);
	}
		break;

	case sf::Event::TouchBegan:
	case sf::Event::TouchEnded: {
		GTouchEvent touchEvent = GTouchEvent();
		touchEvent.finger = e.touch.finger;
		touchEvent.down = (e.type == sf::Event::TouchBegan);
		touchEvent.screenPosition = {(GCoord)e.touch.x, (GCoord)e.touch.y};
		*event = GEvent((e.type == sf::Event::TouchBegan ? GEventType::touchPressed : GEventType::touchReleased), touchEvent);
	}
		break;

	case sf::Event::TouchMoved: {
		GTouchEvent touchEvent = GTouchEvent();
		touchEvent.down = true;
		touchEvent.screenPosition = {(GCoord)e.touch.x, (GCoord)e.touch.y};
		*event = GEvent(GEventType::touchMoved, touchEvent);
	}
		break;

	case sf::Event::Resized:
		*event = GEvent(GEventType::windowResized, GResizeEvent{ (GCoord)e.size.width, (GCoord)e.size.height });
		break;

	case sf::Event::GainedFocus:
		*event = GEvent(GEventType::windowActivated);
		break;

	case sf::Event::LostFocus:
		*event = GEvent(GEventType::windowDeactivated);
		break;

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


} //namespace gincu

#if GINCU_MULTI_THREAD_RENDER
#include "grenderenginemultithread.hxx"
#else
#include "grenderenginesinglethread.hxx"
#endif

