#ifndef GRENDERENGINE_H
#define GRENDERENGINE_H

#include "gincu/ggeometry.h"
#include "gincu/gcolor.h"
#include "gincu/gmatrix.h"

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
class GAtlasRender;
class GCamera;

struct GRenderInfo;
class GEvent;

class GRenderEngine
{
public:
	// Not singleton. It must be created somewhere, the default is created by GApplication
	static GRenderEngine * getInstance();

public:
	GRenderEngine();
	~GRenderEngine();

	void initialize();
	void finalize();

	void render();

	bool peekEvent(GEvent * event);

	void appendRender(const cpgf::GCallback<void ()> & render);
	void removeRender(const cpgf::GCallback<void ()> & render);
	
	bool isAlive() const;

	void switchCamera(const GCamera & camera);
	void draw(const GImage & image, const GMatrix44 & matrix, const GRenderInfo * renderInfo);
	void draw(const GAtlasRender & atlasRender, const GMatrix44 & matrix, const GRenderInfo * renderInfo);
	void draw(const GTextRender & text, const GMatrix44 & matrix, const GRenderInfo * renderInfo);
	void draw(const GRectRender & rect, const GMatrix44 & matrix, const GRenderInfo * renderInfo);

	const std::shared_ptr<GRenderEngineData> & getData() const { return this->data; }

private:
	void doInitialize();
	void doFinalize();
	void doDrawTexture(const std::shared_ptr<GImageData> & texture, const GRect & rect, const GMatrix44 & matrix, const GRenderInfo * renderInfo);

private:
	std::shared_ptr<GRenderEngineData> data;
	cpgf::GCallbackList<void ()> renderList;
};


} //namespace gincu

#endif
