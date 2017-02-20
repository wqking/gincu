#include "testbed/testcase.h"
#include "testbed/testbed.h"
#include "testbed/scenetestcase.h"
#include "uiutil.h"

#include "gincu/ecs/gentity.h"
#include "gincu/ecs/gcomponentrender.h"
#include "gincu/ecs/gcomponenttransform.h"
#include "gincu/ecs/gcomponenttouchhandler.h"
#include "gincu/ecs/gcomponentanchor.h"
#include "gincu/ecs/gcomponentanimation.h"
#include "gincu/gresourcemanager.h"
#include "gincu/grenderanchor.h"
#include "gincu/ecs/gcomponentframeanimation.h"

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

void TestCase_Animation::doInitializeAnimation(const GPoint & position)
{
	const std::string atlasName("testbed/animation_yellow_boy");
	const GCoord x = position.x;
	const GCoord y = position.y;
	const GCoord xDelta = 180;
	const GCoord yDelta = 150;

	this->getScene()->addEntity(
		(new GEntity())
		->addComponent(createComponent<GComponentTransform>(GPoint{x, y}))
		->addComponent(createComponent<GComponentAnchor>(GRenderAnchor::leftTop))
		->addComponent(createAtlasRenderComponent(GResourceManager::getInstance()->getAtlas(atlasName, GAtlasFormat::spritePackText), ""))
		->addComponent(createAnimation(atlasName))
		->addComponent(createComponent<GComponentRendererTouchHandler>()->addOnTouch(createOnPressCallback([=](){ this->getTestBed()->print("clicked: animation LeftTop no flip"); })))
	);

	this->getScene()->addEntity(
		(new GEntity())
		->addComponent(createComponent<GComponentTransform>(GPoint{x, y + yDelta}))
		->addComponent(createComponent<GComponentAnchor>(GRenderAnchor::leftTop)->setFlipX(true))
		->addComponent(createAtlasRenderComponent(GResourceManager::getInstance()->getAtlas(atlasName, GAtlasFormat::spritePackText), ""))
		->addComponent(createAnimation(atlasName))
		->addComponent(createComponent<GComponentRendererTouchHandler>()->addOnTouch(createOnPressCallback([=](){ this->getTestBed()->print("clicked: animation LeftTop flip x"); })))
	);

	this->getScene()->addEntity(
		(new GEntity())
		->addComponent(createComponent<GComponentTransform>(GPoint{x + xDelta, y}))
		->addComponent(createComponent<GComponentAnchor>(GRenderAnchor::leftTop)->setFlipY(true))
		->addComponent(createAtlasRenderComponent(GResourceManager::getInstance()->getAtlas(atlasName, GAtlasFormat::spritePackText), ""))
		->addComponent(createAnimation(atlasName))
		->addComponent(createComponent<GComponentRendererTouchHandler>()->addOnTouch(createOnPressCallback([=](){ this->getTestBed()->print("clicked: animation LeftTop flip y"); })))
	);

	this->getScene()->addEntity(
		(new GEntity())
		->addComponent(createComponent<GComponentTransform>(GPoint{x + xDelta, y + yDelta}))
		->addComponent(createComponent<GComponentAnchor>(GRenderAnchor::leftTop)->setFlipX(true)->setFlipY(true))
		->addComponent(createAtlasRenderComponent(GResourceManager::getInstance()->getAtlas(atlasName, GAtlasFormat::spritePackText), ""))
		->addComponent(createAnimation(atlasName))
		->addComponent(createComponent<GComponentRendererTouchHandler>()->addOnTouch(createOnPressCallback([=](){ this->getTestBed()->print("clicked: animation LeftTop flip x/y"); })))
	);

	this->getScene()->addEntity(
		(new GEntity())
		->addComponent(createComponent<GComponentTransform>(GPoint{x + xDelta * 2, y})->setRotation(30))
		->addComponent(createComponent<GComponentAnchor>(GRenderAnchor::leftTop))
		->addComponent(createAtlasRenderComponent(GResourceManager::getInstance()->getAtlas(atlasName, GAtlasFormat::spritePackText), ""))
		->addComponent(createAnimation(atlasName))
		->addComponent(createComponent<GComponentRendererTouchHandler>()->addOnTouch(createOnPressCallback([=](){ this->getTestBed()->print("clicked: animation LeftTop rotate 30"); })))
	);

	this->getScene()->addEntity(
		(new GEntity())
		->addComponent(createComponent<GComponentTransform>(GPoint{x + xDelta * 3, y})->setRotation(30))
		->addComponent(createComponent<GComponentAnchor>(GRenderAnchor::center))
		->addComponent(createAtlasRenderComponent(GResourceManager::getInstance()->getAtlas(atlasName, GAtlasFormat::spritePackText), ""))
		->addComponent(createAnimation(atlasName))
		->addComponent(createComponent<GComponentRendererTouchHandler>()->addOnTouch(createOnPressCallback([=](){ this->getTestBed()->print("clicked: animation Center rotate 30"); })))
	);
}


G_AUTO_RUN_BEFORE_MAIN(TestCase_Animation)
{
	TestBedRegister::getInstance()->registerItem("Animation", &testCaseCreator<TestCase_Animation>);
}


} //unnamed namespace
