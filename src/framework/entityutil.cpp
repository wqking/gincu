#include "framework/entityutil.h"
#include "framework/componenttransform.h"
#include "framework/componentanchor.h"
#include "framework/componentrender.h"

namespace gincu {

GameTransform computeRenderableTransform(
	ComponentTransform * transform,
	ComponentRender * render
)
{
	ComponentAnchor * anchor = transform->getEntity()->template getComponentByType<ComponentAnchor>();
	if(anchor != nullptr) {
		GameTransform t = transform->getTransform();
		if(render == nullptr) {
			render = transform->getEntity()->getComponentByType<ComponentRender>();
		}
		anchor->apply(t, render->getSize());
		return t;
	}
	else {
		return transform->getTransform();
	}
}


} //namespace gincu
