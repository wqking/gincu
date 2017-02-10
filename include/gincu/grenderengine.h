#ifndef GRENDERENGINE_H
#define GRENDERENGINE_H

#include "gincu/ggeometry.h"
#include "gincu/gcolor.h"

#include "cpgf/gcallbackList.h"

#include <vector>
#include <map>
#include <memory>

namespace gincu {

class GRenderEngineData;
class GImageData;
class GTransform;
class GImage;
class GTextRender;
class GRectRender;
class GSpriteSheetRender;
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

	void appendRender(const cpgf::GCallback<void ()> & render);
	void removeRender(const cpgf::GCallback<void ()> & render);
	
	bool isAlive() const;

	void draw(const GImage & image, const GTransform & transform, const GRenderInfo * renderInfo);
	void draw(const GSpriteSheetRender & spriteSheetRender, const GTransform & transform, const GRenderInfo * renderInfo);
	void draw(const GTextRender & text, const GTransform & transform, const GRenderInfo * renderInfo);
	void draw(const GRectRender & rect, const GTransform & transform, const GRenderInfo * renderInfo);

	void beginBatchDraw();
	void endBatchDraw();

	GPoint mapWindowToView(const GPoint & point) const;

	const std::shared_ptr<GRenderEngineData> & getData() const { return this->data; }

public: // for internal usage
	void onWindowResized(const GSize & newSize);

private:
	void doInitialize();
	void doFinalize();
	void flush();
	void doDrawTexture(const std::shared_ptr<GImageData> & texture, const GRect & rect, const GTransform & transform, const GRenderInfo * renderInfo);

	void doFitView();

private:
	std::shared_ptr<GRenderEngineData> data;
	cpgf::GCallbackList<void ()> renderList;
	GSize windowSize;
};


} //namespace gincu

#endif
