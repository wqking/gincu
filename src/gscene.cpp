#include "gincu/gscene.h"
#include "gincu/gentity.h"
#include "gincu/gcomponenttouchhandler.h"
#include "gincu/gapplication.h"
#include "gincu/gscenemanager.h"
#include "gincu/gevent.h"

namespace gincu {

GScene::GScene()
	: touchCapture(nullptr)
{
}

GScene::~GScene()
{
}

void GScene::onEnter()
{
	this->doOnEnter();
}

void GScene::onExit()
{
	this->doOnExit();

	this->tweenList.clear();
	this->entityList.clear();
}

void GScene::doOnEnter()
{
}

void GScene::doOnExit()
{
}

void GScene::renderScene()
{
	this->tweenList.tick((cpgf::GTweenNumber)GApplication::getInstance()->getRenderMilliseconds());

	this->componentManager.updateDuringRender();
}

void GScene::setTouchCapture(GEntity * touchCapture)
{
	this->touchCapture = touchCapture;
	if(this->touchCapture != nullptr && this->touchCapture->getComponentByType<GComponentTouchHandler>() == nullptr) {
		this->touchCapture = nullptr;
	}
}

GEntity * GScene::getTouchCapture() const
{
	return touchCapture;
}

void GScene::handleTouchEvent(const GEvent & touchEvent)
{
	std::vector<GComponentTouchHandler *> handlerList;

	this->componentManager.findTouchHandlers(touchEvent.touch.position, &handlerList);

	GEvent tempEvent = touchEvent;

	if(handlerList.empty()) {
		if(this->touchCapture != nullptr) {
			tempEvent.touch.touchedEntity = nullptr;
			tempEvent.touch.target = this->touchCapture;
			this->touchCapture->getComponentByType<GComponentTouchHandler>()->handle(tempEvent);
		}
	}
	else {
		for(auto it = handlerList.begin(); it != handlerList.end(); ++it) {
			tempEvent.propagation = false;
			tempEvent.touch.touchedEntity = (*it)->getEntity();
			if(this->touchCapture == nullptr) {
				tempEvent.touch.target = tempEvent.touch.touchedEntity;
				(*it)->handle(tempEvent);
			}
			else {
				tempEvent.touch.target = this->touchCapture;
				this->touchCapture->getComponentByType<GComponentTouchHandler>()->handle(tempEvent);
			}

			if(! tempEvent.propagation) {
				break;
			}
		}
	}
}

GEntity * GScene::addEntity(GEntity * entity)
{
	if(entity != nullptr) {
		this->entityList.push_back(EntityPointer(entity));
		entity->setComponentManager(&this->componentManager);
	}

	return entity;
}

void GScene::removeEntity(GEntity * entity)
{
	if(entity == nullptr) {
		return;
	}

	for(auto it = this->entityList.begin(); it != this->entityList.end(); ++it) {
		if(it->get() == entity) {
			this->entityList.erase(it);
			break;
		}
	}
}

void GScene::removeAllEntities()
{
	this->componentManager.clear();
	this->entityList.clear();
	this->touchCapture = nullptr;
	this->tweenList.clear();
}


cpgf::GTweenList * getTweenListFromScene()
{
	return GApplication::getInstance()->getSceneManager()->getCurrentScene()->getTweenList();
}


} //namespace gincu
