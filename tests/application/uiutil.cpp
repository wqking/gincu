#include "uiutil.h"
#include "gincu/gresourcemanager.h"
#include "gincu/gcomponentrender.h"
#include "gincu/gcomponenttouchhandler.h"
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
		->addComponent(createComponent<GComponentAnchor>(GRenderAnchor::leftTop))
		->addComponent(createComponent<GComponentContainerRender>()
			->add(createRectRenderComponent(0xffeeee77, size))
			->add(createAndLoadTextComponent(text, colorBlue, 16))
		)
		->addComponent(createComponent<GComponentRendererTouchHandler>()->addOnTouch(createOnPressCallback(onClick))
	);
}
