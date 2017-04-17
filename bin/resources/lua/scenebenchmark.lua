local backgroundImageName = "matchthree/background.png"

local animationNames = { "testbed/animation_yellow_boy", "testbed/animation_running_man" };

SceneBenchmark = cpgf.cloneClass(gincu.GSceneWrapper)

local function createAnimationEntity(me, position, atlasName)
	me.addEntity(
		gincu.GEntity()
		.addComponent(gincu.GComponentTransform(position))
		.addComponent(gincu.GComponentAnchor(gincu.GRenderAnchor.center))
		.addComponent(gincu.createAtlasRenderComponent(gincu.GResourceManager.getInstance().getAtlas(atlasName, gincu.GAtlasFormat.spritePackText), ""))
		.addComponent(createAnimation(atlasName))
	);
end

local function getRandomPosition(me)
	local viewSize = me.getPrimaryCamera().getWorldSize();
	return port.createPoint(gincu.getRand(viewSize.width), gincu.getRand(viewSize.height));
end

local function doBenchmarkBatchedAnimation(me)
	local iterateCount = 10000
	local animationCount = #animationNames;

	for key, value in pairs(animationNames) do
		for i = 1, iterateCount / animationCount do
			createAnimationEntity(me, getRandomPosition(me), value);
		end
	end
end

SceneBenchmark.doOnEnter = function(me)
	doBenchmarkBatchedAnimation(me)

	me.addEntity(createBackButton(function(e)
		gincu.GApplication.getInstance().getSceneManager().switchScene(SceneMain())
	end))
	
end

SceneBenchmark.doOnExit = function(me)
end

