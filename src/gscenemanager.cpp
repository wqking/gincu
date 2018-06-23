#include "gincu/gscenemanager.h"
#include "gincu/gscene.h"
#include "gincu/gapplication.h"
#include "gincu/gevent.h"
#include "gincu/geventqueue.h"
#include "gincu/transition/gtransition.h"

namespace gincu {

GSceneManager::GSceneManager()
	:
		keepCurrentScene(false),
		transition(nullptr)
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
	this->doTransiteScene(nullptr, false);
}

void GSceneManager::switchScene(GScene * scene, GTransition * transition)
{
	this->doSetTransition(transition);

	this->sceneToSwitchTo.reset(scene);

	GApplication::getInstance()->getEventQueue()->appendListener(GEventType::update, cpgf::makeCallback(this, &GSceneManager::deferSwitchScene));
}

void GSceneManager::switchScene(const std::string & sceneName, const SceneCreator & creator, GTransition * transition)
{
	if(sceneName.empty()) {
		this->switchScene(creator(), transition);
	}
	else {
		this->doSetTransition(transition);
		
		this->sceneNameToSwitchTo = sceneName;
		this->sceneCreatorToSwitchTo = creator;

		GApplication::getInstance()->getEventQueue()->appendListener(GEventType::update, cpgf::makeCallback(this, &GSceneManager::deferSwitchScene));
	}
}

void GSceneManager::doTransiteScene(GScene * scene, const bool keepScene)
{
	if(this->transition == nullptr || scene == nullptr || !this->currentScene) {
		this->doSwitchScene(scene, keepScene, true);
	}
	else {
		scene->onEnter();
		this->transition->addOnComplete([=]() {
			this->transition = nullptr;
			this->doSwitchScene(scene, keepScene, false);
		});
		this->transition->transite(this->currentScene.get(), scene);
	}
}

void GSceneManager::doSwitchScene(GScene * scene, const bool keepScene, const bool enterNewScene)
{
	if(this->currentScene) {
		this->currentScene->onExit();
	}

	if(this->keepCurrentScene) {
		this->currentScene.release();
	}

	this->currentScene.reset(scene);

	if(this->currentScene) {
		this->keepCurrentScene = keepScene;

		if(enterNewScene) {
			this->currentScene->onEnter();
		}
	}
}

void GSceneManager::deferSwitchScene(const GEvent & /*event*/)
{
	GApplication::getInstance()->getEventQueue()->removeListener(GEventType::update, cpgf::makeCallback(this, &GSceneManager::deferSwitchScene));

	if(this->sceneToSwitchTo) {
		this->doTransiteScene(this->sceneToSwitchTo.release(), false);
	}
	else if(! this->sceneNameToSwitchTo.empty()) {
		auto it = this->sceneNameMap.find(this->sceneNameToSwitchTo);
		
		std::string tempName = this->sceneNameToSwitchTo;
		SceneCreator tempCreator = this->sceneCreatorToSwitchTo;
		this->sceneNameToSwitchTo.clear();
		this->sceneCreatorToSwitchTo = SceneCreator();
		
		if(it != this->sceneNameMap.end()) {
			this->doTransiteScene(it->second.get(), true);
		}
		else {
			GScene * scene = tempCreator();
			this->sceneNameMap.insert(std::make_pair(tempName, std::unique_ptr<GScene>(scene)));
			this->doTransiteScene(scene, true);
		}
	}
}

void GSceneManager::doSetTransition(GTransition * transition)
{
	if(this->transition != transition) {
		if(this->transition != nullptr) {
			this->transition->cancel();
		}
		this->transition = transition;
	}
}


} //namespace gincu
