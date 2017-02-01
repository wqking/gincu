#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include "engine/renderable.h"

#include <memory>

namespace gincu {

class Scene;
struct TouchEvent;

class SceneManager : public Renderable
{
public:
	SceneManager();
	~SceneManager();

	void switchScene(Scene * scene);

	void handleTouchEvent(const TouchEvent & touchEvent);

	Scene * getCurrentScene() const { return currentScene.get(); }

private:
	void doSwitchScene(Scene * scene);
	void onUpdate();

private:
	virtual void render() override;

private:
	std::unique_ptr<Scene> currentScene;
	std::unique_ptr<Scene> sceneToSwitchTo;
};


} //namespace gincu

#endif
