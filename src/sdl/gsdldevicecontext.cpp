#include "gincu/gdevicecontext.h"
#include "gincu/gevent.h"
#include "gincu/glog.h"
#include "gincu/gconfiginfo.h"

#include "gsdlrendercontext.h"
#include "gsdltextrenderdata.h"
#include "gsdlvertexarraydata.h"
#include "gsdlfontdata.h"
#include "gsdltexturedata.h"
#include "gsdlcameradata.h"
#include "gsdlfileinputstreamdata.h"

#include "cpgf/goutmain.h"

#include "SDL_gpu.h"

#include <memory>

namespace gincu {

class GSdlDeviceContext : public GDeviceContext
{
private:
	virtual void initialize(const GConfigInfo & configInfo) override;
	virtual void finalize() override;
	virtual GRenderContext * getRenderContext() const override;
	virtual bool getEvent(GEvent * event) const override;
	virtual bool isFinished() const override;

	virtual std::shared_ptr<GTextRenderData> createTextRenderData(const GTextRenderData * copy) const override;
	virtual std::shared_ptr<GVertexArrayData> createVertexArrayData(const GVertexArrayData * copy) const override;
	virtual std::shared_ptr<GFontData> createFontData(const GFontData * copy) const override;
	virtual std::shared_ptr<GTextureData> createTextureData(const GTextureData * copy) const override;
	virtual std::shared_ptr<GCameraData> createCameraData(const GCameraData * copy) const override;
	virtual std::shared_ptr<GFileInputStreamData> createFileInputStreamData() const override;

private:
	GPU_Target * window;
	std::unique_ptr<GSdlRenderContext> renderContext;
};

void GSdlDeviceContext::initialize(const GConfigInfo & configInfo)
{
	this->window = GPU_Init((int)configInfo.windowSize.width, (int)configInfo.windowSize.height, GPU_DEFAULT_INIT_FLAGS);

	G_LOG_INFO("Render window is created.");
	
	this->renderContext.reset(new GSdlRenderContext());
	this->renderContext->initialize(this->window);
}

void GSdlDeviceContext::finalize()
{
	this->renderContext->finalize();
}

GRenderContext * GSdlDeviceContext::getRenderContext() const
{
	return this->renderContext.get();
}

bool GSdlDeviceContext::getEvent(GEvent * event) const
{
	SDL_Event e;

	if(! SDL_PollEvent(&e)) {
		return false;
	}

	switch(e.type) {
	case SDL_QUIT:
		*event = GEvent(GEventType::windowClosed);
		break;

	case SDL_MOUSEBUTTONDOWN:
	case SDL_MOUSEBUTTONUP: {
		GTouchEvent touchEvent = GTouchEvent();
		touchEvent.down = (e.type == SDL_MOUSEBUTTONDOWN);
		touchEvent.screenPosition = {(GCoord)e.button.x, (GCoord)e.button.y};
		*event = GEvent((e.type == SDL_MOUSEBUTTONDOWN ? GEventType::touchPressed : GEventType::touchReleased), touchEvent);
		break;
	}

	case SDL_MOUSEMOTION: {
		GTouchEvent touchEvent = GTouchEvent();
		touchEvent.down = (e.motion.state == SDL_PRESSED);
		touchEvent.screenPosition = {(GCoord)e.motion.x, (GCoord)e.motion.y};
		*event = GEvent(GEventType::touchMoved, touchEvent);
		break;
	}
	}

	return true;
}

bool GSdlDeviceContext::isFinished() const
{
	return false;
}

std::shared_ptr<GTextRenderData> GSdlDeviceContext::createTextRenderData(const GTextRenderData * copy) const
{
	if(copy == nullptr) {
		return std::make_shared<GSdlTextRenderData>();
	}
	else {
		return std::make_shared<GSdlTextRenderData>(*static_cast<const GSdlTextRenderData *>(copy));
	}
}

std::shared_ptr<GVertexArrayData> GSdlDeviceContext::createVertexArrayData(const GVertexArrayData * copy) const
{
	if(copy == nullptr) {
		return std::make_shared<GSdlVertexArrayData>();
	}
	else {
		return std::make_shared<GSdlVertexArrayData>(*static_cast<const GSdlVertexArrayData *>(copy));
	}
}

std::shared_ptr<GFontData> GSdlDeviceContext::createFontData(const GFontData * copy) const
{
	if(copy == nullptr) {
		return std::make_shared<GSdlFontData>();
	}
	else {
		return std::make_shared<GSdlFontData>(*static_cast<const GSdlFontData *>(copy));
	}
}

std::shared_ptr<GTextureData> GSdlDeviceContext::createTextureData(const GTextureData * copy) const
{
	if(copy == nullptr) {
		return std::make_shared<GSdlTextureData>();
	}
	else {
		return std::make_shared<GSdlTextureData>(*static_cast<const GSdlTextureData *>(copy));
	}
}

std::shared_ptr<GCameraData> GSdlDeviceContext::createCameraData(const GCameraData * copy) const
{
	if(copy == nullptr) {
		return std::make_shared<GSdlCameraData>();
	}
	else {
		return std::make_shared<GSdlCameraData>(*static_cast<const GSdlCameraData *>(copy));
	}
}

std::shared_ptr<GFileInputStreamData> GSdlDeviceContext::createFileInputStreamData() const
{
	return std::make_shared<GSdlFileInputStreamData>();
}


G_AUTO_RUN_BEFORE_MAIN(GSdlDeviceContext)
{
	GDeviceContextRegister::getInstance()->registerObject(
		"sdl",
		&objectFactoryCreator<GSdlDeviceContext>
	);
}



} //namespace gincu