#include "framework/componenttouchhandler.h"
#include "framework/componentrender.h"
#include "framework/componenttransform.h"
#include "framework/entity.h"
#include "framework/entityutil.h"
#include "framework/util.h"
#include "engine/renderanchor.h"

namespace gincu {

ComponentTouchHandler::ComponentTouchHandler()
	: super(this)
{
}

ComponentTouchHandler * ComponentTouchHandler::addOnTouch(const ComponentTouchHandler::OnTouched & onTouch)
{
	onTouchedList.add(onTouch);
	
	return this;
}

void ComponentTouchHandler::removeOnTouch(const ComponentTouchHandler::OnTouched & onTouch)
{
	onTouchedList.remove(onTouch);
}

bool ComponentTouchHandler::canHandle(const GamePoint & point) const
{
	return doCanHandle(point);
}

void ComponentTouchHandler::handle(const TouchEvent & touchEvent)
{
	OnTouchedList tempOnTouchedList = onTouchedList;
	tempOnTouchedList(touchEvent);
}


ComponentRendererTouchHandler::ComponentRendererTouchHandler()
{
}

bool ComponentRendererTouchHandler::doCanHandle(const GamePoint & point) const
{
	ComponentTransform * transform = getEntity()->getComponentByType<ComponentTransform>();
	if(! transform->isVisible()) {
		return false;
	}

	const GameTransform t = computeRenderableTransform(transform);
	const GameSize size = getEntity()->getComponentByType<ComponentRender>()->getSize();
	const sf::Transform & sfmlTransform = t.getSfmlTransform();
	auto normalizedRect = sfmlTransform.transformRect({ 0, 0, size.width, size.height });
	
	return isWithin(point.x, normalizedRect.left, normalizedRect.left + normalizedRect.width)
		&& isWithin(point.y, normalizedRect.top, normalizedRect.top + normalizedRect.height)
	;
}


} //namespace gincu
