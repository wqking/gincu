SceneTestSceneGraph = cpgf.cloneClass(gincu.GSceneWrapper)


local function createParentedObject(me, position, anchor, rotation, scale)
	local imageNameA = "testbed/cat.png";
	local imageNameB = "testbed/dog.png";
	local imageNameC = "testbed/pig.png";
	local imageNameD = "testbed/rabbit.png";
	local atlasName = "testbed/animation_yellow_boy";
	local x = position.x;
	local y = position.y;
	local yDelta = 150;

	local result = nil;

	local entityA = nil;
	local entityB = nil;
	local entityD = nil;

	entityA = gincu.GEntity();
	entityB = gincu.GEntity();
	result = gincu.GComponentLocalTransform(port.createPoint(x, y)).setRotation(rotation).setScale(port.createScale(scale, scale));
	me.addEntity(
		entityA
		.addComponent(gincu.GComponentTransform())
		.addComponent(result)
		.addComponent(gincu.GComponentAnchor(anchor))
		.addComponent(gincu.createAndLoadImageComponent(imageNameA))
		.addComponent(gincu.GComponentRendererTouchHandler().addOnTouch(gincu.createEventCallback(
			function(e)
				if e.getType() == gincu.GEventType.touchPressed then
					cpgf.cast(entityB.getComponentByTypeId(gincu.GComponentLocalTransform.getComponentType()))
						.setVisible(not
							cpgf.cast(entityB.getComponentByTypeId(gincu.GComponentLocalTransform.getComponentType()))
							.isVisible()
						);
				end
			end
		)))
	);

	me.addEntity(
		entityB
		.addComponent(gincu.GComponentTransform())
		.addComponent(gincu.GComponentLocalTransform(port.createPoint(0, yDelta)).setParent(entityA.getComponentByTypeId(gincu.GComponentLocalTransform.getComponentType())))
		.addComponent(gincu.GComponentAnchor(anchor).setFlipX(true))
		.addComponent(gincu.createAndLoadImageComponent(imageNameB))
		.addComponent(gincu.GComponentRendererTouchHandler().addOnTouch(gincu.createEventCallback(
			function(e)
				if e.getType() == gincu.GEventType.touchPressed then
					print("clicked: imageB-A flip x");
				end
			end
		)))
	);

	me.addEntity(
		gincu.GEntity()
		.addComponent(gincu.GComponentTransform())
		.addComponent(gincu.GComponentLocalTransform(port.createPoint(0, yDelta)).setParent(entityB.getComponentByTypeId(gincu.GComponentLocalTransform.getComponentType())))
		.addComponent(gincu.GComponentAnchor(anchor).setFlipY(true))
		.addComponent(gincu.createAndLoadImageComponent(imageNameC))
		.addComponent(gincu.GComponentRendererTouchHandler().addOnTouch(gincu.createEventCallback(
			function(e)
				if e.getType() == gincu.GEventType.touchPressed then
					print("clicked: imageC-B flip y");
				end
			end
		)))
	);

	entityD = gincu.GEntity();
	me.addEntity(
		entityD
		.addComponent(gincu.GComponentTransform())
		.addComponent(gincu.GComponentLocalTransform(port.createPoint(0, yDelta * 2)).setParent(entityB.getComponentByTypeId(gincu.GComponentLocalTransform.getComponentType())))
		.addComponent(gincu.GComponentAnchor(anchor).setFlipX(true).setFlipY(true))
		.addComponent(gincu.createAtlasRenderComponent(gincu.GResourceManager.getInstance().getAtlas(atlasName, gincu.GAtlasFormat.spritePackText), ""))
		.addComponent(createAnimation(atlasName))
		.addComponent(gincu.GComponentRendererTouchHandler().addOnTouch(gincu.createEventCallback(
			function(e)
				if e.getType() == gincu.GEventType.touchPressed then
					print("clicked: imageD-B flip x/y");
				end
			end
		)))
	);

	return result;
end

function doInitializeStatic(me, pos)
	createParentedObject(me, pos, gincu.GRenderAnchor.leftTop, 0, 1)
end

function doInitializeRotation(me, pos)
	createParentedObject(me, pos, gincu.GRenderAnchor.leftTop, -45, 0.75)
end

function doInitializeRotationAnimation(me, pos)
	local localTransform = createParentedObject(me, pos, gincu.GRenderAnchor.center, 0, 0.5)
	local accessor = gincu.createFloatAccessor(localTransform, 'getRotation', 'setRotation')
	me.getTweenList().tween()
		.duration(10000)
		.ease(gincu.ElasticEase.easeOut())
		._repeat(-1)
		.targetFloat(accessor, 360)
end

SceneTestSceneGraph.doOnEnter = function(me)
	me.addEntity(createBackButton(function(e)
		gincu.GApplication.getInstance().getSceneManager().switchScene(SceneMain())
	end))

	doInitializeStatic(me, port.createPoint(150, 50))
	doInitializeRotation(me, port.createPoint(300, 50))
	doInitializeRotationAnimation(me, port.createPoint(450, 350))
end

