#include "gincu/gcolor.h"

namespace gincu {

GColor gameColorSetAlpha(const GColor color, const int alpha)
{
	return (color & 0x00ffffff) | ((alpha & 0xff) << 24);
}


} //namespace gincu
