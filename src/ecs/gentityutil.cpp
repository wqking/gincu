#include "gincu/ecs/gentityutil.h"
#include "gincu/ecs/gcomponenttransform.h"
#include "gincu/ecs/gcomponentlocaltransform.h"
#include "gincu/ecs/gcomponentanchor.h"
#include "gincu/ecs/gcomponentrender.h"

namespace gincu {

GMatrix44 computeRenderableMatrix(const GComponentTransform * componentTransform, const GSize & size)
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

GMatrix44 computeRenderableMatrix(const GComponentTransform * componentTransform, const GComponentRender * render)
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
		const GComponentLocalTransform * localTransform = entity->getComponentByType<GComponentLocalTransform>();
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

int getZOrder(GEntity * entity)
{
	GComponentLocalTransform * localTransform = entity->getComponentByType<GComponentLocalTransform>();
	if(localTransform != nullptr) {
		return localTransform->getZOrder();
	}
	
	GComponentTransform * transform = entity->getComponentByType<GComponentTransform>();
	if(transform != nullptr) {
		return transform->getZOrder();
	}
	
	return 0;
}


} //namespace gincu
