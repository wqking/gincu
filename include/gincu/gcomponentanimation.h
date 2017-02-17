#ifndef GCOMPONENTANIMATION_H
#define GCOMPONENTANIMATION_H

#include "gincu/gcomponent.h"
#include "gincu/gframeanimation.h"

namespace gincu {

class GComponentAnimation : public GComponent
{
private:
	typedef GComponent super;

public:
	inline static constexpr GComponentType getComponentType() {
		return GComponentType::animation;
	}

public:
	GComponentAnimation() : super(this) {}

	void update() {
		this->doUpdate();
	}

private:
	virtual void doUpdate() = 0;
};


template <typename AnimationType>
class GComponentAnimationCommon : public GComponentAnimation
{
public:
	GComponentAnimationCommon() {}
	explicit GComponentAnimationCommon(const AnimationType & animation) : animation(animation) {}

private:
	virtual void doUpdate() override {
		this->animation.update();
	}

private:
	AnimationType animation;
};

typedef GComponentAnimationCommon<GTweenedFrameAnimation> GComponentTweenedFrameAnimation;


} //namespace gincu


#endif
