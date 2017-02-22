#ifndef GSFMLTEXTUREDATA_H
#define GSFMLTEXTUREDATA_H

#include "gincu/gtexture.h"

#include <SFML/Graphics.hpp>

#include <string>

namespace gincu {

class GSfmlTextureData : public GTextureData
{
public:
	virtual void load(const std::string & fileName) override
	{
		this->fileName = fileName;
		this->reload();
	}

	virtual void reload() override
	{
		this->texture = sf::Texture();
		this->texture.loadFromFile(this->fileName);
		this->texture.setSmooth(true);
	}

	virtual GSize getSize() const override
	{
		auto size = this->texture.getSize();
		return { (GCoord)size.x, (GCoord)size.y };
	}
	
	virtual bool isValid() const override
	{
		return true;
	}

	sf::Texture texture;
	std::string fileName;
};

} //namespace gincu



#endif
