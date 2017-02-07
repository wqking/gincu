#include "gincu/gfont.h"
#include "gincu/sfml/gfontdata.h"

namespace gincu {

GFont::GFont()
	:
		data(std::make_shared<GFontData>())
{
}

GFont::~GFont()
{
}


} //namespace gincu
