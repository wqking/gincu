#ifndef GALLEGROUTIL_H
#define GALLEGROUTIL_H

#include "gincu/gcolor.h"
#include "gincu/ggeometry.h"
#include "gincu/gblendmode.h"
#include "gincu/grenderinfo.h"
#include "gincu/gmatrix.h"
#include "gincu/gprimitive.h"

#include "allegro5/allegro.h"
#include "allegro5/allegro_primitives.h"

namespace gincu {

inline ALLEGRO_COLOR gameColorToAllegro(const GColor color)
{
	return al_map_rgba(
		colorGetRed(color),
		colorGetGreen(color),
		colorGetBlue(color),
		colorGetAlpha(color)
	);
}

inline GColor allegroColorToGame(const ALLEGRO_COLOR & color)
{
	unsigned char r, g, b, a;
	al_unmap_rgba(color, &r, &g, &b, &a);
	return colorMakeARGB(a, r, g, b);
}

inline void allegroApplyProjectionMatrix(const GMatrix44 & matrix)
{
	al_use_projection_transform((ALLEGRO_TRANSFORM *)&matrix[0][0]);
}

inline ALLEGRO_PRIM_TYPE primitiveToAllegro(const GPrimitive primitive)
{
	switch(primitive) {
	case GPrimitive::points: return ALLEGRO_PRIM_POINT_LIST;
	case GPrimitive::lines: return ALLEGRO_PRIM_LINE_LIST;
	case GPrimitive::lineStrip: return ALLEGRO_PRIM_LINE_STRIP;
	case GPrimitive::triangles: return ALLEGRO_PRIM_TRIANGLE_LIST;
	case GPrimitive::triangleStrip: return ALLEGRO_PRIM_TRIANGLE_STRIP;
	case GPrimitive::triangleFan: return ALLEGRO_PRIM_TRIANGLE_FAN;
	}

	return ALLEGRO_PRIM_TRIANGLE_LIST;
}


} //namespace gincu



#endif

