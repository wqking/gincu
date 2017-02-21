#include "gincu/transition/gtransitionmovein.h"
#include "gincu/ecs/gcomponentcamera.h"
#include "gincu/gscene.h"

#include "cpgf/tween/gtweenlist.h"
#include "cpgf/accessor/gaccessor.h"

namespace gincu {

GTransitionMoveIn::GTransitionMoveIn(const unsigned int durationMilliseconds, const GPoint & direction)
	: durationMilliseconds(durationMilliseconds), direction(direction)
{
}

GTransitionMoveIn::~GTransitionMoveIn()
{
}

class GCameraComponentSaver
{
public:
	GCameraComponentSaver(GComponentCamera * camera)
		:
			camera(camera),
			viewport(camera->getViewport()),
			fitStrategy(camera->getFitStrategy())
	{
	}
	
	~GCameraComponentSaver() {
		this->camera->setViewport(this->viewport);
		this->camera->setFitStrategy(this->fitStrategy);
	}
	
	GComponentCamera * camera;
	GRect viewport;
	GCameraFitStrategy fitStrategy;
};

void GTransitionMoveIn::doFinalize()
{
	this->fromSaver.reset();
	this->toSaver.reset();
}

void GTransitionMoveIn::doTransite(GScene * fromScene, GScene * toScene)
{
	GComponentCamera * fromCameraComponent = fromScene->getPrimaryCamera();
	GComponentCamera * toCameraComponent = toScene->getPrimaryCamera();
	this->fromSaver.reset(new GCameraComponentSaver(fromCameraComponent));
	this->toSaver.reset(new GCameraComponentSaver(toCameraComponent));

	fromCameraComponent->setFitStrategy(GCameraFitStrategy::none);
	toCameraComponent->setFitStrategy(GCameraFitStrategy::none);
	
	this->getTween()
		.duration(this->durationMilliseconds)
		.target(cpgf::createAccessor(this, 0, &GTransitionMoveIn::doSetRatio), 0.0f, 1.0f)
		.onComplete(cpgf::makeCallback(this, &GTransitionMoveIn::finish))
	;
}

void GTransitionMoveIn::doSetRatio(const float ratio)
{
	const GCoord fromSourceX = this->fromSaver->viewport.x;
	const GCoord fromSourceY = this->fromSaver->viewport.y;
	const GCoord fromTargetX = this->fromSaver->viewport.x + this->fromSaver->viewport.width * this->direction.x;
	const GCoord fromTargetY = this->fromSaver->viewport.y + this->fromSaver->viewport.height * this->direction.y;
	const GCoord toSourceX = this->fromSaver->viewport.x - this->toSaver->viewport.width * this->direction.x;
	const GCoord toSourceY = this->fromSaver->viewport.y - this->toSaver->viewport.height * this->direction.y;
	const GCoord toTargetX = this->toSaver->viewport.x;
	const GCoord toTargetY = this->toSaver->viewport.y;
	
	this->fromSaver->camera->setViewport({
		fromSourceX + (fromTargetX - fromSourceX) * ratio,
		fromSourceY + (fromTargetY - fromSourceY) * ratio,
		this->fromSaver->viewport.width,
		this->fromSaver->viewport.height
	});
	this->toSaver->camera->setViewport({
		toSourceX + (toTargetX - toSourceX) * ratio,
		toSourceY + (toTargetY - toSourceY) * ratio,
		this->toSaver->viewport.width,
		this->toSaver->viewport.height
	});
}


} //namespace gincu
