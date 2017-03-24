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

function createButton(text, pos, onClick)
	local size = gincu.GSize();
	size.width = 100;
	size.height = 40;
	return gincu.GEntity()
		.addComponent(gincu.GComponentTransform(pos))
		.addComponent(gincu.GComponentAnchor(gincu.GRenderAnchor.center))
		.addComponent(gincu.GComponentContainerRender()
			.add(gincu.createRectRenderComponent(0xffeeee77, size))
			.add(gincu.createAndLoadTextComponent(text, 0xff0000ff, 16))
		)
		.addComponent(gincu.GComponentRendererTouchHandler().addOnTouch(createOnTouchedCallback(onClick)))
end

ScriptScene.doOnEnter = function(me)
	local pos = gincu.GVector2()
	pos.x = 100
	pos.y = 100
	me.addEntity(
		gincu.GEntity()
		.addComponent(gincu.createAndLoadImageComponent(backgroundImageName))
		.addComponent(gincu.GComponentTransform(pos))
	)
	
	me.addEntity(
		createButton("Back", pos, function(e)
			--if e.getType() == gincu.GEventType.touchPressed then
				print("Clicked yyyyyyyyyyyyyyy " .. e.getType())
			--end
		end)
	)

--	local t = entity.getComponentByTypeId(1)
--	t = cpgf.cast(t, gincu.GComponentTransform)
--	doTest(t)
end

scriptScene = ScriptScene()

gincu.GApplication.getInstance().getSceneManager().switchScene(scriptScene)
