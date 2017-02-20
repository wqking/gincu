#include "gincu/transition/gtransitionmovein.h"
#include "gincu/ecs/gcomponentcamera.h"
#include "gincu/gscene.h"

#include "cpgf/tween/gtweenlist.h"
#include "cpgf/accessor/gaccessor.h"

namespace gincu {

GTransitionMoveIn::GTransitionMoveIn()
{
}

GTransitionMoveIn::~GTransitionMoveIn()
{
}

class GCameraComponentBackup
{
public:
	GCameraComponentBackup(GComponentCamera * camera)
		:
			camera(camera),
			viewport(camera->getViewport()),
			fitStrategy(camera->getFitStrategy())
	{
	}
	
	~GCameraComponentBackup() {
		this->camera->setViewport(this->viewport);
		this->camera->setFitStrategy(this->fitStrategy);
	}
	
	GComponentCamera * camera;
	GRect viewport;
	GCameraFitStrategy fitStrategy;
};

void GTransitionMoveIn::doTransite(GScene * fromScene, GScene * toScene)
{
this->finish(); return;
	GComponentCamera * fromCameraComponent = fromScene->getPrimaryCamera();
	GComponentCamera * toCameraComponent = toScene->getPrimaryCamera();
	this->fromBackup.reset(new GCameraComponentBackup(fromCameraComponent));
	this->toBackup.reset(new GCameraComponentBackup(toCameraComponent));

	fromCameraComponent->setFitStrategy(GCameraFitStrategy::none);
	toCameraComponent->setFitStrategy(GCameraFitStrategy::none);
	
	this->getTween()
		.duration(1.0f)
		.target(cpgf::createAccessor(nullptr, 0, &GTransitionMoveIn::doSetRatio), 0.0f, 1.0f)
		.onComplete(cpgf::makeCallback(this, &GTransitionMoveIn::finish))
	;
}

void GTransitionMoveIn::doSetRatio(const float ratio)
{
	const GCoord fromSourceX = this->fromBackup->viewport.x;
	const GCoord fromSourceY = this->fromBackup->viewport.y;
	const GCoord fromTargetX = this->fromBackup->viewport.x + this->fromBackup->viewport.width;
	const GCoord fromTargetY = this->fromBackup->viewport.y;
	const GCoord toSourceX = this->fromBackup->viewport.x - this->toBackup->viewport.width;
	const GCoord toSourceY = this->fromBackup->viewport.y;
	const GCoord toTargetX = this->fromBackup->viewport.x;
	const GCoord toTargetY = this->fromBackup->viewport.y;
	
	this->fromBackup->camera->setViewport({
		fromSourceX + (fromTargetX - fromSourceX) * ratio,
		fromSourceY + (fromTargetY - fromSourceY) * ratio,
		this->fromBackup->viewport.width,
		this->fromBackup->viewport.height
	});
	this->toBackup->camera->setViewport({
		toSourceX + (toTargetX - toSourceX) * ratio,
		toSourceY + (toTargetY - toSourceY) * ratio,
		this->toBackup->viewport.width,
		this->toBackup->viewport.height
	});
}


} //namespace gincu
