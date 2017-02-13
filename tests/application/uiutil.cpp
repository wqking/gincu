#include "uiutil.h"
#include "gincu/gresourcemanager.h"
#include "gincu/gcomponentrender.h"
#include "gincu/gcomponenttouchhandler.h"

using namespace gincu;

cpgf::GCallback<void (const gincu::GEvent &)> createOnPressCallback(const cpgf::GCallback<void ()> & onPress)
{
	return [=](const GEvent & e) {
		if(e.type == GEventType::touchPressed) {
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

