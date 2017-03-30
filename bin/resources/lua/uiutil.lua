function createButton(text, pos, size, onClick)
	if size == nil then
		size = port.createSize(100, 40)
	end

	return gincu.GEntity()
		.addComponent(gincu.GComponentTransform(pos))
		.addComponent(gincu.GComponentAnchor(gincu.GRenderAnchor.center))
		.addComponent(gincu.GComponentContainerRender()
			.add(gincu.createRectRenderComponent(0xffeeee77, size))
			.add(gincu.createAndLoadTextComponent(text, 0xff0000ff, 16))
		)
		.addComponent(gincu.GComponentRendererTouchHandler().addOnTouch(gincu.createEventCallback(
			function(e)
				if e.getType() == gincu.GEventType.touchPressed then
					onClick(e)
				end
			end
		)))
end

function createBackButton(onClick)
	return gincu.GEntity()
		.addComponent(gincu.GComponentTransform(port.createPoint(40, 40)))
		.addComponent(gincu.GComponentAnchor(gincu.GRenderAnchor.center))
		.addComponent(gincu.createAtlasRenderComponent(gincu.GResourceManager.getInstance().getAtlas("ui_atlas", gincu.GAtlasFormat.spritePackText), "back_button"))
		.addComponent(gincu.GComponentRendererTouchHandler().addOnTouch(gincu.createEventCallback(
			function(e)
				if e.getType() == gincu.GEventType.touchPressed then
					onClick(e)
				end
			end
		)))
end

function createAnimation(atlasName)
	local data = gincu.GFrameAnimationSetData();
	gincu.buildFrameAnimationDataFromAtlas(data, gincu.GResourceManager.getInstance().getAtlas(atlasName, gincu.GAtlasFormat.spritePackText));
	local sp = gincu.createSharedPointer(data);
	local component = gincu.GComponentFrameAnimation(sp);
	component.getTween()._repeat(-1).timeScale(0.2);
	return component;
end

