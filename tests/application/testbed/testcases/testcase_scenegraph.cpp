#include "testbed/testcase.h"
#include "testbed/testbed.h"
#include "testbed/scenetestcase.h"
#include "uiutil.h"

#include "gincu/gentity.h"
#include "gincu/gcomponentrender.h"
#include "gincu/gcomponenttransform.h"
#include "gincu/gcomponenttouchhandler.h"
#include "gincu/gcomponentanchor.h"

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
};

void TestCase_SceneGraph::doInitialize()
{
	this->doInitializeStatic({ 150, 50 });
	this->doInitializeRotation({ 300, 50 });
}

GComponentLocalTransform * TestCase_SceneGraph::createParentedObject(const GPoint & position, const GRenderAnchor anchor, const float rotation, const float scale)
{
	const std::string imageNameA("testbed/cat.png");
	const std::string imageNameB("testbed/dog.png");
	const std::string imageNameC("testbed/rabbit.png");
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
		->addComponent(createComponent<GComponentRendererTouchHandler>()->addOnTouch(createOnPressCallback([=](){ this->getTestBed()->print("clicked: imageB flip x"); })))
	);

	this->getScene()->addEntity(
		(new GEntity())
		->addComponent(createComponent<GComponentTransform>())
		->addComponent(createComponent<GComponentLocalTransform>(GPoint{0, yDelta})->setParent(entityB->getComponentByType<GComponentLocalTransform>()))
		->addComponent(createComponent<GComponentAnchor>(anchor)->setFlipY(true))
		->addComponent(createAndLoadImageComponent(imageNameC))
		->addComponent(createComponent<GComponentRendererTouchHandler>()->addOnTouch(createOnPressCallback([=](){ this->getTestBed()->print("clicked: imageC flip y"); })))
	);

	return result;
}

void TestCase_SceneGraph::doInitializeStatic(const GPoint & position)
{
	this->createParentedObject(position, GRenderAnchor::leftTop);
}

void TestCase_SceneGraph::doInitializeRotation(const GPoint & position)
{
	GComponentLocalTransform * localTransform = this->createParentedObject(position, GRenderAnchor::center);
	localTransform->setRotation(-45)->setScale({ 0.75f, 0.75f });
}


G_AUTO_RUN_BEFORE_MAIN(TestCase_SceneGraph)
{
	TestBedRegister::getInstance()->registerItem("Scene Graph", &testCaseCreator<TestCase_SceneGraph>);
}
