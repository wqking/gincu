#ifndef GSCENEMANAGER_H
#define GSCENEMANAGER_H

#include <memory>

namespace gincu {

class GScene;
struct GTouchEvent;

class GSceneManager
{
public:
	GSceneManager();
	~GSceneManager();

	void switchScene(GScene * scene);

	void handleTouchEvent(const GTouchEvent & touchEvent);

	GScene * getCurrentScene() const { return currentScene.get(); }

private:
	void doSwitchScene(GScene * scene);
	void onUpdate();

private:
	void render();

private:
	std::unique_ptr<GScene> currentScene;
	std::unique_ptr<GScene> sceneToSwitchTo;
};


} //namespace gincu

#endif
