#ifndef GENTITYUTIL_H
#define GENTITYUTIL_H

#include "gincu/gtransform.h"
#include "gincu/gcomponenttransform.h"

namespace gincu {

class GComponentRender;

GTransform computeRenderableTransform(
		GComponentTransform * transform,
		GComponentRender * render = nullptr
	);

template <typename Callback>
void enumerateEntityChildren(GComponentLocalTransform * localTransform, const Callback callback)
{
	if(localTransform != nullptr) {
		for(int i = 0; i < localTransform->getChildCount(); ++i) {
			callback(localTransform->getChildAt(i));
		}
	}
}


} //namespace gincu

#endif
