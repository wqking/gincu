cpgf.import(nil, "builtin.core");
cpgf.import(nil, "builtin.debug");

backgroundImageName = "matchthree/background.png"

ScriptScene = cpgf.cloneClass(gincu.GSceneWrapper)

ScriptScene.doOnEnter = function(me)
	print(456)
	me.addEntity(
		createEntity()
--			.addComponent(gincu.GComponentTransform())
			.addComponent(gincu.createAndLoadImageComponent(backgroundImageName))
	)
end

scriptScene = ScriptScene()

gincu.GApplication.getInstance().getSceneManager().switchScene(scriptScene)
