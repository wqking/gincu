#include "mainapplication.h"
#include "gincu/gscenemanager.h"
#include "gincu/gresourcemanager.h"
#include "scenelogo.h"
#include "scenemenu.h"
#include "constants.h"

namespace gincu {

struct ConfigItem
{
	std::string engine;
	std::string fontName;
};

const ConfigItem sfmlConfig {
	"sfml",
	"arialbd.ttf"
};
const ConfigItem allegroConfig {
	"allegro",
	"fixed_font.tga"
};

const ConfigItem * config = &sfmlConfig;
//const ConfigItem * config = &allegroConfig;

MainApplication * MainApplication::getInstance()
{
	return static_cast<MainApplication *>(super::getInstance());
}

MainApplication::MainApplication()
{
	this->setConfigInfo(
		{
			config->engine,
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
	GResourceManager::getInstance()->setDefaultFontName(config->fontName);

	GResourceManager::getInstance()->asyncGetFont(GResourceManager::getInstance()->getDefaultFontName(), [=]() {
		this->getSceneManager()->switchScene(new SceneLogo(true));
	});
}

void MainApplication::doFinalize()
{
}


} //namespace gincu
