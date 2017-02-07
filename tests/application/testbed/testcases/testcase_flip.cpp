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

class TestCase_Flip : public TestCase
{
private:
	virtual void doInitialize() override;
};

void TestCase_Flip::doInitialize()
{
	GCoord x = 100;
	GCoord y = 100;
	GCoord xDelta = 400;
	GCoord yDelta = 60;
	const GColor color = colorBlue;
	const int fontSize = 32;
	this->getScene()->addEntity(
		(new GEntity())
		->addComponent(createComponent<GComponentTransform>(GPoint{x, y}))
		->addComponent(createComponent<GComponentAnchor>(GRenderAnchor::leftTop))
		->addComponent(createAndLoadTextComponent("text LeftTop no flip", color, fontSize))
		->addComponent(createComponent<GComponentRendererTouchHandler>()->addOnTouch(createOnPressCallback([=](){ this->getTestBed()->print("clicked: text LeftTop no flip"); })))
	);

	this->getScene()->addEntity(
		(new GEntity())
		->addComponent(createComponent<GComponentTransform>(GPoint{x, y + yDelta}))
		->addComponent(createComponent<GComponentAnchor>(GRenderAnchor::leftTop)->setFlipX(true))
		->addComponent(createAndLoadTextComponent("text LeftTop flip x", color, fontSize))
		->addComponent(createComponent<GComponentRendererTouchHandler>()->addOnTouch(createOnPressCallback([=](){ this->getTestBed()->print("clicked: text LeftTop flip x"); })))
	);

	this->getScene()->addEntity(
		(new GEntity())
		->addComponent(createComponent<GComponentTransform>(GPoint{x + xDelta, y}))
		->addComponent(createComponent<GComponentAnchor>(GRenderAnchor::leftTop)->setFlipY(true))
		->addComponent(createAndLoadTextComponent("text LeftTop flip y", color, fontSize))
		->addComponent(createComponent<GComponentRendererTouchHandler>()->addOnTouch(createOnPressCallback([=](){ this->getTestBed()->print("clicked: text LeftTop flip y"); })))
	);

	this->getScene()->addEntity(
		(new GEntity())
		->addComponent(createComponent<GComponentTransform>(GPoint{x + xDelta, y + yDelta}))
		->addComponent(createComponent<GComponentAnchor>(GRenderAnchor::leftTop)->setFlipX(true)->setFlipY(true))
		->addComponent(createAndLoadTextComponent("text LeftTop flip x/y", color, fontSize))
		->addComponent(createComponent<GComponentRendererTouchHandler>()->addOnTouch(createOnPressCallback([=](){ this->getTestBed()->print("clicked: text LeftTop flip x/y"); })))
	);
}


G_AUTO_RUN_BEFORE_MAIN()
{
	TestBedRegister::getInstance()->registerItem("Flip", &testCaseCreator<TestCase_Flip>);
}
