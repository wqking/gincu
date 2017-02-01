#ifndef RECTRENDER_H
#define RECTRENDER_H

#include "engine/gamecolor.h"
#include "engine/geometry.h"
#include "engine/renderanchor.h"

#include <memory>

namespace gincu {

class GameTransform;
class RectRenderResource;

class RectRender
{
public:
	RectRender();
	~RectRender();

	void draw(const GameTransform & transform);

	void setColor(const GameColor color);
	GameColor getColor() const;

	void setSize(const GameSize & size);
	GameSize getSize() const;

	const std::shared_ptr<RectRenderResource> & getResource() const { return this->resource; }

private:
	std::shared_ptr<RectRenderResource> resource;
};


} //namespace gincu

#endif
