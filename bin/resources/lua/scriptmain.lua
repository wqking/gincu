cpgf.import(nil, "builtin.core");
cpgf.import(nil, "builtin.debug");

package.path = package.path .. ';resources/lua/?.lua'
require("port")
require("uiutil")
require("scenemain")

gincu.GApplication.getInstance().getSceneManager().switchScene(SceneMain())

