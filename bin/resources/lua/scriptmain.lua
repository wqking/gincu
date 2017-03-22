cpgf.import(nil, "builtin.core");
cpgf.import(nil, "builtin.debug");

backgroundImageName = "matchthree/background.png"

ScriptScene = cpgf.cloneClass(gincu.GSceneWrapper)

ScriptScene.doOnEnter = function(me)
	local pos = gincu.GVector2()
	me.addEntity(
		gincu.GEntity()
			.addComponent(gincu.GComponentTransform())
			.addComponent(gincu.createAndLoadImageComponent(backgroundImageName))
	)
end

scriptScene = ScriptScene()

gincu.GApplication.getInstance().getSceneManager().switchScene(scriptScene)
