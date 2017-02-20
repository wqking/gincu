#ifndef GENTITYUTIL_H
#define GENTITYUTIL_H

#include "gincu/gtransform.h"
#include "gincu/ecs/gcomponenttransform.h"
#include "gincu/ecs/gcomponentlocaltransform.h"
#include "gincu/ecs/gentity.h"
#include "gincu/gmatrix.h"

namespace gincu {

template <typename Callback>
void enumerateEntityChildren(GComponentLocalTransform * localTransform, const Callback callback)
{
	if(localTransform != nullptr) {
		for(int i = 0; i < localTransform->getChildCount(); ++i) {
			callback(localTransform->getChildAt(i));
		}
	}
}

template <typename T>
T * getComponentByTypeFromComponent(const GComponent * component)
{
	if(component != nullptr) {
		GEntity * entity = component->getEntity();
		if(entity != nullptr) {
			return entity->getComponentByType<T>();
		}
	}

	return nullptr;
}

class GComponentRender;
class GEntity;
class GComponentManager;

GMatrix44 computeRenderableMatrix(const GComponentTransform * componentTransform, const GSize & size);
GMatrix44 computeRenderableMatrix(const GComponentTransform * componentTransform, const GComponentRender * render = nullptr);

GComponentManager * getComponentManagerFromEntity(const GEntity * entity);
GComponentLocalTransform * getParentLocalTransform(const GEntity * entity);
GEntity * getAncestor(GEntity * entity);
int getZOrder(GEntity * entity);


} //namespace gincu

#endif
