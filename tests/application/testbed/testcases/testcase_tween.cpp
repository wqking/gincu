#include "testbed/testcase.h"
#include "testbed/testbed.h"
#include "testbed/scenetestcase.h"
#include "uiutil.h"

#include "gincu/ecs/gentity.h"
#include "gincu/ecs/gcomponentrender.h"
#include "gincu/ecs/gcomponenttransform.h"
#include "gincu/ecs/gcomponenttouchhandler.h"
#include "gincu/ecs/gcomponentanchor.h"
#include "gincu/grenderanchor.h"
#include "gincu/gapplication.h"
#include "gincu/geventqueue.h"

#include "cpgf/tween/gtween.h"
#include "cpgf/tween/gtweenlist.h"
#include "cpgf/tween/gtimeline.h"
#include "cpgf/accessor/gaccessor.h"

#include "cpgf/tween/easing/linear.h"
#include "cpgf/tween/easing/back.h"
#include "cpgf/tween/easing/bounce.h"
#include "cpgf/tween/easing/circle.h"
#include "cpgf/tween/easing/cubic.h"
#include "cpgf/tween/easing/elastic.h"
#include "cpgf/tween/easing/exponent.h"
#include "cpgf/tween/easing/quad.h"
#include "cpgf/tween/easing/quart.h"
#include "cpgf/tween/easing/quint.h"
#include "cpgf/tween/easing/sine.h"

#include "cpgf/goutmain.h"

#include <vector>
#include <string>

