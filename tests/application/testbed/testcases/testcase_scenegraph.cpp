#include "testbed/testcase.h"
#include "testbed/testbed.h"
#include "testbed/scenetestcase.h"
#include "uiutil.h"

#include "gincu/gentity.h"
#include "gincu/gcomponentrender.h"
#include "gincu/gcomponenttransform.h"
#include "gincu/gcomponenttouchhandler.h"
#include "gincu/gcomponentanchor.h"

#include "cpgf/accessor/gaccessor.h"
#include "cpgf/tween/easing/elastic.h"
#include "cpgf/goutmain.h"

using namespace gincu;

class TestCase_SceneGraph : public TestCase
{
private:
	virtual void doInitialize() override;

private:
	GComponentLocalTransform * createParentedObject(const GPoint & position, const GRenderAnchor anchor = GRenderAnchor::leftTop, const float rotation = 0, const float scale = 1.0f);

	void doInitializeStatic(const GPoint & position);
	void doInitializeRotation(const GPoint & position);
	void doInitializeRotationAnimation(const GPoint & position);
};

void TestCase_SceneGraph::doInitialize()
{
	this->doInitializeStatic({ 150, 50 });
	this->doInitializeRotation({ 300, 50 });
	this->doInitializeRotationAnimation({ 450, 350 });
}

GComponentLocalTransform * TestCase_SceneGraph::createParentedObject(const GPoint & position, const GRenderAnchor anchor, const float rotation, const float scale)
{
	const std::string imageNameA("testbed/cat.png");
	const std::string imageNameB("testbed/dog.png");
	const std::string imageNameC("testbed/pig.png");
	const std::string imageNameD("testbed/rabbit.png");
	const GCoord x = position.x;
	const GCoord y = position.y;
	const GCoord xDelta = 150;
	const GCoord yDelta = 150;

	GComponentLocalTransform * result;

	GEntity * entityA;
	GEntity * entityB;
	this->getScene()->addEntity(
		(entityA = new GEntity())
		->addComponent(createComponent<GComponentTransform>())
		->addComponent((result = createComponent<GComponentLocalTransform>(GPoint{x, y}))->setRotation(rotation)->setScale({ scale, scale }))
		->addComponent(createComponent<GComponentAnchor>(anchor))
		->addComponent(createAndLoadImageComponent(imageNameA))
		->addComponent(createComponent<GComponentRendererTouchHandler>()->addOnTouch(createOnPressCallback([=](){ this->getTestBed()->print("clicked: imageA"); })))
	);

	this->getScene()->addEntity(
		(entityB = new GEntity())
		->addComponent(createComponent<GComponentTransform>())
		->addComponent(createComponent<GComponentLocalTransform>(GPoint{0, yDelta})->setParent(entityA->getComponentByType<GComponentLocalTransform>()))
		->addComponent(createComponent<GComponentAnchor>(anchor)->setFlipX(true))
		->addComponent(createAndLoadImageComponent(imageNameB))
		->addComponent(createComponent<GComponentRendererTouchHandler>()->addOnTouch(createOnPressCallback([=](){ this->getTestBed()->print("clicked: imageB-A flip x"); })))
	);

	this->getScene()->addEntity(
		(new GEntity())
		->addComponent(createComponent<GComponentTransform>())
		->addComponent(createComponent<GComponentLocalTransform>(GPoint{0, yDelta})->setParent(entityB->getComponentByType<GComponentLocalTransform>()))
		->addComponent(createComponent<GComponentAnchor>(anchor)->setFlipY(true))
		->addComponent(createAndLoadImageComponent(imageNameC))
		->addComponent(createComponent<GComponentRendererTouchHandler>()->addOnTouch(createOnPressCallback([=](){ this->getTestBed()->print("clicked: imageC-B flip y"); })))
	);

	this->getScene()->addEntity(
		(new GEntity())
		->addComponent(createComponent<GComponentTransform>())
		->addComponent(createComponent<GComponentLocalTransform>(GPoint{0, yDelta * 2})->setParent(entityB->getComponentByType<GComponentLocalTransform>()))
		->addComponent(createComponent<GComponentAnchor>(anchor)->setFlipX(true)->setFlipY(true))
		->addComponent(createAndLoadImageComponent(imageNameD))
		->addComponent(createComponent<GComponentRendererTouchHandler>()->addOnTouch(createOnPressCallback([=](){ this->getTestBed()->print("clicked: imageD-B flip x/y"); })))
	);

	return result;
}

void TestCase_SceneGraph::doInitializeStatic(const GPoint & position)
{
	this->createParentedObject(position, GRenderAnchor::leftTop);
}

void TestCase_SceneGraph::doInitializeRotation(const GPoint & position)
{
	this->createParentedObject(position, GRenderAnchor::leftTop, -45, 0.75f);
}

void TestCase_SceneGraph::doInitializeRotationAnimation(const GPoint & position)
{
	GComponentLocalTransform * localTransform = this->createParentedObject(position, GRenderAnchor::center, 0, 0.5f);
	getTweenListFromScene()->tween()
		.duration(3000)
		.ease(cpgf::ElasticEase::easeOut())
		.repeat(-1)
		.target(cpgf::createAccessor(localTransform, &GComponentLocalTransform::getRotation, &GComponentLocalTransform::setRotation), 360)
	;
}


G_AUTO_RUN_BEFORE_MAIN(TestCase_SceneGraph)
{
	TestBedRegister::getInstance()->registerItem("Scene Graph", &testCaseCreator<TestCase_SceneGraph>);
}
