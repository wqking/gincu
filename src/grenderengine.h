#ifndef GRENDERENGINE_H
#define GRENDERENGINE_H

#include "gincu/ggeometry.h"
#include "gincu/gcolor.h"
#include "gincu/gmatrix.h"
#include "gincu/grendercontext.h"

#include "cpgf/gcallbackList.h"

#include <vector>
#include <map>
#include <memory>

namespace gincu {

class GRenderEngineData;
class GEvent;

class GRenderEngine : public GRenderContext
{
private: // make it private for now, may remove it later.
	// Not singleton. It must be created somewhere, the default is created by GApplication
	static GRenderEngine * getInstance();

public:
	GRenderEngine();
	~GRenderEngine();

	void initialize();
	void finalize();

	void render();

	bool peekEvent(GEvent * event);

	bool isAlive() const;

	const std::shared_ptr<GRenderEngineData> & getData() const { return this->data; }

private: // implement GRenderContext
	virtual void switchCamera(const GCamera & camera) override;
	virtual void draw(const GTexture & texture, const GRect & rect, const GMatrix44 & matrix, const GRenderInfo * renderInfo) override;
	virtual void draw(const GTextRender & text, const GMatrix44 & matrix, const GRenderInfo * renderInfo) override;
	virtual void draw(const GVertexArray & vertexArray, const GPrimitive type, const GTexture & texture, const GMatrix44 & matrix, const GRenderInfo * renderInfo) override;

private:
	void doInitialize();
	void doFinalize();

private:
	std::shared_ptr<GRenderEngineData> data;
};


} //namespace gincu

#endif
