#include "gincu/ecs/gcomponentframeanimation.h"
#include "gincu/ecs/gcomponentrender.h"

#include "cpgf/tween/gtweenlist.h"
#include "cpgf/accessor/gaccessor.h"

namespace gincu {

GComponentFrameAnimation::GComponentFrameAnimation()
	: GComponentFrameAnimation(std::shared_ptr<GFrameAnimationSetData>())
{
}

GComponentFrameAnimation::GComponentFrameAnimation(const std::shared_ptr<GFrameAnimationSetData> & animationSetData)
	:
		animationSetData(animationSetData),
		currentAnimation(nullptr)
{
	if(this->animationSetData && this->animationSetData->getAnimationCount() > 0) {
		this->setAnimation(this->animationSetData->getAnimationNameAt(0));
	}
}

GComponentFrameAnimation::~GComponentFrameAnimation()
{
	this->doRemoveTween();
}

void GComponentFrameAnimation::doSetAnimation(const std::string & name)
{
	this->currentAnimation = this->animationSetData->getAnimationData(name);
	if(this->currentAnimation != nullptr) {
		this->doRestartTween();
	}
	else {
		this->doRemoveTween();
	}
}

void GComponentFrameAnimation::doRemoveTween()
{
	if(this->tween != nullptr) {
		cpgf::GTweenList::getInstance()->remove(*this->tween);
		this->tween = nullptr;
	}
}

void GComponentFrameAnimation::doRestartTween()
{
	this->doRemoveTween();
	
	this->tween = &cpgf::GTweenList::getInstance()->tween();

	this->tween->onDestroy([=](){ this->tween = nullptr; });
	this->tween->useFrames(false);
	this->tween->target(cpgf::createAccessor(this, 0, &GComponentFrameAnimation::doSetRatio), 0.0f, 1.0f);
	this->tween->duration((cpgf::GTweenNumber)this->currentAnimation->getDurationMilliseconds());
}

void GComponentFrameAnimation::doSetRatio(const float ratio)
{
	if(this->currentAnimation != nullptr) {
		auto frameIndexList = this->currentAnimation->getFrameIndexList();
		const int frameCount = (int)frameIndexList.size();
		const int index = (int)((float)frameCount * ratio);
		if(index < frameCount) {
			GComponentAtlasRender * render = this->getEntity()->getComponentByType<GComponentAtlasRender>();
			render->getRender().setIndex(index);
		}
	}
}


} //namespace gincu

