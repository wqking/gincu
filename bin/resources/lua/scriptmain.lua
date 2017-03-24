cpgf.import(nil, "builtin.core");
cpgf.import(nil, "builtin.debug");

GPoint = gincu.GVector2

local pos = GPoint()
pos.x = 3
pos.y = 8
-- t = gincu.GComponentTransform(pos)
-- doTest(t)
-- print("\n")

backgroundImageName = "matchthree/background.png"

ScriptScene = cpgf.cloneClass(gincu.GSceneWrapper)

function onTouched(e)
	print("Clicked yyyyyyyyyyyyyyy")
end

ScriptScene.doOnEnter = function(me)
	local pos = gincu.GVector2()
	pos.x = 100
	pos.y = 100
	entity = gincu.GEntity()
	entity.addComponent(gincu.createAndLoadImageComponent(backgroundImageName))
	entity.addComponent(gincu.GComponentTransform(pos))
	entity.addComponent(gincu.GComponentRendererTouchHandler().addOnTouch(createOnTouchedCallback(onTouched)))
	me.addEntity(entity)

--	local t = entity.getComponentByTypeId(1)
--	t = cpgf.cast(t, gincu.GComponentTransform)
--	doTest(t)
end

scriptScene = ScriptScene()

gincu.GApplication.getInstance().getSceneManager().switchScene(scriptScene)
