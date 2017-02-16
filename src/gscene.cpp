#include "gincu/gscene.h"
#include "gincu/gentity.h"
#include "gincu/gcomponenttouchhandler.h"
#include "gincu/gcomponenttransform.h"
#include "gincu/gcomponentcamera.h"
#include "gincu/gapplication.h"
#include "gincu/gscenemanager.h"
#include "gincu/gcomponentmanager.h"
#include "gincu/gevent.h"

#include "gincu/gcomponentanchor.h" // for test

namespace gincu {

GScene::GScene()
	: 
		componentManager(new GComponentManager()),
		primaryCamera(nullptr),
		touchCapture(nullptr)
{
}

GScene::~GScene()
{
}

void GScene::initializePrimaryCamera()
{
	if(this->primaryCamera != nullptr) {
		this->removeEntity(this->primaryCamera->getEntity());
	}

	GEntity * cameraEntity = new GEntity();
	cameraEntity->addComponent(createComponent<GComponentTransform>());
	cameraEntity->addComponent((this->primaryCamera = createComponent<GComponentCamera>()
		->setFitStrategy(GCameraFitStrategy::scaleFitFullScreen)
	));
//cameraEntity->addComponent(createComponent<GComponentAnchor>(GRenderAnchor::leftTop)->setFlipX(true)->setFlipY(true));
	this->addEntity(cameraEntity);
}

void GScene::onEnter()
{
	this->initializePrimaryCamera();

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

	this->componentManager->updateDuringRender();
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
	std::vector<GTouchHandlerFindResult> handlerList;

	this->componentManager->findTouchHandlers(&handlerList, touchEvent.touch.screenPosition);

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
			tempEvent.touch.touchedEntity = it->handler->getEntity();
			tempEvent.touch.worldPosition = it->worldPosition;
			if(this->touchCapture == nullptr) {
				tempEvent.touch.target = tempEvent.touch.touchedEntity;
				it->handler->handle(tempEvent);
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
		entity->setComponentManager(this->componentManager.get());
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
	this->componentManager->clear();
	this->entityList.clear();
	this->touchCapture = nullptr;
	this->tweenList.clear();
}


cpgf::GTweenList * getTweenListFromScene()
{
	return GApplication::getInstance()->getSceneManager()->getCurrentScene()->getTweenList();
}


} //namespace gincu
