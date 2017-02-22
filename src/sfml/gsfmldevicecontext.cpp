#include "gincu/gdevicecontext.h"
#include "gincu/gevent.h"
#include "gincu/glog.h"
#include "gincu/gconfiginfo.h"

#include "gsfmlrendercontext.h"

#include "cpgf/goutmain.h"

#include <SFML/Graphics.hpp>

#include <memory>

namespace gincu {

class GSfmlDeviceContext : public GDeviceContext
{
private:
	virtual void initialize(const GConfigInfo & configInfo) override;
	virtual void finalize() override;
	virtual GRenderContext * getRenderContext() const override;
	virtual bool getEvent(GEvent * event) const override;
	virtual bool isFinished() const override;
	
private:
	std::unique_ptr<sf::RenderWindow> window;
	std::unique_ptr<GSfmlRenderContext> renderContext;
};

void GSfmlDeviceContext::initialize(const GConfigInfo & configInfo)
{
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

	this->window.reset(new sf::RenderWindow(
		sf::VideoMode((int)configInfo.windowSize.width, (int)configInfo.windowSize.height),
		configInfo.caption,
		flags
	));

	G_LOG_INFO("Render window is created.");
	
	this->renderContext.reset(new GSfmlRenderContext());
	this->renderContext->initialize(this->window.get());
}

void GSfmlDeviceContext::finalize()
{
	this->renderContext->finalize();
}

GRenderContext * GSfmlDeviceContext::getRenderContext() const
{
	return this->renderContext.get();
}

bool GSfmlDeviceContext::getEvent(GEvent * event) const
{
	sf::Event e;

	if(! this->window->pollEvent(e)) {
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

bool GSfmlDeviceContext::isFinished() const
{
	return ! this->window->isOpen();
}

G_AUTO_RUN_BEFORE_MAIN(GSfmlDeviceContext)
{
	GDeviceContextRegister::getInstance()->registerObject(
		"sfml",
		&objectFactoryCreator<GSfmlDeviceContext>
	);
}



} //namespace gincu