namespace {

using namespace gincu;

class TestCase_Tween : public TestCase
{
private:
	virtual void doInitialize() override;
	virtual void doFinalize() override;

private:
	void onUpdate(const GEvent & event);
	void doExecuteTest(const cpgf::GCallback<void ()> & handler);
	GComponentTransform * addImage(const std::string & resourceName, const GPoint & position);
	void addEntity(GEntity * entity);

private: // tests
	void doTestBasic();
	void doTestFollow();
	void doTestTimeline1();
	void doTestTimeline2();
	
private:
	cpgf::GTweenList tweenList;
	std::vector<GEntity *> entityList;
};

const std::string imageName("testbed/rabbit.png");
constexpr GSize imageSize { 120, 103 };
constexpr GPoint spriteBoardStart { 200, 100 };
constexpr GSize spriteBoardSize = { 500, 400 };
constexpr GPoint spriteBoardEnd { spriteBoardStart.x + spriteBoardSize.width, spriteBoardStart.y + spriteBoardSize.height };

struct EaseInfo
{
	std::string name;
	cpgf::GTweenEaseType ease;
};

const std::vector<EaseInfo> easeList {
	{ "Back-In", cpgf::BackEase::easeIn() },
	{ "Back-Out", cpgf::BackEase::easeOut() },
	{ "Back-InOut", cpgf::BackEase::easeInOut() },

	{ "Bounce-In", cpgf::BounceEase::easeIn() },
	{ "Bounce-Out", cpgf::BounceEase::easeOut() },
	{ "Bounce-InOut", cpgf::BounceEase::easeInOut() },

	{ "Circle-In", cpgf::CircleEase::easeIn() },
	{ "Circle-Out", cpgf::CircleEase::easeOut() },
	{ "Circle-InOut", cpgf::CircleEase::easeInOut() },
	
	{ "Cubic-In", cpgf::CubicEase::easeIn() },
	{ "Cubic-Out", cpgf::CubicEase::easeOut() },
	{ "Cubic-InOut", cpgf::CubicEase::easeInOut() },

	{ "Elastic-In", cpgf::ElasticEase::easeIn() },
	{ "Elastic-Out", cpgf::ElasticEase::easeOut() },
	{ "Elastic-InOut", cpgf::ElasticEase::easeInOut() },
	
	{ "Exponent-In", cpgf::ExponentEase::easeIn() },
	{ "Exponent-Out", cpgf::ExponentEase::easeOut() },
	{ "Exponent-InOut", cpgf::ExponentEase::easeInOut() },

	{ "Quad-In", cpgf::QuadEase::easeIn() },
	{ "Quad-Out", cpgf::QuadEase::easeOut() },
	{ "Quad-InOut", cpgf::QuadEase::easeInOut() },
	
	{ "Quart-In", cpgf::QuartEase::easeIn() },
	{ "Quart-Out", cpgf::QuartEase::easeOut() },
	{ "Quart-InOut", cpgf::QuartEase::easeInOut() },
	
	{ "Quint-In", cpgf::QuintEase::easeIn() },
	{ "Quint-Out", cpgf::QuintEase::easeOut() },
	{ "Quint-InOut", cpgf::QuintEase::easeInOut() },
	
	{ "Sine-In", cpgf::SineEase::easeIn() },
	{ "Sine-Out", cpgf::SineEase::easeOut() },
	{ "Sine-InOut", cpgf::SineEase::easeInOut() },
	
	{ "Linear", cpgf::LinearEase::ease() },
};

void TestCase_Tween::doInitialize()
{
	const GSize buttonSize = defaultButtonSize;
	GCoord buttonX = buttonSize.width / 2 + 10;
	GCoord buttonY = 100;
	const GCoord yDelta = buttonSize.height + 20;
	
	this->getScene()->addEntity(createButton(
		"Basic",
		{ buttonX, buttonY },
		[=](){ this->doExecuteTest(cpgf::makeCallback(this, &TestCase_Tween::doTestBasic)); },
		buttonSize
	));
	buttonY += yDelta;

	this->getScene()->addEntity(createButton(
		"Follow",
		{ buttonX, buttonY },
		[=](){ this->doExecuteTest(cpgf::makeCallback(this, &TestCase_Tween::doTestFollow)); },
		buttonSize
	));
	buttonY += yDelta;

	this->getScene()->addEntity(createButton(
		"Timeline 1",
		{ buttonX, buttonY },
		[=](){ this->doExecuteTest(cpgf::makeCallback(this, &TestCase_Tween::doTestTimeline1)); },
		buttonSize
	));
	buttonY += yDelta;

	this->getScene()->addEntity(createButton(
		"Timeline 2",
		{ buttonX, buttonY },
		[=](){ this->doExecuteTest(cpgf::makeCallback(this, &TestCase_Tween::doTestTimeline2)); },
		buttonSize
	));
	buttonY += yDelta;

	GApplication::getInstance()->getEventQueue()->addListener(cpgf::makeCallback(this, &TestCase_Tween::onUpdate));
}

void TestCase_Tween::doFinalize()
{
	GApplication::getInstance()->getEventQueue()->removeListener(cpgf::makeCallback(this, &TestCase_Tween::onUpdate));
}

void TestCase_Tween::onUpdate(const GEvent & /*event*/)
{
	this->tweenList.tick((cpgf::GTweenNumber)std::max(1u, GApplication::getInstance()->getFrameMilliseconds()));
}

void TestCase_Tween::doExecuteTest(const cpgf::GCallback<void ()> & handler)
{
	this->tweenList.clear();
	
	for(GEntity * entity : this->entityList) {
		this->getScene()->removeEntity(entity);
	}
	this->entityList.clear();
	
	handler();
}

GComponentTransform * TestCase_Tween::addImage(const std::string & resourceName, const GPoint & position)
{
	GComponentTransform * result;
	this->addEntity(
		(new GEntity())
		->addComponent(result = createComponent<GComponentTransform>(position))
		->addComponent(createComponent<GComponentAnchor>(GRenderAnchor::center))
		->addComponent(createAndLoadImageComponent(resourceName))
	);
	return result;
}

void TestCase_Tween::addEntity(GEntity * entity)
{
	this->getScene()->addEntity(entity);
	this->entityList.push_back(entity);
}

void TestCase_Tween::doTestBasic()
{
	const cpgf::GTweenNumber duration = 2000;

	GComponentTransform * sprite = this->addImage(imageName, { spriteBoardStart.x, spriteBoardStart.y });
	GComponentTransform * target = this->addImage(imageName, { spriteBoardEnd.x, spriteBoardEnd.y });
	
	target->getEntity()->getComponentByType<GComponentRender>()->setColor(colorSetAlpha(colorWhite, 127));

	this->tweenList.tween()
		.duration(duration)
		.target(cpgf::createAccessor(sprite, &GComponentTransform::getPosition, &GComponentTransform::setPosition), target->getPosition())
		.target(cpgf::createAccessor(sprite, &GComponentTransform::getRotation, &GComponentTransform::setRotation), 180, 360)
		.repeat(cpgf::tweenRepeatInfinitely)
//		.backward(true)
		.yoyo(true)
	;
}

void TestCase_Tween::doTestFollow()
{
	const cpgf::GTweenNumber duration = 2000;

	GComponentTransform * target = this->addImage(imageName, { spriteBoardStart.x, spriteBoardEnd.y });
	GComponentTransform * sprite = this->addImage(imageName, { spriteBoardStart.x, spriteBoardStart.y });
	GComponentTransform * sprite2 = this->addImage(imageName, { spriteBoardEnd.x, spriteBoardStart.y });
	
	target->getEntity()->getComponentByType<GComponentRender>()->setColor(colorSetAlpha(colorWhite, 127));

	this->tweenList.tween()
		.duration(duration)
		.follow(cpgf::createAccessor(sprite, &GComponentTransform::getPosition, &GComponentTransform::setPosition), cpgf::createGetter(target, &GComponentTransform::getPosition))
	;

	this->tweenList.tween()
		.duration(duration)
		.follow(cpgf::createAccessor(sprite2, &GComponentTransform::getPosition, &GComponentTransform::setPosition), cpgf::createGetter(sprite, &GComponentTransform::getPosition))
	;

	this->tweenList.tween()
		.duration(duration)
		.target(cpgf::createAccessor(target, &GComponentTransform::getPosition, &GComponentTransform::setPosition), spriteBoardEnd)
	;
}

void TestCase_Tween::doTestTimeline1()
{
	constexpr cpgf::GTweenNumber duration = 2000;

	GComponentTransform * target = this->addImage(imageName, { spriteBoardEnd.x, spriteBoardEnd.y });
	(void)target;
	GComponentTransform * sprite = this->addImage(imageName, { spriteBoardStart.x, spriteBoardStart.y });
	
	target->getEntity()->getComponentByType<GComponentRender>()->setColor(colorSetAlpha(colorWhite, 127));

	cpgf::GTimeline & timeline = this->tweenList.timeline();

	timeline.append(
		timeline.tween()
			.duration(duration)
			.relative(cpgf::createAccessor(sprite, &GComponentTransform::getPosition, &GComponentTransform::setPosition), GPoint { spriteBoardSize.width, 0 })
	);

	timeline.append(
		timeline.tween()
			.duration(duration)
			.relative(cpgf::createAccessor(sprite, &GComponentTransform::getPosition, &GComponentTransform::setPosition), GPoint { 0, spriteBoardSize.height })
	);
}

void TestCase_Tween::doTestTimeline2()
{
	constexpr cpgf::GTweenNumber duration = 2000;
	constexpr int spriteCount = 3;
	constexpr GCoord distanceX = 100;
	constexpr GCoord distanceY = 100;

	GComponentTransform * sprites[spriteCount];
	for(int i = 0; i < spriteCount; ++i) {
		sprites[i] = this->addImage(imageName, { spriteBoardStart.x + 100.0f + imageSize.width * 1.5f * i, spriteBoardStart.y + spriteBoardSize.height / 2 } );
	}
	sprites[1]->setScale({ 0.5f, 0.5f });

	cpgf::GTimeline & timeline = this->tweenList.timeline();
	cpgf::GTweenNumber t;

	timeline.append(
		timeline.tween()
			.duration(duration)
			.ease(cpgf::ElasticEase::easeIn())
			.relative(cpgf::createAccessor(sprites[0], &GComponentTransform::getPosition, &GComponentTransform::setPosition), GPoint { -distanceX, 0 })
	);

	cpgf::GTimeline & timeline2 = timeline.timeline();

	timeline2.append(
		timeline2.tween()
			.duration(duration)
			.ease(cpgf::SineEase::easeIn())
			.target(cpgf::createAccessor(sprites[1], &GComponentTransform::getRotation, &GComponentTransform::setRotation), 360)
	);
	timeline2.prepend(
		timeline2.tween()
			.duration(duration)
			.ease(cpgf::QuintEase::easeIn())
			.target(cpgf::createAccessor(sprites[1], &GComponentTransform::getScale, &GComponentTransform::setScale), GScale{ 1, 1 })
	);
	t = timeline.append(
		timeline.tween()
			.duration(duration)
			.ease(cpgf::CubicEase::easeIn())
			.relative(cpgf::createAccessor(sprites[2], &GComponentTransform::getPosition, &GComponentTransform::setPosition), GPoint { distanceX, 0 })
	);
	timeline.insert(
		t,
		timeline2
	);

	t = timeline.append(
		timeline.tween()
			.duration(duration)
			.ease(cpgf::BounceEase::easeOut())
			.relative(cpgf::createAccessor(sprites[0], &GComponentTransform::getPosition, &GComponentTransform::setPosition), GPoint{ 0, -distanceY })
	);
	timeline.setAt(t,
		timeline.tween()
			.duration(duration)
			.ease(cpgf::BounceEase::easeOut())
			.relative(cpgf::createAccessor(sprites[1], &GComponentTransform::getPosition, &GComponentTransform::setPosition), GPoint{ 0, distanceY })
	);
	timeline.setAt(t,
		timeline.tween()
			.duration(duration)
			.ease(cpgf::BounceEase::easeOut())
			.relative(cpgf::createAccessor(sprites[2], &GComponentTransform::getPosition, &GComponentTransform::setPosition), GPoint{ 0, -distanceY })
	);

	timeline
		.repeat(cpgf::tweenRepeatInfinitely)
		.yoyo(true)
	;
}


} //unnamed namespace

G_AUTO_RUN_BEFORE_MAIN(TestCase_Tween)
{
	TestBedRegister::getInstance()->registerItem("Tween", &testCaseCreator<TestCase_Tween>);
}
