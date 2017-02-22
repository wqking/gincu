#ifndef GDEVICECONTEXT_H
#define GDEVICECONTEXT_H

#include "gincu/gobjectfactory.h"

#include <memory>

namespace gincu {

class GRenderContext;
class GEvent;
struct GConfigInfo;

class GTextRenderData;
class GVertexArrayData;
class GFontData;
class GTextureData;
class GCameraData;
class GFileInputStreamData;

class GDeviceContext
{
public:
	static GDeviceContext * getInstance();

public:
	GDeviceContext();
	virtual ~GDeviceContext();

	virtual void initialize(const GConfigInfo & configInfo) = 0;
	virtual void finalize() = 0;
	virtual GRenderContext * getRenderContext() const = 0;
	virtual bool getEvent(GEvent * event) const = 0;
	virtual bool isFinished() const = 0;
	
	virtual std::shared_ptr<GTextRenderData> createTextRenderData(const GTextRenderData * copy) const = 0;
	virtual std::shared_ptr<GVertexArrayData> createVertexArrayData(const GVertexArrayData * copy) const = 0;
	virtual std::shared_ptr<GFontData> createFontData(const GFontData * copy) const = 0;
	virtual std::shared_ptr<GTextureData> createTextureData(const GTextureData * copy) const = 0;
	virtual std::shared_ptr<GCameraData> createCameraData(const GCameraData * copy) const = 0;
	virtual std::shared_ptr<GFileInputStreamData> createFileInputStreamData() const = 0;
};

class GDeviceContextRegister : public GObjectFactory<GDeviceContext>
{
public:
	static GDeviceContextRegister * getInstance();
};


} //namespace gincu


#endif
