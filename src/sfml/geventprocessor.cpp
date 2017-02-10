#include "gincu/geventprocessor.h"
#include "gincu/gtouchevent.h"
#include "gincu/grenderengine.h"
#include "gincu/gapplication.h"
#include "gincu/gscenemanager.h"
#include "grenderenginedata.h"

#include <SFML/Window.hpp>

namespace gincu {

GEventProcessor::GEventProcessor(GApplication * application)
	: application(application)
{
}
	
void GEventProcessor::processEvents()
{
	sf::Event e;

	while(GRenderEngine::getInstance()->getData()->window->pollEvent(e)) {
		switch(e.type) {
		case sf::Event::Closed:
			this->application->finish();
			return;

		case sf::Event::MouseButtonPressed:
		case sf::Event::MouseButtonReleased: {
			GTouchEvent touchEvent = GTouchEvent();
			touchEvent.type = (e.type == sf::Event::MouseButtonPressed ? GTouchEventType::eventPressed : GTouchEventType::eventReleased);
			touchEvent.down = (e.type == sf::Event::MouseButtonPressed);
			touchEvent.position = GRenderEngine::getInstance()->mapWindowToView({(GCoord)e.mouseButton.x, (GCoord)e.mouseButton.y});
			this->application->getSceneManager()->handleTouchEvent(touchEvent);
			break;
		}

		case sf::Event::MouseMoved: {
			GTouchEvent touchEvent = GTouchEvent();
			touchEvent.type = GTouchEventType::eventMoved;
			touchEvent.down = sf::Mouse::isButtonPressed(sf::Mouse::Left);
			touchEvent.position = GRenderEngine::getInstance()->mapWindowToView({(GCoord)e.mouseMove.x, (GCoord)e.mouseMove.y});
			touchEvent.deltaPosition.x = 0;
			touchEvent.deltaPosition.y = 0;
			this->application->getSceneManager()->handleTouchEvent(touchEvent);
			break;
		}
		
		case sf::Event::TouchBegan:
		case sf::Event::TouchEnded: {
			if(e.touch.finger == 0) {
				GTouchEvent touchEvent = GTouchEvent();
				touchEvent.type = (e.type == sf::Event::TouchBegan ? GTouchEventType::eventPressed : GTouchEventType::eventReleased);
				touchEvent.down = (e.type == sf::Event::TouchBegan);
				touchEvent.position = GRenderEngine::getInstance()->mapWindowToView({(GCoord)e.touch.x, (GCoord)e.touch.y});
				this->application->getSceneManager()->handleTouchEvent(touchEvent);
			}

			break;
		}

		case sf::Event::TouchMoved: {
			GTouchEvent touchEvent = GTouchEvent();
			touchEvent.type = GTouchEventType::eventMoved;
			touchEvent.down = true;
			touchEvent.position = GRenderEngine::getInstance()->mapWindowToView({(GCoord)e.touch.x, (GCoord)e.touch.y});
			touchEvent.deltaPosition.x = 0;
			touchEvent.deltaPosition.y = 0;
			this->application->getSceneManager()->handleTouchEvent(touchEvent);
			break;
		}

		case sf::Event::Resized: {
			GRenderEngine::getInstance()->onWindowResized(GSize{ (GCoord)e.size.width, (GCoord)e.size.height });
			break;
		}

		default:
			break;
		}
	}
}


} //namespace gincu
