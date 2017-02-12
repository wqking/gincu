#include "gincu/gfont.h"
#include "gfontdata.h"

namespace gincu {

GFont::GFont()
	:
		data(std::make_shared<GFontData>())
{
}

GFont::GFont(const std::shared_ptr<GFontData> & data)
	: data(data)
{
}

GFont::~GFont()
{
}


} //namespace gincu
