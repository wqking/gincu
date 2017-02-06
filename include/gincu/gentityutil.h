#ifndef GENTITYUTIL_H
#define GENTITYUTIL_H

#include "gincu/gtransform.h"

namespace gincu {

class GComponentTransform;
class GComponentRender;

GTransform computeRenderableTransform(
		GComponentTransform * transform,
		GComponentRender * render = nullptr
	);


} //namespace gincu

#endif
