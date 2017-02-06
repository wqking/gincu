#ifndef GIMAGERESOURCE_H
#define GIMAGERESOURCE_H

#include <SFML/Graphics.hpp>

#include <string>

namespace gincu {

class GImageResource
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
