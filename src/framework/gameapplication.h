#ifndef GAMEAPPLICATION_H
#define GAMEAPPLICATION_H

#include "engine/geometry.h"
#include "cpgf/gcallbacklist.h"

#include <memory>

namespace gincu {

class RenderEngine;
class ResourceManager;
class SceneManager;
class GameEventProcessor;
class MemoryPool;

typedef cpgf::GCallback<void ()> FrameUpdater;

class GameApplication
{
public:
	static GameApplication * getInstance();

public:
	GameApplication();
	virtual ~GameApplication();

	void run();
	
	void finish();

	void addUpdater(const FrameUpdater & updater);
	void removeUpdater(const FrameUpdater & updater);

	const GameSize & getViewSize() const { return this->viewSize; }

	RenderEngine * getRenderEngine() const { return this->renderEngine.get(); }
	ResourceManager * getResourceManager() const { return this->resourceManager.get(); }
	SceneManager * getSceneManager() const { return this->sceneManager.get(); }

protected:
	void setViewSize(const GameSize & viewSize) { this->viewSize = viewSize; }
	void setFramesPerSecond(const int framesPerSecond) { this->framesPerSecond = framesPerSecond; }

private:
	void initialize();
	void finalize();
	void processMainLoop();

private:
	virtual void doInitialize();
	virtual void doFinalize();

private:
	GameSize viewSize;
	int framesPerSecond;

	std::unique_ptr<RenderEngine> renderEngine;
	std::unique_ptr<ResourceManager> resourceManager;
	std::unique_ptr<SceneManager> sceneManager;
	std::unique_ptr<GameEventProcessor> eventProcessor;

	bool finished;

	cpgf::GCallbackList<void ()> updaterList;
};


} //namespace gincu

#endif
