#ifndef ENTITYUTIL_H
#define ENTITYUTIL_H

#include "engine/gametransform.h"

namespace gincu {

class ComponentTransform;
class ComponentRender;

GameTransform computeRenderableTransform(
		ComponentTransform * transform,
		ComponentRender * render = nullptr
	);


} //namespace gincu

#endif
