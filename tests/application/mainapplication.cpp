#include "mainapplication.h"
#include "gincu/gscenemanager.h"
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
			gameRenderFramesPerSecond,
			{ (GCoord)gameViewWidth, (GCoord)gameViewHeight },
			{ (GCoord)gameViewWidth, (GCoord)gameViewHeight },
			false,
			true,
			GViewFitStrategy::scaleFit,
			0xffeeeeee
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
