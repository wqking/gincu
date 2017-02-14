#ifndef GENTITYUTIL_H
#define GENTITYUTIL_H

#include "gincu/gtransform.h"
#include "gincu/gcomponenttransform.h"
#include "gincu/gentity.h"

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
T * getComponentByTypeFromComponent(GComponent * component)
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

GTransform computeRenderableTransform(GComponentTransform * componentTransform, const GSize & size);
GTransform computeRenderableTransform(GComponentTransform * componentTransform, GComponentRender * render = nullptr);

GComponentManager * getComponentManagerFromEntity(const GEntity * entity);
GComponentLocalTransform * getParentLocalTransform(const GEntity * entity);
GEntity * getAncestor(GEntity * entity);


} //namespace gincu

#endif
