#ifndef GTEXTUREDATA_H
#define GTEXTUREDATA_H

#include <SFML/Graphics.hpp>

#include <string>

namespace gincu {

class GTextureData
{
public:
	void load(const std::string & fileName)
	{
		this->fileName = fileName;
		this->reload();
	}

	void reload()
	{
		this->texture = sf::Texture();
		this->texture.loadFromFile(this->fileName);
		this->texture.setSmooth(true);
	}

	sf::Texture texture;
	std::string fileName;
};

} //namespace gincu



#endif
