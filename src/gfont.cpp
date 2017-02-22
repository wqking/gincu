#include "gincu/gfont.h"

namespace gincu {

GFont::GFont()
	:
		data()
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
