#ifndef GIMAGE_H
#define GIMAGE_H

#include "gincu/ggeometry.h"
#include "gincu/grenderanchor.h"

#include <string>
#include <memory>

namespace gincu {

class GameTransform;
struct RenderInfo;
class GameImageResource;

class GameImage
{
public:
	GameImage();
	~GameImage();
	explicit GameImage(const std::shared_ptr<GameImageResource> & resource);
	GameImage(const std::shared_ptr<GameImageResource> & resource, const GameRect & rect);

	void load(const std::string & fileName);

	void draw(const GameTransform & transform, const RenderInfo * renderInfo);

	GameSize getSize() const;

	void setResource(const std::shared_ptr<GameImageResource> & resource);
	const std::shared_ptr<GameImageResource> & getResource() const { return this->resource; }

	void setRect(const GameRect & rect) { this->rect = rect; }
	const GameRect & getRect() const { return this->rect; }

	bool isValid() const { return this->resource.get() != nullptr; }

	const GameImageResource * getTexture() const { return this->resource.get(); }

private:
	std::shared_ptr<GameImageResource> resource;
	GameRect rect;
};


} //namespace gincu

#endif
