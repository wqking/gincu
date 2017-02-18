#include "gincu/gscenemanager.h"
#include "gincu/gscene.h"
#include "gincu/grenderengine.h"
#include "gincu/gapplication.h"
#include "gincu/gheappool.h"
#include "gincu/gevent.h"
#include "gincu/geventqueue.h"

namespace gincu {

GSceneManager::GSceneManager()
	: keepCurrentScene(false)
{
}

GSceneManager::~GSceneManager()
{
}

void GSceneManager::initialize()
{
}

void GSceneManager::finalize()
{
	this->doSwitchScene(nullptr, false);
}

void GSceneManager::switchScene(GScene * scene)
{
	this->sceneToSwitchTo.reset(scene);

	GApplication::getInstance()->addUpdater(cpgf::makeCallback(this, &GSceneManager::lazySwitchScene));
}

void GSceneManager::switchScene(const std::string & sceneName, const SceneCreator & creator)
{
	if(sceneName.empty()) {
		this->switchScene(creator());
	}
	else {
		this->sceneNameToSwitchTo = sceneName;
		this->sceneCreatorToSwitchTo = creator;

		GApplication::getInstance()->addUpdater(cpgf::makeCallback(this, &GSceneManager::lazySwitchScene));
	}
}

void GSceneManager::doSwitchScene(GScene * scene, const bool keepScene)
{
	if(this->currentScene) {
		this->currentScene->onExit();
	}

	if(this->keepCurrentScene) {
		this->currentScene.release();
	}

	this->currentScene.reset();

	if(GHeapPool::getInstance()->getPurgeStrategy() == GHeapPoolPurgeStrategy::onSceneFreed) {
		GHeapPool::getInstance()->purge();
	}

	this->currentScene.reset(scene);

	if(this->currentScene) {
		this->keepCurrentScene = keepScene;

		this->currentScene->onEnter();
		
		if(GHeapPool::getInstance()->getPurgeStrategy() == GHeapPoolPurgeStrategy::onSceneSwitched) {
			GHeapPool::getInstance()->purge();
		}
	}
}

void GSceneManager::lazySwitchScene()
{
	GApplication::getInstance()->removeUpdater(cpgf::makeCallback(this, &GSceneManager::lazySwitchScene));

	if(this->sceneToSwitchTo) {
		this->doSwitchScene(this->sceneToSwitchTo.release(), false);
	}
	else if(! this->sceneNameToSwitchTo.empty()) {
		auto it = this->sceneNameMap.find(this->sceneNameToSwitchTo);
		
		std::string tempName = this->sceneNameToSwitchTo;
		SceneCreator tempCreator = this->sceneCreatorToSwitchTo;
		this->sceneNameToSwitchTo.clear();
		this->sceneCreatorToSwitchTo = SceneCreator();
		
		if(it != this->sceneNameMap.end()) {
			this->doSwitchScene(it->second.get(), true);
		}
		else {
			GScene * scene = tempCreator();
			this->sceneNameMap.insert(std::make_pair(tempName, std::unique_ptr<GScene>(scene)));
			this->doSwitchScene(scene, true);
		}
	}
}


} //namespace gincu
