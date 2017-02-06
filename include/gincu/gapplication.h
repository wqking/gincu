#ifndef GAPPLICATION_H
#define GAPPLICATION_H

#include "gincu/ggeometry.h"
#include "gincu/gconfiginfo.h"
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

	const GameConfigInfo & getConfigInfo() const { return this->configInfo; }
	const GameSize & getViewSize() const { return this->configInfo.viewSize; }

	SceneManager * getSceneManager() const { return this->sceneManager.get(); }

protected:
	void setConfigInfo(const GameConfigInfo & configInfo) { this->configInfo = configInfo; }

private:
	void initialize();
	void finalize();
	void processMainLoop();

private:
	virtual void doInitialize();
	virtual void doFinalize();

private:
	GameConfigInfo configInfo;

	std::unique_ptr<RenderEngine> renderEngine;
	std::unique_ptr<ResourceManager> resourceManager;
	std::unique_ptr<SceneManager> sceneManager;
	std::unique_ptr<GameEventProcessor> eventProcessor;

	bool finished;

	cpgf::GCallbackList<void ()> updaterList;
};


} //namespace gincu

#endif
