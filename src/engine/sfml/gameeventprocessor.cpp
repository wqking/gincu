#include "engine/gameeventprocessor.h"
#include "engine/touchevent.h"
#include "engine/renderengine.h"
#include "engine/sfml/renderengineresource.h"
#include "framework/gameapplication.h"
#include "framework/scenemanager.h"

#include <SFML/Window.hpp>

namespace gincu {

GameEventProcessor::GameEventProcessor(GameApplication * application)
	: application(application)
{
}
	
void GameEventProcessor::processEvents()
{
	sf::Event e;

	while(RenderEngine::getInstance()->getResource()->window->pollEvent(e)) {
		switch(e.type) {
		case sf::Event::Closed:
			this->application->finish();
			return;

		case sf::Event::MouseButtonPressed:
		case sf::Event::MouseButtonReleased: {
			TouchEvent touchEvent = TouchEvent();
			touchEvent.type = (e.type == sf::Event::MouseButtonPressed ? TouchEventType::eventPressed : TouchEventType::eventReleased);
			touchEvent.down = (e.type == sf::Event::MouseButtonPressed);
			touchEvent.position = RenderEngine::getInstance()->mapWindowToView({(CoordType)e.mouseButton.x, (CoordType)e.mouseButton.y});
			this->application->getSceneManager()->handleTouchEvent(touchEvent);
			break;
		}

		case sf::Event::MouseMoved: {
			TouchEvent touchEvent = TouchEvent();
			touchEvent.type = TouchEventType::eventMoved;
			touchEvent.down = sf::Mouse::isButtonPressed(sf::Mouse::Left);
			touchEvent.position = RenderEngine::getInstance()->mapWindowToView({(CoordType)e.mouseMove.x, (CoordType)e.mouseMove.y});
			touchEvent.deltaPosition.x = 0;
			touchEvent.deltaPosition.y = 0;
			this->application->getSceneManager()->handleTouchEvent(touchEvent);
			break;
		}
		
		case sf::Event::TouchBegan:
		case sf::Event::TouchEnded: {
			if(e.touch.finger == 0) {
				TouchEvent touchEvent = TouchEvent();
				touchEvent.type = (e.type == sf::Event::TouchBegan ? TouchEventType::eventPressed : TouchEventType::eventReleased);
				touchEvent.down = (e.type == sf::Event::TouchBegan);
				touchEvent.position = RenderEngine::getInstance()->mapWindowToView({(CoordType)e.touch.x, (CoordType)e.touch.y});
				this->application->getSceneManager()->handleTouchEvent(touchEvent);
			}

			break;
		}

		case sf::Event::TouchMoved: {
			TouchEvent touchEvent = TouchEvent();
			touchEvent.type = TouchEventType::eventMoved;
			touchEvent.down = true;
			touchEvent.position = RenderEngine::getInstance()->mapWindowToView({(CoordType)e.touch.x, (CoordType)e.touch.y});
			touchEvent.deltaPosition.x = 0;
			touchEvent.deltaPosition.y = 0;
			this->application->getSceneManager()->handleTouchEvent(touchEvent);
			break;
		}

		case sf::Event::Resized: {
			RenderEngine::getInstance()->onWindowResized(GameSize{ (CoordType)e.size.width, (CoordType)e.size.height });
			break;
		}

		default:
			break;
		}
	}
}


} //namespace gincu
