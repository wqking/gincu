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
	this->setConfigInfo(
		{
			"Gincu",
			gameFramesPerSecond,
			{ (CoordType)gameViewWidth, (CoordType)gameViewHeight },
			{ (CoordType)gameViewWidth, (CoordType)gameViewHeight },
			false,
			true,
			ViewFitStrategy::scaleFit,
			colorWhite
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
