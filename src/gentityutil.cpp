#include "gincu/gentityutil.h"
#include "gincu/gcomponenttransform.h"
#include "gincu/gcomponentanchor.h"
#include "gincu/gcomponentrender.h"

namespace gincu {

GMatrix44 computeRenderableMatrix(GComponentTransform * componentTransform, const GSize & size)
{
	GComponentAnchor * anchor = componentTransform->getEntity()->template getComponentByType<GComponentAnchor>();
	if(anchor != nullptr) {
		GMatrix44 matrix = componentTransform->getTransform().getMatrix();
		anchor->apply(matrix, size);
		return matrix;
	}
	else {
		return componentTransform->getTransform().getMatrix();
	}
}

GMatrix44 computeRenderableMatrix(GComponentTransform * componentTransform, GComponentRender * render)
{
	if(render == nullptr) {
		render = componentTransform->getEntity()->getComponentByType<GComponentRender>();
	}
	return computeRenderableMatrix(componentTransform, render->getSize());
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
