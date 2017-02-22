#ifndef GFONTDATA_H
#define GFONTDATA_H

#include "gincu/gfont.h"

#include <SFML/Graphics.hpp>

namespace gincu {

class GSfmlFontData : public GFontData
{
public:
	virtual void load(const std::string & fileName) override
	{
		this->font.loadFromFile(fileName);
	}

	sf::Font font;
};


} //namespace gincu



#endif
