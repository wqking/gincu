#include "gincu/gapplication.h"
#include "gincu/grenderengine.h"
#include "gincu/gresourcemanager.h"
#include "gincu/geventprocessor.h"
#include "gincu/gscenemanager.h"
#include "gincu/gheappool.h"
#include "gincu/gutil.h"

#include "cpgf/tween/gtweenlist.h"

#include <chrono>
#include <thread>
#include <iostream>

namespace gincu {

namespace {
	GApplication * instance = nullptr;
}

GApplication * GApplication::getInstance()
{
	return instance;
}

GApplication::GApplication()
	:
		finished(false)
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
	this->renderEngine.reset(new GRenderEngine());
	this->renderEngine->inititialize();

	this->resourceManager.reset(new GResourceManager());

	this->sceneManager.reset(new GSceneManager());
	
	this->eventProcessor.reset(new GEventProcessor(this));
	
	this->doInitialize();
}

void GApplication::finalize()
{
	this->doFinalize();
}

void GApplication::processMainLoop()
{
	const unsigned int millisecondsPerFrame = 1000 / this->configInfo.framesPerSecond;
	const unsigned int millisecondsPerRenderFrame = 1000 / this->configInfo.renderFramesPerSecond;

	unsigned int lastTweenTime = getMilliseconds();
	unsigned int lastRenderTime = 0;

//unsigned int lastFpsTime = getMilliseconds();
//int fps = 0;
//int renderFps = 0;

	while(! this->finished && this->renderEngine->isAlive()) {
		const unsigned int frameBeginTime = getMilliseconds();

		this->eventProcessor->processEvents();

		this->updaterList();

		if(this->configInfo.renderFramesPerSecond < 0
			|| getMilliseconds() - lastRenderTime >= millisecondsPerRenderFrame) {
			lastRenderTime = getMilliseconds();
			this->renderEngine->render();
//++renderFps;
		}

		const unsigned int milliseconds = getMilliseconds();
		cpgf::GTweenList::getInstance()->tick((cpgf::GTweenNumber)(milliseconds - lastTweenTime));
		lastTweenTime = milliseconds;

		if(millisecondsPerFrame > 0) {
			while(getMilliseconds() < frameBeginTime + millisecondsPerFrame - 1) {
				sleepMilliseconds(1);
			}
		}
/*
++fps;
if(getMilliseconds() - lastFpsTime >= 1000) {
	std::cout << "FPS " << fps << " Render: " << renderFps << std::endl;
	lastFpsTime = getMilliseconds();
	fps = 0;
	renderFps = 0;
}
*/
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


} //namespace gincu
