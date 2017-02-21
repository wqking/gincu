#ifndef GTRANSITIONFADEINOUT_H
#define GTRANSITIONFADEINOUT_H

#include "gincu/transition/gtransition.h"
#include "gincu/ggeometry.h"
#include "gincu/gcolor.h"
#include "gincu/ecs/gcomponentrender.h"

#include "cpgf/tween/gtween.h"

#include <memory>

namespace gincu {

class GScene;

class GTransitionFadeInOut : public GTransition
{
public:
	explicit GTransitionFadeInOut(unsigned int durationMilliseconds = 500, const GColor color = colorWhite);
	virtual ~GTransitionFadeInOut();
	
private:
	virtual void doFinalize() override;
	virtual void doTransite(GScene * fromScene, GScene * toScene) override;
	void doSetRatio(const float ratio);

private:
	unsigned int durationMilliseconds;
	GColor color;
	GScene * fromScene;
	GScene * toScene;
	GComponentRectRender * fromRender;
	GComponentRectRender * toRender;
};


} //namespace gincu


#endif

