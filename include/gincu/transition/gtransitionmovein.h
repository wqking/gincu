#ifndef GTRANSITIONMOVEIN_H
#define GTRANSITIONMOVEIN_H

#include "gincu/transition/gtransition.h"

#include "cpgf/tween/gtween.h"

#include <memory>

namespace gincu {

class GScene;
class GCameraComponentBackup;

class GTransitionMoveIn : public GTransition
{
public:
	GTransitionMoveIn();
	virtual ~GTransitionMoveIn();
	
private:
	virtual void doTransite(GScene * fromScene, GScene * toScene) override;
	void doSetRatio(const float ratio);

private:
	std::unique_ptr<GCameraComponentBackup> fromBackup;
	std::unique_ptr<GCameraComponentBackup> toBackup;
};


} //namespace gincu


#endif

