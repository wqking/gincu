cpgf.import(nil, "builtin.core");
cpgf.import(nil, "builtin.debug");

package.path = package.path .. ';resources/lua/?.lua'
require("port")
require("uiutil")
require("scenemain")

currentScene = nil;

function doSwitchScene(scene)
	currentScene = scene
	gincu.GApplication.getInstance().getSceneManager().switchScene(currentScene)
end

-- gincu.GApplication.getInstance().getSceneManager().switchScene(SceneMain())
doSwitchScene(SceneMain())

