#include "gincu/gentityutil.h"
#include "gincu/gcomponenttransform.h"
#include "gincu/gcomponentanchor.h"
#include "gincu/gcomponentrender.h"

namespace gincu {

GTransform computeRenderableTransform(
	GComponentTransform * transform,
	GComponentRender * render
)
{
	GComponentAnchor * anchor = transform->getEntity()->template getComponentByType<GComponentAnchor>();
	if(anchor != nullptr) {
		GTransform t = transform->getTransform();
		if(render == nullptr) {
			render = transform->getEntity()->getComponentByType<GComponentRender>();
		}
		anchor->apply(t, render->getSize());
		return t;
	}
	else {
		return transform->getTransform();
	}
}

GComponentManager * getComponentManagerFromEntity(const GEntity * entity)
{
	if(entity != nullptr) {
		return entity ->getComponentManager();
	}
	else {
		return nullptr;
	}
}

GComponentLocalTransform * getParentLocalTransform(const GEntity * entity)
{
	if(entity != nullptr) {
		GComponentLocalTransform * localTransform = entity->getComponentByType<GComponentLocalTransform>();
		if(localTransform != nullptr) {
			return localTransform->getParent();
		}
	}

	return nullptr;
}

GEntity * getAncestor(GEntity * entity)
{
	GEntity * ancestor = entity;

	for(;;) {
		GComponentLocalTransform * localTransform = ancestor->getComponentByType<GComponentLocalTransform>();
		if(localTransform != nullptr) {
			ancestor = localTransform->getParent()->getEntity();
		}
		else {
			break;
		}
	}

	return ancestor;
}


} //namespace gincu
