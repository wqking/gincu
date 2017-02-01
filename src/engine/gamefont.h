#ifndef GAMEFONT_H
#define GAMEFONT_H

#include <memory>

namespace gincu {

class GameFontResource;

class GameFont
{
public:
	GameFont();
	~GameFont();

	void setResource(const std::shared_ptr<GameFontResource> & resource) { this->resource = resource; }
	const std::shared_ptr<GameFontResource> & getResource() const { return this->resource; }

private:
	std::shared_ptr<GameFontResource> resource;
};


} //namespace gincu

#endif
