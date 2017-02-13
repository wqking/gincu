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

namespace {

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
	this->doInitializeAnimation({ 100, 50 });
}

GComponentTweenedFrameAnimation * createAnimation(GEntity * entity, const std::string & atlasName)
{
	std::shared_ptr<GFrameAnimationSetData> data(std::make_shared<GFrameAnimationSetData>());
	buildFrameAnimationDataFromAtlas(data.get(), GResourceManager::getInstance()->getAtlas(atlasName, GAtlasFormat::spritePackText));
	GTweenedFrameAnimation animation(data);
	animation.setUpdater([=](const int index) {
		GComponentAtlasRender * render = entity->getComponentByType<GComponentAtlasRender>();
		render->getRender().setIndex(index);
	});
	animation.getTween().repeat(-1);
	animation.getTween().timeScale(0.2f);
	return createComponent<GComponentTweenedFrameAnimation>(animation);
}

void TestCase_Animation::doInitializeAnimation(const GPoint & position)
{
	const std::string atlasName("testbed/animation_yellow_boy");
	const GCoord x = position.x;
	const GCoord y = position.y;
	const GCoord xDelta = 180;
	const GCoord yDelta = 150;

	GEntity * entity;

	entity = new GEntity();
	this->getScene()->addEntity(
		entity
		->addComponent(createComponent<GComponentTransform>(GPoint{x, y}))
		->addComponent(createComponent<GComponentAnchor>(GRenderAnchor::leftTop))
		->addComponent(createAtlasRenderComponent(GResourceManager::getInstance()->getAtlas(atlasName, GAtlasFormat::spritePackText), ""))
		->addComponent(createAnimation(entity, atlasName))
		->addComponent(createComponent<GComponentRendererTouchHandler>()->addOnTouch(createOnPressCallback([=](){ this->getTestBed()->print("clicked: animation LeftTop no flip"); })))
	);

	entity = new GEntity();
	this->getScene()->addEntity(
		entity
		->addComponent(createComponent<GComponentTransform>(GPoint{x, y + yDelta}))
		->addComponent(createComponent<GComponentAnchor>(GRenderAnchor::leftTop)->setFlipX(true))
		->addComponent(createAtlasRenderComponent(GResourceManager::getInstance()->getAtlas(atlasName, GAtlasFormat::spritePackText), ""))
		->addComponent(createAnimation(entity, atlasName))
		->addComponent(createComponent<GComponentRendererTouchHandler>()->addOnTouch(createOnPressCallback([=](){ this->getTestBed()->print("clicked: animation LeftTop flip x"); })))
	);

	entity = new GEntity();
	this->getScene()->addEntity(
		entity
		->addComponent(createComponent<GComponentTransform>(GPoint{x + xDelta, y}))
		->addComponent(createComponent<GComponentAnchor>(GRenderAnchor::leftTop)->setFlipY(true))
		->addComponent(createAtlasRenderComponent(GResourceManager::getInstance()->getAtlas(atlasName, GAtlasFormat::spritePackText), ""))
		->addComponent(createAnimation(entity, atlasName))
		->addComponent(createComponent<GComponentRendererTouchHandler>()->addOnTouch(createOnPressCallback([=](){ this->getTestBed()->print("clicked: animation LeftTop flip y"); })))
	);

	entity = new GEntity();
	this->getScene()->addEntity(
		entity
		->addComponent(createComponent<GComponentTransform>(GPoint{x + xDelta, y + yDelta}))
		->addComponent(createComponent<GComponentAnchor>(GRenderAnchor::leftTop)->setFlipX(true)->setFlipY(true))
		->addComponent(createAtlasRenderComponent(GResourceManager::getInstance()->getAtlas(atlasName, GAtlasFormat::spritePackText), ""))
		->addComponent(createAnimation(entity, atlasName))
		->addComponent(createComponent<GComponentRendererTouchHandler>()->addOnTouch(createOnPressCallback([=](){ this->getTestBed()->print("clicked: animation LeftTop flip x/y"); })))
	);

	entity = new GEntity();
	this->getScene()->addEntity(
		entity
		->addComponent(createComponent<GComponentTransform>(GPoint{x + xDelta * 2, y})->setRotation(30))
		->addComponent(createComponent<GComponentAnchor>(GRenderAnchor::leftTop))
		->addComponent(createAtlasRenderComponent(GResourceManager::getInstance()->getAtlas(atlasName, GAtlasFormat::spritePackText), ""))
		->addComponent(createAnimation(entity, atlasName))
		->addComponent(createComponent<GComponentRendererTouchHandler>()->addOnTouch(createOnPressCallback([=](){ this->getTestBed()->print("clicked: animation LeftTop rotate 30"); })))
	);

	entity = new GEntity();
	this->getScene()->addEntity(
		entity
		->addComponent(createComponent<GComponentTransform>(GPoint{x + xDelta * 3, y})->setRotation(30))
		->addComponent(createComponent<GComponentAnchor>(GRenderAnchor::center))
		->addComponent(createAtlasRenderComponent(GResourceManager::getInstance()->getAtlas(atlasName, GAtlasFormat::spritePackText), ""))
		->addComponent(createAnimation(entity, atlasName))
		->addComponent(createComponent<GComponentRendererTouchHandler>()->addOnTouch(createOnPressCallback([=](){ this->getTestBed()->print("clicked: animation Center rotate 30"); })))
	);
}


G_AUTO_RUN_BEFORE_MAIN(TestCase_Animation)
{
	TestBedRegister::getInstance()->registerItem("Animation", &testCaseCreator<TestCase_Animation>);
}


} //unnamed namespace
