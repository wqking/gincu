#ifndef GCOMPONENTANIMATION_H
#define GCOMPONENTANIMATION_H

#include "gincu/ecs/gcomponent.h"
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

	void setAnimation(const std::string & name) {
		this->doSetAnimation(name);
	}

private:
	virtual void doSetAnimation(const std::string & name) = 0;
};


} //namespace gincu


#endif
