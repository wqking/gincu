#include "gincu/gapplication.h"
#include "gincu/gdevicecontext.h"
#include "gincu/grendercontext.h"
#include "gincu/gresourcemanager.h"
#include "gincu/gscenemanager.h"
#include "gincu/gevent.h"
#include "gincu/geventqueue.h"
#include "gincu/gutil.h"
#include "gincu/glog.h"
#include "gworker.h"

#include "cpgf/tween/gtweenlist.h"

#include <vector>
#include <chrono>
#include <thread>

namespace gincu {

namespace {

GApplication * instance = nullptr;

const std::vector<GEventType> interestedEventTypes {
	GEventType::execute,
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
		deviceContext(),
		renderContext(),
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
	G_LOG_INFO("Application start initialization");

	this->eventQueue.reset(new GEventQueue());

	this->resourceManager.reset(new GResourceManager());

	this->sceneManager.reset(new GSceneManager());

	this->eventQueue->addListeners(interestedEventTypes.begin(), interestedEventTypes.end(), cpgf::makeCallback(this, &GApplication::onEvent));
	
	std::string engineName = this->configInfo.engine;
	if(engineName.empty()) {
		engineName = GDeviceContextRegister::getInstance()->getNameList().front();
	}
	this->deviceContext.reset(GDeviceContextRegister::getInstance()->createObject(engineName));
	this->deviceContext->initialize(this->configInfo);
	this->renderContext = this->deviceContext->getRenderContext();
	this->renderContext->setBackgroundColor(this->configInfo.backgroundColor);

	this->resourceManager->initialize();
	this->sceneManager->initialize();

	this->doInitialize();

	G_LOG_INFO("Application finished initialization");
}

void GApplication::finalize()
{
	this->eventQueue->removeListeners(interestedEventTypes.begin(), interestedEventTypes.end(), cpgf::makeCallback(this, &GApplication::onEvent));
	
	this->resourceManager->finalize();
	this->sceneManager->finalize();
	this->deviceContext->finalize();

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

	const GEvent updateEvent(GEventType::update);
	auto renderCallback = cpgf::makeCallback(this, &GApplication::doRender);

	while(! this->finished && ! this->deviceContext->isFinished()) {
		++this->frameCount;

		const unsigned int frameBeginTime = getMilliseconds();

		this->processEvents();

		cpgf::GTweenList::getInstance()->tick((cpgf::GTweenNumber)this->frameMilliseconds);

		this->eventQueue->dispatch(updateEvent);

		if(this->configInfo.renderFramesPerSecond <= 0
			|| getMilliseconds() - lastRenderTime >= millisecondsPerRenderFrame) {
			milliseconds = getMilliseconds();
			this->renderMilliseconds = milliseconds - lastRenderTime;
			lastRenderTime = milliseconds;;

			this->renderContext->render(renderCallback);
			
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
	while(this->deviceContext->getEvent(&event)) {
		this->eventQueue->enqueue(event);
	}

	GEventQueue::dispatchAll();
}

void GApplication::onEvent(const GEvent & event)
{
	switch(event.getType()) {
	case GEventType::execute: {
		auto callback = event.getCallback();
		if(! callback.empty()) {
			callback();
		}
	}
		break;

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

void GApplication::doRender(GRenderContext * renderContext)
{
	this->eventQueue->dispatch(GEvent(GEventType::render, renderContext));
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

void GApplication::executeWorkerTask(const cpgf::GCallback<void ()> & task)
{
	if(! this->worker) {
		this->worker.reset(new GWorker());
	}

	this->worker->addTask(task);
}


} //namespace gincu
