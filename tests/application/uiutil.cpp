#include "uiutil.h"
#include "gincu/gresourcemanager.h"
#include "gincu/gcomponentrender.h"
#include "gincu/gcomponenttouchhandler.h"

using namespace gincu;

cpgf::GCallback<void (const gincu::GTouchEvent &)> createOnPressCallback(const cpgf::GCallback<void ()> & onPress)
{
	return [=](const GTouchEvent & e) {
		if(e.type == GTouchEventType::eventPressed) {
			onPress();
		}
	};
}

gincu::GEntity * createBackButton(const cpgf::GCallback<void ()> & onClick)
{
	return (new GEntity())
		->addComponent(createComponent<GComponentTransform>(GPoint{ 40, 40 }))
		->addComponent(createComponent<GComponentAnchor>(GRenderAnchor::center))
		->addComponent(createSpriteSheetComponent(GResourceManager::getInstance()->getSpriteSheet("ui_spritesheet", GSpriteSheetFormat::spritePackText), "back_button"))
		->addComponent(createComponent<GComponentRendererTouchHandler>()->addOnTouch(createOnPressCallback(onClick))
	);
}

