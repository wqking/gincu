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
#include "gincu/gapplication.h"
#include "gincu/gscenemanager.h"
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

	GComponentTweenedFrameAnimation * createAnimation(GEntity * entity, const std::string & atlasName);
	GEntity * createAnimationEntity(const GPoint & position, const std::string & atlasName);
	GPoint getRandomPosition() const;
};

void TestCase_Benchmark::doInitialize()
{
	this->doBenchmarkBatchedAnimation();
//	this->doBenchmarkUnbatchedAnimation();
}

GComponentTweenedFrameAnimation * TestCase_Benchmark::createAnimation(GEntity * entity, const std::string & atlasName)
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

GEntity * TestCase_Benchmark::createAnimationEntity(const GPoint & position, const std::string & atlasName)
{
	GEntity * entity;

	entity = new GEntity();
	this->getScene()->addEntity(
		entity
		->addComponent(createComponent<GComponentTransform>(position))
		->addComponent(createComponent<GComponentAnchor>(GRenderAnchor::center))
		->addComponent(createAtlasRenderComponent(GResourceManager::getInstance()->getAtlas(atlasName, GAtlasFormat::spritePackText), ""))
		->addComponent(createAnimation(entity, atlasName))
	);

	return entity;
}

GPoint TestCase_Benchmark::getRandomPosition() const
{
	const GSize viewSize = GApplication::getInstance()->getViewSize();

	return { (GCoord)getRand((int)viewSize.width), (GCoord)getRand((int)viewSize.height) };
}

void TestCase_Benchmark::doBenchmarkBatchedAnimation()
{
	constexpr int iterateCount = 1000;
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
