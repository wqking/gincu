#ifndef GRENDERINFO_H
#define GRENDERINFO_H

#include "gincu/gblendmode.h"

namespace gincu {

class GTextureData;

struct GRenderInfo
{
	constexpr GRenderInfo()
		: blendMode()
	{}

	GBlendMode blendMode;
	
	// will add shader in the future
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
