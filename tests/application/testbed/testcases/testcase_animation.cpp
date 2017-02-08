#include "testbed/testcase.h"
#include "testbed/testbed.h"
#include "testbed/scenetestcase.h"
#include "uiutil.h"

#include "gincu/gentity.h"
#include "gincu/gcomponentrender.h"
#include "gincu/gcomponenttransform.h"
#include "gincu/gcomponenttouchhandler.h"
#include "gincu/gcomponentanchor.h"
#include "gincu/gcomponentanimation.h"
#include "gincu/gresourcemanager.h"

#include "cpgf/goutmain.h"

using namespace gincu;

class TestCase_Animation : public TestCase
{
private:
	virtual void doInitialize() override;

private:
	void doInitializeAnimation(const GPoint & position);
};

void TestCase_Animation::doInitialize()
{
	this->doInitializeAnimation({ 100, 150 });
}

GComponentTweenedFrameAnimation * createAnimation(GEntity * entity, const std::string & spriteSheetName)
{
	std::shared_ptr<GFrameAnimationSetData> data(std::make_shared<GFrameAnimationSetData>());
	buildFrameAnimationDataFromSpriteSheet(data.get(), GResourceManager::getInstance()->getSpriteSheet(spriteSheetName, GSpriteSheetFormat::spritePackText));
	GTweenedFrameAnimation animation(data);
	animation.setUpdater([=](const int index) {
		GComponentSpriteSheetRender * render = entity->getComponentByType<GComponentSpriteSheetRender>();
		render->getRender().setIndex(index);
	});
	animation.getTween().repeat(-1);
	animation.getTween().timeScale(0.1);
	return createComponent<GComponentTweenedFrameAnimation>(animation);
}

void TestCase_Animation::doInitializeAnimation(const GPoint & position)
{
	const std::string spriteSheetName("testbed/animation_yellow_boy");
	const GCoord x = position.x;
	const GCoord y = position.y;
	const GCoord xDelta = 150;
	const GCoord yDelta = 150;

	GEntity * entity;

	entity = new GEntity();
	this->getScene()->addEntity(
		entity
		->addComponent(createComponent<GComponentTransform>(GPoint{x, y}))
		->addComponent(createComponent<GComponentAnchor>(GRenderAnchor::leftTop))
		->addComponent(createSpriteSheetComponent(GResourceManager::getInstance()->getSpriteSheet(spriteSheetName, GSpriteSheetFormat::spritePackText), ""))
		->addComponent(createAnimation(entity, spriteSheetName))
		->addComponent(createComponent<GComponentRendererTouchHandler>()->addOnTouch(createOnPressCallback([=](){ this->getTestBed()->print("clicked: animation LeftTop no flip"); })))
	);
}


G_AUTO_RUN_BEFORE_MAIN(TestCase_Animation)
{
	TestBedRegister::getInstance()->registerItem("Animation", &testCaseCreator<TestCase_Animation>);
}
