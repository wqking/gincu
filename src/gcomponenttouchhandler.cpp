#include "gincu/gcomponenttouchhandler.h"
#include "gincu/gcomponentrender.h"
#include "gincu/gcomponenttransform.h"
#include "gincu/gentity.h"
#include "gincu/gentityutil.h"
#include "gincu/gutil.h"
#include "gincu/grenderanchor.h"

namespace gincu {

GComponentTouchHandler::GComponentTouchHandler()
	:
		super(this),
		onTouchedList(std::make_shared<OnTouchedList>())
{
}

GComponentTouchHandler * GComponentTouchHandler::addOnTouch(const GComponentTouchHandler::OnTouched & onTouch)
{
	this->onTouchedList->add(onTouch);
	
	return this;
}

void GComponentTouchHandler::removeOnTouch(const GComponentTouchHandler::OnTouched & onTouch)
{
	this->onTouchedList->remove(onTouch);
}

bool GComponentTouchHandler::canHandle(const GPoint & point) const
{
	return doCanHandle(point);
}

void GComponentTouchHandler::handle(const GTouchEvent & touchEvent)
{
	// The touch handler may be freed during event handling,
	// so we have to cache the callback list in a local variable.
	auto tempOnTouchedList = this->onTouchedList;
	(*tempOnTouchedList)(touchEvent);
}


GComponentRendererTouchHandler::GComponentRendererTouchHandler()
{
}

bool GComponentRendererTouchHandler::doCanHandle(const GPoint & point) const
{
	GComponentTransform * transform = getEntity()->getComponentByType<GComponentTransform>();
	if(! transform->isVisible()) {
		return false;
	}

	const GTransform t = computeRenderableTransform(transform);
	const GSize size = getEntity()->getComponentByType<GComponentRender>()->getSize();
	const sf::Transform & sfmlTransform = t.getSfmlTransform();

	auto normalizedPoint = sfmlTransform.getInverse().transformPoint({ point.x, point.y });
	return isWithin(normalizedPoint.x, 0, size.width) && isWithin(normalizedPoint.y, 0, size.height);
}


} //namespace gincu
