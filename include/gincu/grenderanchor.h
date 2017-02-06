#ifndef GRENDERANCHOR_H
#define GRENDERANCHOR_H

#include "gincu/ggeometry.h"

namespace gincu {

enum class GRenderAnchor
{
	none = 0,
	hLeft = 0x01,
	hCenter = 0x02,
	hRight = 0x04,
	hMask = 0x0f,
	vTop = 0x10,
	vCenter = 0x20,
	vBottom = 0x40,
	vMask = 0xf0,

	leftTop = hLeft | vTop,
	center = hCenter | vCenter,
	rightTop = hRight | vTop,
};

inline GRenderAnchor operator & (const GRenderAnchor a, const GRenderAnchor b)
{
	return (GRenderAnchor)((int)a & (int)b);
}

inline GRenderAnchor operator | (const GRenderAnchor a, const GRenderAnchor b)
{
	return (GRenderAnchor)((int)a | (int)b);
}

GPoint getOriginByRenderAnchor(const GRenderAnchor renderAnchor, const GSize & size);


} //namespace gincu

#endif
