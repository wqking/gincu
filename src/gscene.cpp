#include "gincu/gscene.h"
#include "gincu/gentity.h"
#include "gincu/gcomponenttouchhandler.h"
#include "gincu/gapplication.h"
#include "gincu/gscenemanager.h"

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

void GScene::handleTouchEvent(const GTouchEvent & touchEvent)
{
	std::vector<GComponentTouchHandler *> handlerList;

	this->componentManager.findTouchHandlers(touchEvent.position, &handlerList);

	GTouchEvent tempEvent = touchEvent;

	if(handlerList.empty()) {
		if(this->touchCapture != nullptr) {
			tempEvent.touchedEntity = nullptr;
			tempEvent.target = this->touchCapture;
			this->touchCapture->getComponentByType<GComponentTouchHandler>()->handle(tempEvent);
		}
	}
	else {
		for(auto it = handlerList.begin(); it != handlerList.end(); ++it) {
			tempEvent.touchedEntity = (*it)->getEntity();
			if(this->touchCapture == nullptr) {
				tempEvent.target = tempEvent.touchedEntity;
				(*it)->handle(tempEvent);
			}
			else {
				tempEvent.target = this->touchCapture;
				this->touchCapture->getComponentByType<GComponentTouchHandler>()->handle(tempEvent);
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

cpgf::GTweenList * getTweenListFromScene()
{
	return GApplication::getInstance()->getSceneManager()->getCurrentScene()->getTweenList();
}


} //namespace gincu
