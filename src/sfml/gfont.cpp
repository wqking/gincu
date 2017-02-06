#include "gincu/gfont.h"
#include "gincu/sfml/gfontresource.h"

namespace gincu {

GameFont::GameFont()
	:
		resource(std::make_shared<GameFontResource>())
{
}

GameFont::~GameFont()
{
}


} //namespace gincu
