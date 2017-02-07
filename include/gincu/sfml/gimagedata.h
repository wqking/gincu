#ifndef GIMAGEDATA_H
#define GIMAGEDATA_H

#include <SFML/Graphics.hpp>

#include <string>

namespace gincu {

class GImageData
{
public:
	void load(const std::string & fileName)
	{
		this->texture.loadFromFile(fileName);
		this->texture.setSmooth(true);
	}

	sf::Texture texture;
};

} //namespace gincu



#endif
