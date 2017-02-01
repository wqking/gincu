#include "framework/scenemanager.h"
#include "framework/scene.h"
#include "engine/renderengine.h"
#include "framework/gameapplication.h"
#include "framework/memorypool.h"

namespace gincu {

SceneManager::SceneManager()
{
	GameApplication::getInstance()->getRenderEngine()->appendRenderable(this);
}

SceneManager::~SceneManager()
{
	GameApplication::getInstance()->getRenderEngine()->removeRenderable(this);
}

void SceneManager::switchScene(Scene * scene)
{
	this->sceneToSwitchTo.reset(scene);

	GameApplication::getInstance()->addUpdater(cpgf::makeCallback(this, &SceneManager::onUpdate));
}

void SceneManager::doSwitchScene(Scene * scene)
{
	if(this->currentScene) {
		this->currentScene->onExit();
	}

	this->currentScene.reset();
	MemoryPool::getInstance()->sceneFreed();
	this->currentScene.reset(scene);

	if(this->currentScene) {
		this->currentScene->onEnter();
		
		MemoryPool::getInstance()->sceneSwitched();
	}
}

void SceneManager::render()
{
	if(this->currentScene) {
		this->currentScene->renderScene();
	}
}

void SceneManager::handleTouchEvent(const TouchEvent & touchEvent)
{
	if(this->currentScene) {
		this->currentScene->handleTouchEvent(touchEvent);
	}
}

void SceneManager::onUpdate()
{
	GameApplication::getInstance()->removeUpdater(cpgf::makeCallback(this, &SceneManager::onUpdate));

	if(this->sceneToSwitchTo) {
		this->doSwitchScene(this->sceneToSwitchTo.release());
	}
}


} //namespace gincu
