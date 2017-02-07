#ifndef GRENDERINFO_H
#define GRENDERINFO_H

#include "gincu/gblendmode.h"

namespace gincu {

class GImageData;

struct GRenderInfo
{
	constexpr GRenderInfo()
		: blendMode(), texture(nullptr)
	{}

	GBlendMode blendMode;
	const GImageData * texture;
	
	// will add shader in the future
};

inline bool operator == (const GRenderInfo & a, const GRenderInfo & b)
{
	return a.blendMode == b.blendMode
		&& a.texture == b.texture
	;
}

inline bool operator != (const GRenderInfo & a, const GRenderInfo & b)
{
	return !(a == b);
}


} //namespace gincu


#endif
