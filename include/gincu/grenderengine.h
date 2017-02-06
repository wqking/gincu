#ifndef GRENDERENGINE_H
#define GRENDERENGINE_H

#include "gincu/ggeometry.h"
#include "gincu/gcolor.h"

#include <vector>
#include <map>
#include <memory>

namespace gincu {

class GRenderEngineResource;
class GRenderable;
class GTransform;
class GImage;
class GText;
class GRectRender;
struct GRenderInfo;

class GRenderEngine
{
public:
	// Not singleton. It must be created somewhere, the default is created by GApplication
	static GRenderEngine * getInstance();

public:
	GRenderEngine();
	~GRenderEngine();

	void inititialize();

	void render();

	void appendRenderable(GRenderable * renderable);
	void removeRenderable(GRenderable * renderable);
	
	bool isAlive() const;

	void draw(const GImage & image, const GTransform & transform, const GRenderInfo * renderInfo);
	void draw(const GText & text, const GTransform & transform, const GRenderInfo * renderInfo);
	void draw(const GRectRender & rect, const GTransform & transform, const GRenderInfo * renderInfo);

	void beginBatchDraw();
	void endBatchDraw();

	GPoint mapWindowToView(const GPoint & point) const;

	const std::shared_ptr<GRenderEngineResource> & getResource() const { return this->resource; }

public: // for internal usage
	void onWindowResized(const GSize & newSize);

private:
	void doFitView();

private:
	std::shared_ptr<GRenderEngineResource> resource;
	std::vector<GRenderable *> renderableList;
	GSize windowSize;
};


} //namespace gincu

#endif
