#include "engine/gamefont.h"
#include "engine/sfml/gamefontresource.h"

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
