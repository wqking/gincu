#include "gincu/transition/gtransitionfadeinout.h"
#include "gincu/ecs/gcomponentcamera.h"
#include "gincu/gscene.h"
#include "gincu/gapplication.h"
#include "gincu/ecs/gcomponentanchor.h"
#include "gincu/grenderanchor.h"

#include "cpgf/tween/gtweenlist.h"
#include "cpgf/accessor/gaccessor.h"

namespace gincu {

GTransitionFadeInOut::GTransitionFadeInOut(const unsigned int durationMilliseconds, const GColor color)
	:
		durationMilliseconds(durationMilliseconds),
		color(color),
		fromScene(nullptr),
		toScene(nullptr),
		fromRender(nullptr),
		toRender(nullptr)
{
}

GTransitionFadeInOut::~GTransitionFadeInOut()
{
}

void GTransitionFadeInOut::doFinalize()
{
	if(this->fromScene != nullptr) {
		this->fromScene->enableRender(false);
	
	if(this->fromRender != nullptr) {
			this->fromScene->removeEntity(this->fromRender->getEntity());
		}
	}

	if(this->toScene != nullptr && this->toRender != nullptr) {
		this->toScene->removeEntity(this->toRender->getEntity());
	}
}

void GTransitionFadeInOut::doTransite(GScene * fromScene, GScene * toScene)
{
	this->fromScene = fromScene;
	this->toScene = toScene;
	
	const GSize size = GApplication::getInstance()->getScreenSize();

	this->fromScene->addEntity(
		(new GEntity())
		->addComponent(createComponent<GComponentTransform>()->setZOrder(std::numeric_limits<int>::max()))
		->addComponent((this->fromRender = createRectRenderComponent(colorSetAlpha(this->color, 0), size)))
	);
	GComponentAnchor * fromAnchor = this->fromScene->getPrimaryCamera()->getEntity()->getComponentByType<GComponentAnchor>();
	if(fromAnchor != nullptr) {
		this->fromRender->getEntity()->addComponent(
			createComponent<GComponentAnchor>(fromAnchor->getAnchor())->setFlipX(fromAnchor->isFlipX())->setFlipY(fromAnchor->isFlipY())
		);
	}
	
	this->toScene->addEntity(
		(new GEntity())
		->addComponent(createComponent<GComponentTransform>(this->toScene->getPrimaryCamera()->getCamera().mapScreenToWorld(GPoint()))->setZOrder(std::numeric_limits<int>::max()))
		->addComponent((this->toRender = createRectRenderComponent(this->color, size)))
	);
	GComponentAnchor * toAnchor = this->toScene->getPrimaryCamera()->getEntity()->getComponentByType<GComponentAnchor>();
	if(toAnchor != nullptr) {
		this->toRender->getEntity()->addComponent(
			createComponent<GComponentAnchor>(toAnchor->getAnchor())->setFlipX(toAnchor->isFlipX())->setFlipY(toAnchor->isFlipY())
		);
	}
	
	this->toScene->enableRender(false);

	this->getTween()
		.duration((cpgf::GTweenNumber)this->durationMilliseconds)
		.target(cpgf::createAccessor(this, 0, &GTransitionFadeInOut::doSetRatio), 0.0f, 255.0f * 2.0f)
		.onComplete(cpgf::makeCallback(this, &GTransitionFadeInOut::finish))
	;
}

void GTransitionFadeInOut::doSetRatio(const float ratio)
{
	if(ratio <= 255.0f) {
		this->fromRender->setColor(colorSetAlpha(this->fromRender->getRender().getColor(), (unsigned int)ratio));
	}
	else {
		this->fromScene->enableRender(false);
		this->toScene->enableRender(true);
		this->toRender->setColor(colorSetAlpha(this->toRender->getRender().getColor(), 255 * 2 - (unsigned int)ratio));
	}
}


} //namespace gincu
