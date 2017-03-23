cpgf.import(nil, "builtin.core");
cpgf.import(nil, "builtin.debug");

local pos = gincu.GVector2()
pos.x = 3
pos.y = 8
t = gincu.GComponentTransform(pos)
-- doTest(t.getPosition())

backgroundImageName = "matchthree/background.png"

ScriptScene = cpgf.cloneClass(gincu.GSceneWrapper)

ScriptScene.doOnEnter = function(me)
	local pos = gincu.GVector2()
--	pos.x = 100
--	pos.y = 100
	entity = me.addEntity(
		gincu.GEntity()
			.addComponent(gincu.GComponentTransform())
			.addComponent(gincu.createAndLoadImageComponent(backgroundImageName))
	)

	print(cpgf.inspect(entity))
	
	--local t = entity.getComponentByTypeId(1)
	--t = cpgf.cast(t, gincu.GComponentTransform)
	--doTest(t.getPosition())
end

scriptScene = ScriptScene()

gincu.GApplication.getInstance().getSceneManager().switchScene(scriptScene)
