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
	this->setWindowInfo(
		{
			"Gincu",
			gameFramesPerSecond,
			{ (CoordType)gameViewWidth, (CoordType)gameViewHeight },
			{ (CoordType)gameViewWidth, (CoordType)gameViewHeight },
			false,
			true
		}
	);
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
