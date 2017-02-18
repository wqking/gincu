#include "gincu/gapplication.h"
#include "gincu/grenderengine.h"
#include "gincu/gresourcemanager.h"
#include "gincu/gscenemanager.h"
#include "gincu/gevent.h"
#include "gincu/geventqueue.h"
#include "gincu/gheappool.h"
#include "gincu/gutil.h"
#include "gincu/glog.h"

#include "cpgf/tween/gtweenlist.h"

#include <vector>
#include <chrono>
#include <thread>

namespace gincu {

namespace {

GApplication * instance = nullptr;

const std::vector<GEventType> interestedEventTypes {
	GEventType::windowClosed,
	GEventType::windowResized,
	GEventType::windowActivated,
	GEventType::windowDeactivated,
};

}

GApplication * GApplication::getInstance()
{
	return instance;
}

GApplication::GApplication()
	:
		finished(false),
		screenSize(),
		frameCount(0),
		frameRate(60),
		renderFrameRate(60),
		frameMilliseconds(1),
		renderMilliseconds(1)
{
	instance = this;
}

GApplication::~GApplication()
{
}

void GApplication::run()
{
	this->initialize();
	this->processMainLoop();
	this->finalize();
}

void GApplication::finish()
{
	this->finished = true;
}

void GApplication::initialize()
{
	this->eventQueue.reset(new GEventQueue());

	this->renderEngine.reset(new GRenderEngine());

	this->resourceManager.reset(new GResourceManager());

	this->sceneManager.reset(new GSceneManager());

	this->eventQueue->addListeners(interestedEventTypes.begin(), interestedEventTypes.end(), cpgf::makeCallback(this, &GApplication::onEvent));

	this->renderEngine->initialize();
	this->resourceManager->initialize();
	this->sceneManager->initialize();

	this->doInitialize();
}

void GApplication::finalize()
{
	this->eventQueue->removeListeners(interestedEventTypes.begin(), interestedEventTypes.end(), cpgf::makeCallback(this, &GApplication::onEvent));
	
	this->renderEngine->finalize();
	this->resourceManager->finalize();
	this->sceneManager->finalize();

	this->doFinalize();
}

void GApplication::processMainLoop()
{
	const unsigned int millisecondsPerFrame = (this->configInfo.framesPerSecond <= 0 ? 0 : 1000 / this->configInfo.framesPerSecond);
	const unsigned int millisecondsPerRenderFrame = 1000 / this->configInfo.renderFramesPerSecond;

	this->frameCount = 0;

	const unsigned int startTime = getMilliseconds();

	unsigned int lastRenderTime = 0;

	if(startTime > millisecondsPerRenderFrame + 1) {
		lastRenderTime = startTime - millisecondsPerRenderFrame - 1;
	}

	unsigned int lastFpsTime = startTime;
	int fps = 0;
	int renderFps = 0;

	unsigned int milliseconds;

	while(! this->finished && this->renderEngine->isAlive()) {
		++this->frameCount;

		const unsigned int frameBeginTime = getMilliseconds();

		this->processEvents();

		cpgf::GTweenList::getInstance()->tick((cpgf::GTweenNumber)this->frameMilliseconds);

		this->updaterList();

		if(this->configInfo.renderFramesPerSecond <= 0
			|| getMilliseconds() - lastRenderTime >= millisecondsPerRenderFrame) {
			milliseconds = getMilliseconds();
			this->renderMilliseconds = milliseconds - lastRenderTime;
			lastRenderTime = milliseconds;;

			this->renderEngine->render();
			
			++renderFps;
		}

		if(millisecondsPerFrame > 0) {
			while(getMilliseconds() < frameBeginTime + millisecondsPerFrame - 1) {
				sleepMilliseconds(1);
			}
		}

		++fps;

		milliseconds = getMilliseconds();
		this->frameMilliseconds = milliseconds - frameBeginTime;

		if(milliseconds - lastFpsTime >= 1000) {
			this->frameRate = fps;
			this->renderFrameRate = renderFps;
			lastFpsTime = milliseconds;
			fps = 0;
			renderFps = 0;

			G_LOG_VERBOSE("FPS: %d RenderFPS: %d", this->frameRate, this->renderFrameRate);
		}
	}
}

void GApplication::processEvents()
{
	GEvent event;
	while(this->renderEngine->peekEvent(&event)) {
		this->eventQueue->post(event);
	}

	GEventQueue::dispatchAll();
}

void GApplication::onEvent(const GEvent & event)
{
	switch(event.getType()) {
	case GEventType::windowClosed:
		this->finish();
		break;

	case GEventType::windowResized:
		this->screenSize = GSize{ (GCoord)event.getResize().width, (GCoord)event.getResize().height };
		break;

	case GEventType::windowActivated:
		G_LOG_INFO("Application is activated.");
//		this->resourceManager->reloadResources();
		break;

	case GEventType::windowDeactivated:
		G_LOG_INFO("Application is deactivated.");
		break;

	default:
		break;
	}
}

void GApplication::addUpdater(const FrameUpdater & updater)
{
	this->updaterList.add(updater);
}

void GApplication::removeUpdater(const FrameUpdater & updater)
{
	this->updaterList.remove(updater);
}

void GApplication::doInitialize()
{
}

void GApplication::doFinalize()
{
}

GSize GApplication::getScreenSize() const
{
	return this->screenSize;
}

void GApplication::setConfigInfo(const GConfigInfo & configInfo)
{
	this->configInfo = configInfo;
	this->screenSize = this->configInfo.windowSize;
}


} //namespace gincu
