#ifndef GSCENEMANAGER_H
#define GSCENEMANAGER_H

#include "gincu/grenderable.h"

#include <memory>

namespace gincu {

class GScene;
struct GTouchEvent;

class GSceneManager : public GRenderable
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
	virtual void render() override;

private:
	std::unique_ptr<GScene> currentScene;
	std::unique_ptr<GScene> sceneToSwitchTo;
};


} //namespace gincu

#endif
