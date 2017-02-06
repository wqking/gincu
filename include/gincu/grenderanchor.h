#ifndef GRENDERANCHOR_H
#define GRENDERANCHOR_H

#include "gincu/ggeometry.h"

namespace gincu {

enum class RenderAnchor
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

inline RenderAnchor operator & (const RenderAnchor a, const RenderAnchor b)
{
	return (RenderAnchor)((int)a & (int)b);
}

inline RenderAnchor operator | (const RenderAnchor a, const RenderAnchor b)
{
	return (RenderAnchor)((int)a | (int)b);
}

GamePoint getOriginByRenderAnchor(const RenderAnchor renderAnchor, const GameSize & size);


} //namespace gincu

#endif
