#include "gincu/gfont.h"
#include "gincu/sfml/gfontresource.h"

namespace gincu {

GFont::GFont()
	:
		resource(std::make_shared<GFontResource>())
{
}

GFont::~GFont()
{
}


} //namespace gincu
