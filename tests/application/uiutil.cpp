#include "uiutil.h"
#include "gincu/gresourcemanager.h"
#include "gincu/ecs/gcomponentrender.h"
#include "gincu/ecs/gcomponenttouchhandler.h"
#include "gincu/grenderanchor.h"

using namespace gincu;

cpgf::GCallback<void (const gincu::GEvent &)> createOnPressCallback(const cpgf::GCallback<void ()> & onPress)
{
	return [=](const GEvent & e) {
		if(e.getType() == GEventType::touchPressed) {
			onPress();
		}
	};
}

gincu::GEntity * createBackButton(const cpgf::GCallback<void ()> & onClick)
{
	return (new GEntity())
		->addComponent(createComponent<GComponentTransform>(GPoint{ 40, 40 }))
		->addComponent(createComponent<GComponentAnchor>(GRenderAnchor::center))
		->addComponent(createAtlasRenderComponent(GResourceManager::getInstance()->getAtlas("ui_atlas", GAtlasFormat::spritePackText), "back_button"))
		->addComponent(createComponent<GComponentRendererTouchHandler>()->addOnTouch(createOnPressCallback(onClick))
	);
}

gincu::GEntity * createButton(
		const std::string & text,
		const gincu::GPoint & position,
		const cpgf::GCallback<void ()> & onClick,
		const gincu::GSize size
	)
{
	return (new GEntity())
		->addComponent(createComponent<GComponentTransform>(position))
		->addComponent(createComponent<GComponentAnchor>(GRenderAnchor::center))
		->addComponent(createComponent<GComponentContainerRender>()
			->add(createRectRenderComponent(0xffeeee77, size))
			->add(createAndLoadTextComponent(text, colorBlue, 16))
		)
		->addComponent(createComponent<GComponentRendererTouchHandler>()->addOnTouch(createOnPressCallback(onClick))
	);
}

gincu::GComponentFrameAnimation * createAnimation(const std::string & atlasName)
{
	std::shared_ptr<GFrameAnimationSetData> data(std::make_shared<GFrameAnimationSetData>());
	buildFrameAnimationDataFromAtlas(data.get(), GResourceManager::getInstance()->getAtlas(atlasName, GAtlasFormat::spritePackText));
	GComponentFrameAnimation * component = createComponent<GComponentFrameAnimation>(data);
	component->getTween().repeat(-1).timeScale(0.2f);
	return component;
}

