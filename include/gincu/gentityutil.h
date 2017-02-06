#ifndef GENTITYUTIL_H
#define GENTITYUTIL_H

#include "gincu/gtransform.h"

namespace gincu {

class ComponentTransform;
class ComponentRender;

GameTransform computeRenderableTransform(
		ComponentTransform * transform,
		ComponentRender * render = nullptr
	);


} //namespace gincu

#endif
