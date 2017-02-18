#include "gincu/gscene.h"
#include "gincu/gentity.h"
#include "gincu/gcomponenttouchhandler.h"
#include "gincu/gcomponenttransform.h"
#include "gincu/gcomponentcamera.h"
#include "gincu/gapplication.h"
#include "gincu/gscenemanager.h"
#include "gincu/gcomponentmanager.h"
#include "gincu/gevent.h"
#include "gincu/geventqueue.h"

#include "gincu/gcomponentanchor.h" // for test

namespace gincu {

namespace {

const std::vector<GEventType> interestedEventTypes {
	GEventType::render,
	GEventType::touchMoved,
	GEventType::touchPressed,
	GEventType::touchReleased,
};

} //unnamed namespace

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
	GApplication::getInstance()->getEventQueue()->addListeners(interestedEventTypes.begin(), interestedEventTypes.end(), cpgf::makeCallback(this, &GScene::onEvent));

	this->doOnEnter();
}

void GScene::onExit()
{
	GApplication::getInstance()->getEventQueue()->removeListeners(interestedEventTypes.begin(), interestedEventTypes.end(), cpgf::makeCallback(this, &GScene::onEvent));

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

void GScene::onEvent(const GEvent & event)
{
	if(isTouchEvent(event.getType())) {
		this->doHandleTouchEvent(event);
	}
	else {
		if(event.getType() == GEventType::render) {
			this->tweenList.tick((cpgf::GTweenNumber)GApplication::getInstance()->getRenderMilliseconds());
			this->componentManager->updateDuringRender(event.getRenderContext());
		}
	}
	
}

void GScene::doHandleTouchEvent(const GEvent & event)
{
	std::vector<GTouchHandlerFindResult> handlerList;

	this->componentManager->findTouchHandlers(&handlerList, event.getTouch().screenPosition);

	GEvent tempEvent = event;
	GTouchEvent touchEvent = tempEvent.getTouch();

	if(handlerList.empty()) {
		if(this->touchCapture != nullptr) {
			touchEvent.touchedEntity = nullptr;
			tempEvent.setTouch(touchEvent);
			this->touchCapture->getComponentByType<GComponentTouchHandler>()->handle(tempEvent);
		}
	}
	else {
		for(auto it = handlerList.begin(); it != handlerList.end(); ++it) {
			tempEvent.setAllowPropagate(false);
			touchEvent.touchedEntity = it->handler->getEntity();
			touchEvent.worldPosition = it->worldPosition;
			if(this->touchCapture == nullptr) {
				tempEvent.setTouch(touchEvent);
				it->handler->handle(tempEvent);
			}
			else {
				tempEvent.setTouch(touchEvent);
				this->touchCapture->getComponentByType<GComponentTouchHandler>()->handle(tempEvent);
			}

			if(! tempEvent.doesAllowPropagate()) {
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


cpgf::GTweenList * getTweenListFromScene()
{
	return GApplication::getInstance()->getSceneManager()->getCurrentScene()->getTweenList();
}


} //namespace gincu
