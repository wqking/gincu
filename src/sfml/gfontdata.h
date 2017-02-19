#ifndef GFONTDATA_H
#define GFONTDATA_H

#include <SFML/Graphics.hpp>

namespace gincu {

class GFontData
{
public:
	void load(const std::string & fileName)
	{
		this->font.loadFromFile(fileName);
	}

	sf::Font font;
};


} //namespace gincu



#endif
