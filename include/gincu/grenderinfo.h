#ifndef GRENDERINFO_H
#define GRENDERINFO_H

#include "gincu/gblendmode.h"

namespace gincu {

class GameImageResource;

struct RenderInfo
{
	constexpr RenderInfo()
		: blendMode(), texture(nullptr)
	{}

	GameBlendMode blendMode;
	const GameImageResource * texture;
	
	// will add shader in the future
};

inline bool operator == (const RenderInfo & a, const RenderInfo & b)
{
	return a.blendMode == b.blendMode
		&& a.texture == b.texture
	;
}

inline bool operator != (const RenderInfo & a, const RenderInfo & b)
{
	return !(a == b);
}


} //namespace gincu


#endif
