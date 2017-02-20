#ifndef GSCENEMANAGER_H
#define GSCENEMANAGER_H

#include "cpgf/gcallback.h"

#include <memory>
#include <string>
#include <map>

namespace gincu {

class GScene;
class GEvent;
class GTransition;

class GSceneManager
{
public:
	typedef cpgf::GCallback<GScene * ()> SceneCreator;

public:
	GSceneManager();
	~GSceneManager();

	void initialize();
	void finalize();

	void switchScene(GScene * scene, GTransition * transition = nullptr);
	void switchScene(const std::string & sceneName, const SceneCreator & creator, GTransition * transition = nullptr);

	GScene * getCurrentScene() const { return currentScene.get(); }

private:
	void doTransiteScene(GScene * scene, const bool keepScene);
	void doSwitchScene(GScene * scene, const bool keepScene, const bool enterNewScene);
	void deferSwitchScene(const GEvent & event);
	void doSetTransition(GTransition * transition);

private:
	std::unique_ptr<GScene> currentScene;
	bool keepCurrentScene;
	std::map<std::string, std::unique_ptr<GScene> > sceneNameMap;
	std::unique_ptr<GScene> sceneToSwitchTo;
	std::string sceneNameToSwitchTo;
	SceneCreator sceneCreatorToSwitchTo;
	GTransition * transition;
};


} //namespace gincu

#endif
