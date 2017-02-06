#include "gincu/gscenemanager.h"
#include "gincu/gscene.h"
#include "gincu/grenderengine.h"
#include "gincu/gapplication.h"
#include "gincu/gheappool.h"

namespace gincu {

GSceneManager::GSceneManager()
{
	GRenderEngine::getInstance()->appendRender(cpgf::makeCallback(this, &GSceneManager::render));
}

GSceneManager::~GSceneManager()
{
	GRenderEngine::getInstance()->removeRender(cpgf::makeCallback(this, &GSceneManager::render));
}

void GSceneManager::switchScene(GScene * scene)
{
	this->sceneToSwitchTo.reset(scene);

	GApplication::getInstance()->addUpdater(cpgf::makeCallback(this, &GSceneManager::onUpdate));
}

void GSceneManager::doSwitchScene(GScene * scene)
{
	if(this->currentScene) {
		this->currentScene->onExit();
	}

	this->currentScene.reset();
	GHeapPool::getInstance()->sceneFreed();
	this->currentScene.reset(scene);

	if(this->currentScene) {
		this->currentScene->onEnter();
		
		GHeapPool::getInstance()->sceneSwitched();
	}
}

void GSceneManager::render()
{
	if(this->currentScene) {
		this->currentScene->renderScene();
	}
}

void GSceneManager::handleTouchEvent(const GTouchEvent & touchEvent)
{
	if(this->currentScene) {
		this->currentScene->handleTouchEvent(touchEvent);
	}
}

void GSceneManager::onUpdate()
{
	GApplication::getInstance()->removeUpdater(cpgf::makeCallback(this, &GSceneManager::onUpdate));

	if(this->sceneToSwitchTo) {
		this->doSwitchScene(this->sceneToSwitchTo.release());
	}
}


} //namespace gincu
