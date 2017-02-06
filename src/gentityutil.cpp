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


} //namespace gincu
