#include "testbed/testcase.h"
#include "testbed/testbed.h"
#include "testbed/scenetestcase.h"
#include "uiutil.h"

#include "gincu/ecs/gentity.h"
#include "gincu/ecs/gcomponentrender.h"
#include "gincu/ecs/gcomponenttransform.h"
#include "gincu/ecs/gcomponenttouchhandler.h"
#include "gincu/ecs/gcomponentanchor.h"
#include "gincu/ecs/gcomponentcamera.h"
#include "gincu/ecs/gcomponentanimation.h"
#include "gincu/gresourcemanager.h"
#include "gincu/grenderanchor.h"

#include "cpgf/goutmain.h"

#include <vector>

using namespace gincu;

class TestCase_Camera : public TestCase
{
private:
	virtual void doInitialize() override;

private:
	void doInitializeContent();
	void doInitializeCameras();
	void doInitializeButtons();
	
private:
	std::vector<GEntity *> cameraList;
	std::vector<GEntity *> entityList;
};

void TestCase_Camera::doInitialize()
{
	this->doInitializeContent();
	this->doInitializeCameras();
	this->doInitializeButtons();
}

void TestCase_Camera::doInitializeContent()
{
	this->entityList.push_back(
	this->getScene()->addEntity(
		(new GEntity())
		->addComponent(createComponent<GComponentTransform>(GPoint{ 10, 10 })->setCameraId(1))
		->addComponent(createComponent<GComponentAnchor>(GRenderAnchor::leftTop))
		->addComponent(createAndLoadTextComponent("This is text", colorBlue, 24))
		->addComponent(createComponent<GComponentRendererTouchHandler>()->addOnTouch(createOnPressCallback([=](){ this->getTestBed()->print("clicked: text LeftTop no flip"); })))
	));

	const std::string atlasName("testbed/animation_yellow_boy");

	this->entityList.push_back(
	this->getScene()->addEntity(
		(new GEntity())
		->addComponent(createComponent<GComponentTransform>(GPoint{150, 150})->setCameraId(2))
		->addComponent(createComponent<GComponentAnchor>(GRenderAnchor::leftTop))
		->addComponent(createAtlasRenderComponent(GResourceManager::getInstance()->getAtlas(atlasName, GAtlasFormat::spritePackText), ""))
		->addComponent(createAnimation(atlasName))
		->addComponent(createComponent<GComponentRendererTouchHandler>()->addOnTouch(createOnPressCallback([=](){ this->getTestBed()->print("clicked: animation LeftTop no flip"); })))
	));

}

void TestCase_Camera::doInitializeCameras()
{
	const unsigned int defaultMask = (1u << 1) | (1u << 2);
	const GPoint position{ 0, 0 };
	const GSize worldSize{ 360, 240 };
	const float viewportSize = 0.3f;
	const float viewportX = 0.1f;
	const float viewportY = 0.1f;

	this->cameraList.push_back(
	this->getScene()->addEntity(
		(new GEntity())
		->addComponent(createComponent<GComponentTransform>(position))
		->addComponent(createComponent<GComponentCamera>()
			->setMask(defaultMask)
			->setViewport({ viewportX, viewportY, viewportSize, viewportSize })
			->setWorldSize(worldSize)
		)
		->addComponent(createComponent<GComponentAnchor>(GRenderAnchor::leftTop))
	));

	this->cameraList.push_back(
	this->getScene()->addEntity(
		(new GEntity())
		->addComponent(createComponent<GComponentTransform>(position))
		->addComponent(createComponent<GComponentCamera>()
			->setMask(defaultMask)
			->setViewport({ viewportX + viewportSize, viewportY, viewportSize, viewportSize })
			->setWorldSize(worldSize)
		)
		->addComponent(createComponent<GComponentAnchor>(GRenderAnchor::leftTop)->setFlipX(true))
	));

	this->cameraList.push_back(
	this->getScene()->addEntity(
		(new GEntity())
		->addComponent(createComponent<GComponentTransform>(position)->setScale({ 2.0f, 2.0f }))
		->addComponent(createComponent<GComponentCamera>()
			->setMask(defaultMask)
			->setViewport({ viewportX + viewportSize, viewportY + viewportSize, viewportSize, viewportSize })
			->setWorldSize(worldSize)
		)
		->addComponent(createComponent<GComponentAnchor>(GRenderAnchor::center)->setFlipY(true))
	));

	this->cameraList.push_back(
	this->getScene()->addEntity(
		(new GEntity())
		->addComponent(createComponent<GComponentTransform>(position)
			->setScale({ 2.0f, 2.0f })
			->setRotation(45)
		)
		->addComponent(createComponent<GComponentCamera>()
			->setMask(defaultMask)
			->setViewport({ viewportX + viewportSize * 1.5f, viewportY + viewportSize * 1.5f, viewportSize, viewportSize })
			->setWorldSize(worldSize)
		)
		->addComponent(createComponent<GComponentAnchor>(GRenderAnchor::center)->setFlipX(true)->setFlipY(true))
	));
}

void TestCase_Camera::doInitializeButtons()
{
	const float startX = 80;
	const float startY = 100;
//	const float deltaY = defaultButtonSize.height + 10;

	this->getScene()->addEntity(
		createButton("Turn on/off", GPoint{startX, startY}, [=]() {
			GComponentCamera * camera = this->cameraList[1]->getComponentByType<GComponentCamera>();
			camera->setMask(camera->getMask() ^ (1u << 2));
			
			GComponentTransform * transform = this->entityList[0]->getComponentByType<GComponentTransform>();
			transform->setCameraId((transform->getCameraId() != 1) ? 1 : 6);
		})
	);
}


G_AUTO_RUN_BEFORE_MAIN(TestCase_Camera)
{
	TestBedRegister::getInstance()->registerItem("Camera", &testCaseCreator<TestCase_Camera>);
}
