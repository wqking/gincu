#ifndef RECTRENDER_H
#define RECTRENDER_H

#include "engine/gamecolor.h"
#include "engine/geometry.h"
#include "engine/renderanchor.h"

#include <memory>

namespace gincu {

class GameTransform;
struct RenderInfo;
class RectRenderResource;
class GameImageResource;

class RectRender
{
public:
	RectRender();
	~RectRender();

	void draw(const GameTransform & transform, const RenderInfo * renderInfo);

	void setColor(const GameColor color);
	GameColor getColor() const;

	void setSize(const GameSize & size);
	GameSize getSize() const;

	const std::shared_ptr<RectRenderResource> & getResource() const { return this->resource; }

	const GameImageResource * getTexture() const { return nullptr; }

private:
	std::shared_ptr<RectRenderResource> resource;
};


} //namespace gincu

#endif
