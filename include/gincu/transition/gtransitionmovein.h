#ifndef GTRANSITIONMOVEIN_H
#define GTRANSITIONMOVEIN_H

#include "gincu/transition/gtransition.h"
#include "gincu/ggeometry.h"

#include "cpgf/tween/gtween.h"

#include <memory>

namespace gincu {

class GScene;
class GCameraComponentSaver;

class GTransitionMoveIn : public GTransition
{
public:
	explicit GTransitionMoveIn(unsigned int durationMilliseconds = 500, const GPoint & direction = { 1.0f, 0.0f });
	virtual ~GTransitionMoveIn();
	
private:
	virtual void doFinalize() override;
	virtual void doTransite(GScene * fromScene, GScene * toScene) override;
	void doSetRatio(const float ratio);

private:
	unsigned int durationMilliseconds;
	GPoint direction;
	std::unique_ptr<GCameraComponentSaver> fromSaver;
	std::unique_ptr<GCameraComponentSaver> toSaver;
};


} //namespace gincu


#endif

