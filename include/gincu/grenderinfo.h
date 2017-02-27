#ifndef GRENDERINFO_H
#define GRENDERINFO_H

#include "gincu/gblendmode.h"
#include "gincu/gcolor.h"

namespace gincu {

struct GRenderInfo
{
	constexpr GRenderInfo()
		:
			blendMode(),
			color(colorWhite)
	{}

	GBlendMode blendMode;
	GColor color;
};

inline bool operator == (const GRenderInfo & a, const GRenderInfo & b)
{
	return a.blendMode == b.blendMode
	;
}

inline bool operator != (const GRenderInfo & a, const GRenderInfo & b)
{
	return !(a == b);
}


} //namespace gincu


#endif
