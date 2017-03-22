cpgf.import(nil, "builtin.core");
cpgf.import(nil, "builtin.debug");
ScriptScene = cpgf.cloneClass(gincu.GSceneWrapper)
print(ScriptScene.doOnEnter)
function OnEnter(me)
print(456)
end
ScriptScene.doOnEnter = OnEnter
print(ScriptScene.doOnEnter)
scriptScene = ScriptScene()

gincu.GApplication.getInstance().getSceneManager().switchScene(scriptScene)
