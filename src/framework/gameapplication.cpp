#include "framework/gameapplication.h"
#include "engine/renderengine.h"
#include "engine/resourcemanager.h"
#include "engine/gameeventprocessor.h"
#include "engine/engineutil.h"
#include "framework/scenemanager.h"
#include "framework/memorypool.h"
#include "framework/util.h"

#include "cpgf/tween/gtweenlist.h"

#include <chrono>
#include <thread>
#include <iostream>

namespace gincu {

namespace {
	GameApplication * instance = nullptr;
}

GameApplication * GameApplication::getInstance()
{
	return instance;
}

GameApplication::GameApplication()
	:
		viewSize{ 800, 600 },
		finished(false)
{
	instance = this;
}

GameApplication::~GameApplication()
{
}

void GameApplication::run()
{
	this->initialize();
	this->processMainLoop();
	this->finalize();
}

void GameApplication::finish()
{
	this->finished = true;
}

void GameApplication::initialize()
{
	this->renderEngine.reset(new RenderEngine());
	this->renderEngine->inititialize();

	this->resourceManager.reset(new ResourceManager());

	this->sceneManager.reset(new SceneManager());
	
	this->eventProcessor.reset(new GameEventProcessor(this));
	
	this->doInitialize();
}

void GameApplication::finalize()
{
	this->doFinalize();
}

void GameApplication::processMainLoop()
{
	const int millisecondsPerFrame = 1000 / this->framesPerSecond;

	unsigned int lastTweenTime = getMilliseconds();

//unsigned int lastFpsTime = getMilliseconds();
//int fps = 0;
	while(! this->finished && this->renderEngine->isAlive()) {
		const unsigned int frameBeginTime = getMilliseconds();

		this->eventProcessor->processEvents();

		this->updaterList();

		this->renderEngine->render();

		const unsigned int milliseconds = getMilliseconds();
		cpgf::GTweenList::getInstance()->tick((cpgf::GTweenNumber)(milliseconds - lastTweenTime));
		lastTweenTime = milliseconds;

		while(getMilliseconds() < frameBeginTime + millisecondsPerFrame - 1) {
			sleepMilliseconds(1);
		}
/*
++fps;
if(getMilliseconds() - lastFpsTime >= 1000) {
	std::cout << "FPS " << fps << std::endl;
	lastFpsTime = getMilliseconds();
	fps = 0;
}
*/

	}
}

void GameApplication::addUpdater(const FrameUpdater & updater)
{
	this->updaterList.add(updater);
}

void GameApplication::removeUpdater(const FrameUpdater & updater)
{
	this->updaterList.remove(updater);
}

void GameApplication::doInitialize()
{
}

void GameApplication::doFinalize()
{
}


} //namespace gincu
