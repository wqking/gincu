#ifndef GAMEIMAGE_H
#define GAMEIMAGE_H

#include "engine/geometry.h"
#include "engine/renderanchor.h"

#include <string>
#include <memory>

namespace gincu {

class GameTransform;

class GameImageResource;

class GameImage
{
public:
	GameImage();
	~GameImage();

	void load(const std::string & fileName);

	void draw(const GameTransform & transform);

	GameSize getSize() const;

	void setResource(const std::shared_ptr<GameImageResource> & resource) { this->resource = resource; }
	const std::shared_ptr<GameImageResource> & getResource() const { return this->resource; }

private:
	std::shared_ptr<GameImageResource> resource;
};


} //namespace gincu

#endif
