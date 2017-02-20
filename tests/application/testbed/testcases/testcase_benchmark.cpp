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
#include "gincu/gapplication.h"
#include "gincu/gscenemanager.h"
#include "gincu/grenderanchor.h"
#include "gincu/gutil.h"

#include "cpgf/goutmain.h"

#include <vector>

namespace {

using namespace gincu;

const std::vector<std::string> animationNames { "testbed/animation_yellow_boy", "testbed/animation_running_man" };

class TestCase_Benchmark : public TestCase
{
private:
	virtual void doInitialize() override;

private:
	void doBenchmarkBatchedAnimation();
	void doBenchmarkUnbatchedAnimation();

	GEntity * createAnimationEntity(const GPoint & position, const std::string & atlasName);
	GPoint getRandomPosition() const;
};

void TestCase_Benchmark::doInitialize()
{
	this->doBenchmarkBatchedAnimation();
//	this->doBenchmarkUnbatchedAnimation();
}

GEntity * TestCase_Benchmark::createAnimationEntity(const GPoint & position, const std::string & atlasName)
{
	return this->getScene()->addEntity(
		(new GEntity())
		->addComponent(createComponent<GComponentTransform>(position))
		->addComponent(createComponent<GComponentAnchor>(GRenderAnchor::center))
		->addComponent(createAtlasRenderComponent(GResourceManager::getInstance()->getAtlas(atlasName, GAtlasFormat::spritePackText), ""))
		->addComponent(createAnimation(atlasName))
	);
}

GPoint TestCase_Benchmark::getRandomPosition() const
{
	const GSize viewSize = this->getScene()->getPrimaryCamera()->getWorldSize();

	return { (GCoord)getRand((int)viewSize.width), (GCoord)getRand((int)viewSize.height) };
}

void TestCase_Benchmark::doBenchmarkBatchedAnimation()
{
	constexpr int iterateCount = 10000;
	const int animationCount = (int)animationNames.size();

	for(int a = 0; a < animationCount; ++a) {
		for(int i = 0; i < iterateCount / animationCount; ++i) {
			this->createAnimationEntity(this->getRandomPosition(), animationNames[a]);
		}
	}
}

void TestCase_Benchmark::doBenchmarkUnbatchedAnimation()
{
	constexpr int iterateCount = 1000;
	const int animationCount = (int)animationNames.size();

	for(int i = 0; i < iterateCount / animationCount; ++i) {
		for(int a = 0; a < animationCount; ++a) {
			this->createAnimationEntity(this->getRandomPosition(), animationNames[a]);
		}
	}
}


G_AUTO_RUN_BEFORE_MAIN(TestCase_Benchmark)
{
	TestBedRegister::getInstance()->registerItem("Benchmark", &testCaseCreator<TestCase_Benchmark>);
}


} //unnamed namespace
