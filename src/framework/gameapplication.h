#ifndef GAMEAPPLICATION_H
#define GAMEAPPLICATION_H

#include "engine/geometry.h"
#include "cpgf/gcallbacklist.h"

#include <memory>
#include <string>

namespace gincu {

class RenderEngine;
class ResourceManager;
class SceneManager;
class GameEventProcessor;
class MemoryPool;

typedef cpgf::GCallback<void ()> FrameUpdater;

struct GameWindowInfo
{
	std::string caption;
	int framesPerSecond;
	GameSize windowSize; // the window size
	GameSize viewSize; // the virtual view size, no matter how the window resized
	bool fullScreenMode;
	bool resizable;
};

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

	const GameWindowInfo & getWindowInfo() const { return this->windowInfo; }
	const GameSize & getViewSize() const { return this->windowInfo.viewSize; }

	RenderEngine * getRenderEngine() const { return this->renderEngine.get(); }
	ResourceManager * getResourceManager() const { return this->resourceManager.get(); }
	SceneManager * getSceneManager() const { return this->sceneManager.get(); }

protected:
	void setWindowInfo(const GameWindowInfo & windowInfo) { this->windowInfo = windowInfo; }

private:
	void initialize();
	void finalize();
	void processMainLoop();

private:
	virtual void doInitialize();
	virtual void doFinalize();

private:
	GameWindowInfo windowInfo;

	std::unique_ptr<RenderEngine> renderEngine;
	std::unique_ptr<ResourceManager> resourceManager;
	std::unique_ptr<SceneManager> sceneManager;
	std::unique_ptr<GameEventProcessor> eventProcessor;

	bool finished;

	cpgf::GCallbackList<void ()> updaterList;
};


} //namespace gincu

#endif
