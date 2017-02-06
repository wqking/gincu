#include "gincu/gscene.h"
#include "gincu/gentity.h"
#include "gincu/gcomponenttouchhandler.h"

namespace gincu {

Scene::Scene()
	: touchCapture(nullptr)
{
}

Scene::~Scene()
{
}

void Scene::onEnter()
{
	this->doOnEnter();
}

void Scene::onExit()
{
	this->doOnExit();

	this->entityList.clear();
}

void Scene::doOnEnter()
{
}

void Scene::doOnExit()
{
}

void Scene::renderScene()
{
	this->componentsBuffer.updateLocalTransforms();
	this->componentsBuffer.render();
}

void Scene::setTouchCapture(Entity * touchCapture)
{
	this->touchCapture = touchCapture;
	if(this->touchCapture != nullptr && this->touchCapture->getComponentByType<ComponentTouchHandler>() == nullptr) {
		this->touchCapture = nullptr;
	}
}

Entity * Scene::getTouchCapture() const
{
	return touchCapture;
}

void Scene::handleTouchEvent(const TouchEvent & touchEvent)
{
	std::vector<ComponentTouchHandler *> handlerList;

	this->componentsBuffer.findTouchHandlers(touchEvent.position, &handlerList);

	TouchEvent tempEvent = touchEvent;

	if(handlerList.empty()) {
		if(this->touchCapture != nullptr) {
			tempEvent.touchedEntity = nullptr;
			tempEvent.target = this->touchCapture;
			this->touchCapture->getComponentByType<ComponentTouchHandler>()->handle(tempEvent);
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
				this->touchCapture->getComponentByType<ComponentTouchHandler>()->handle(tempEvent);
			}
		}
	}
}

Entity * Scene::addEntity(Entity * entity)
{
	if(entity != nullptr) {
		this->entityList.push_back(EntityPointer(entity));
		entity->setComponentsBuffer(&this->componentsBuffer);
	}

	return entity;
}

void Scene::removeEntity(Entity * entity)
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


} //namespace gincu
