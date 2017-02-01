#include "mainapplication.h"
#include "framework/scenemanager.h"
#include "scenelogo.h"
#include "scenemenu.h"
#include "constants.h"

namespace gincu {

MainApplication * MainApplication::getInstance()
{
	return static_cast<MainApplication *>(super::getInstance());
}

MainApplication::MainApplication()
{
	this->setViewSize(GameSize{ (CoordType)gameViewWidth, (CoordType)gameViewHeight });
	this->setFramesPerSecond(gameFramesPerSecond);
}

MainApplication::~MainApplication()
{
}

void MainApplication::doInitialize()
{
	this->getSceneManager()->switchScene(new SceneLogo(true));
}

void MainApplication::doFinalize()
{
}


} //namespace gincu
