cpgf.import(nil, "builtin.core");
cpgf.import(nil, "builtin.debug");

print("Scriptmain.lua")

GPoint = gincu.GVector2

package.path = package.path .. ';resources/lua/?.lua'
scriptHome = ''

require(scriptHome .. "scriptscene")

scriptScene = ScriptScene()
gincu.GApplication.getInstance().getSceneManager().switchScene(scriptScene)

