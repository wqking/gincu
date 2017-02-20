#ifndef GCOMPONENTFRAMEANIMATION_H
#define GCOMPONENTFRAMEANIMATION_H

#include "gincu/ecs/gcomponentanimation.h"

#include "cpgf/tween/gtween.h"

#include <memory>

namespace gincu {

class GFrameAnimationSetData;
class GFrameAnimationData;

class GComponentFrameAnimation : public GComponentAnimation
{
public:
	GComponentFrameAnimation();
	explicit GComponentFrameAnimation(const std::shared_ptr<GFrameAnimationSetData> & animationSetData);
	~GComponentFrameAnimation();

	cpgf::GTween & getTween() { return *this->tween; }

private:
	void doRemoveTween();
	void doRestartTween();
	void doSetRatio(const float ratio);

private:
	virtual void doSetAnimation(const std::string & name) override;

private:
	std::shared_ptr<GFrameAnimationSetData> animationSetData;
	const GFrameAnimationData * currentAnimation;
	cpgf::GTween * tween;
};


} //namespace gincu


#endif

