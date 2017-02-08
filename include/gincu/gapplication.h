#ifndef GAPPLICATION_H
#define GAPPLICATION_H

#include "gincu/ggeometry.h"
#include "gincu/gconfiginfo.h"

#include "cpgf/gcallbacklist.h"

#include <memory>
#include <string>
#include <cstdint>

namespace gincu {

class GRenderEngine;
class GResourceManager;
class GSceneManager;
class GEventProcessor;
class GHeapPool;

typedef cpgf::GCallback<void ()> FrameUpdater;

class GApplication
{
public:
	static GApplication * getInstance();

public:
	GApplication();
	virtual ~GApplication();

	void run();
	
	void finish();

	void addUpdater(const FrameUpdater & updater);
	void removeUpdater(const FrameUpdater & updater);

	const GConfigInfo & getConfigInfo() const { return this->configInfo; }
	const GSize & getViewSize() const { return this->configInfo.viewSize; }

	GSceneManager * getSceneManager() const { return this->sceneManager.get(); }

	int64_t getFrameCount() const { return this->frameCount; }
	int getFrameRate() const { return this->frameRate; }
	int getRenderFrameRate() const { return this->renderFrameRate; }
	unsigned int getFrameMilliseconds() const { return this->frameMilliseconds; }

protected:
	void setConfigInfo(const GConfigInfo & configInfo) { this->configInfo = configInfo; }

private:
	void initialize();
	void finalize();
	void processMainLoop();

private:
	virtual void doInitialize();
	virtual void doFinalize();

private:
	GConfigInfo configInfo;

	cpgf::GCallbackList<void ()> updaterList;

	std::unique_ptr<GRenderEngine> renderEngine;
	std::unique_ptr<GResourceManager> resourceManager;
	std::unique_ptr<GSceneManager> sceneManager;
	std::unique_ptr<GEventProcessor> eventProcessor;

	bool finished;
	int64_t frameCount;
	int frameRate;
	int renderFrameRate;
	unsigned int frameMilliseconds;
};


} //namespace gincu

#endif
