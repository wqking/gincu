#include "mainapplication.h"
#include "gincu/gscenemanager.h"
#include "gincu/gresourcemanager.h"
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
			0xffeeeeee
		}
	);
}

MainApplication::~MainApplication()
{
}

void MainApplication::doInitialize()
{
	GResourceManager::getInstance()->setDefaultFontName(fontName);

	this->getSceneManager()->switchScene(new SceneLogo(true));
}

void MainApplication::doFinalize()
{
}


} //namespace gincu
