#include "gincu/gdevicecontext.h"
#include "gincu/gevent.h"
#include "gincu/glog.h"
#include "gincu/gconfiginfo.h"

#include "gallegrorendercontext.h"
#include "gallegrotextrenderdata.h"
#include "gallegrovertexarraydata.h"
#include "gallegrofontdata.h"
#include "gallegrotexturedata.h"
#include "gallegrocameradata.h"
#include "gallegrofileinputstreamdata.h"

#include "cpgf/goutmain.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>

#include <memory>

namespace gincu {

class GAllegroDeviceContext : public GDeviceContext
{
public:
	GAllegroDeviceContext();
	~GAllegroDeviceContext();

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
	mutable bool needInitializeDisplayEvent;
	ALLEGRO_EVENT_QUEUE * eventQueue;
	std::unique_ptr<GAllegroRenderContext> renderContext;
};

GAllegroDeviceContext::GAllegroDeviceContext()
	:
		needInitializeDisplayEvent(true),
		eventQueue(nullptr),
		renderContext()
{
}

GAllegroDeviceContext::~GAllegroDeviceContext()
{
}

void GAllegroDeviceContext::initialize(const GConfigInfo & configInfo)
{
	al_init();

	al_install_mouse();
	al_install_keyboard();
	al_init_image_addon();
	al_init_font_addon();
//	al_init_ttf_addon();
	al_init_primitives_addon();

	this->eventQueue = al_create_event_queue();
	al_register_event_source(this->eventQueue, al_get_mouse_event_source());
	al_register_event_source(this->eventQueue, al_get_keyboard_event_source());

	this->needInitializeDisplayEvent = true;
	
	this->renderContext.reset(new GAllegroRenderContext());
	this->renderContext->initialize(true);
}

void GAllegroDeviceContext::finalize()
{
	this->renderContext->finalize();

	al_destroy_event_queue(this->eventQueue);
}

GRenderContext * GAllegroDeviceContext::getRenderContext() const
{
	return this->renderContext.get();
}

bool GAllegroDeviceContext::getEvent(GEvent * event) const
{
	if(this->needInitializeDisplayEvent) {
		ALLEGRO_DISPLAY * window = this->renderContext->getWindow();
		if(window != nullptr) {
			this->needInitializeDisplayEvent = false;
			al_register_event_source(this->eventQueue, al_get_display_event_source(window));
		}
	}

	ALLEGRO_EVENT e;
	if(! al_get_next_event(this->eventQueue, &e)) {
		return false;
	}

	switch(e.type) {
	case ALLEGRO_EVENT_DISPLAY_RESIZE:
		*event = GEvent(GEventType::windowResized, GResizeEvent{ (GCoord)e.display.width, (GCoord)e.display.height });
		break;

	case ALLEGRO_EVENT_DISPLAY_CLOSE:
		*event = GEvent(GEventType::windowClosed);
		break;

	case ALLEGRO_EVENT_MOUSE_AXES: {
		GTouchEvent touchEvent = GTouchEvent();
		ALLEGRO_MOUSE_STATE mouseState;
		touchEvent.down = al_mouse_button_down(&mouseState, 1);
		touchEvent.screenPosition = {(GCoord)e.mouse.x, (GCoord)e.mouse.y};
		*event = GEvent(GEventType::touchMoved, touchEvent);
	}
		break;

	case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
	case ALLEGRO_EVENT_MOUSE_BUTTON_UP: {
		GTouchEvent touchEvent = GTouchEvent();
		touchEvent.down = (e.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN);
		touchEvent.screenPosition = {(GCoord)e.mouse.x, (GCoord)e.mouse.y};
		*event = GEvent((touchEvent.down ? GEventType::touchPressed : GEventType::touchReleased), touchEvent);
	}
	   break;

	}

	return true;
}

bool GAllegroDeviceContext::isFinished() const
{
	return false;
}

std::shared_ptr<GTextRenderData> GAllegroDeviceContext::createTextRenderData(const GTextRenderData * copy) const
{
	if(copy == nullptr) {
		return std::make_shared<GAllegroTextRenderData>();
	}
	else {
		return std::make_shared<GAllegroTextRenderData>(*static_cast<const GAllegroTextRenderData *>(copy));
	}
}

std::shared_ptr<GVertexArrayData> GAllegroDeviceContext::createVertexArrayData(const GVertexArrayData * copy) const
{
	if(copy == nullptr) {
		return std::make_shared<GAllegroVertexArrayData>();
	}
	else {
		return std::make_shared<GAllegroVertexArrayData>(*static_cast<const GAllegroVertexArrayData *>(copy));
	}
}

std::shared_ptr<GFontData> GAllegroDeviceContext::createFontData(const GFontData * copy) const
{
	if(copy == nullptr) {
		return std::make_shared<GAllegroFontData>();
	}
	else {
		return std::make_shared<GAllegroFontData>(*static_cast<const GAllegroFontData *>(copy));
	}
}

std::shared_ptr<GTextureData> GAllegroDeviceContext::createTextureData(const GTextureData * copy) const
{
	if(copy == nullptr) {
		return std::make_shared<GAllegroTextureData>();
	}
	else {
		return std::make_shared<GAllegroTextureData>(*static_cast<const GAllegroTextureData *>(copy));
	}
}

std::shared_ptr<GCameraData> GAllegroDeviceContext::createCameraData(const GCameraData * copy) const
{
	if(copy == nullptr) {
		return std::make_shared<GAllegroCameraData>();
	}
	else {
		return std::make_shared<GAllegroCameraData>(*static_cast<const GAllegroCameraData *>(copy));
	}
}

std::shared_ptr<GFileInputStreamData> GAllegroDeviceContext::createFileInputStreamData() const
{
	return std::make_shared<GAllegroFileInputStreamData>();
}


G_AUTO_RUN_BEFORE_MAIN(GAllegroDeviceContext)
{
	GDeviceContextRegister::getInstance()->registerObject(
		"allegro",
		&objectFactoryCreator<GAllegroDeviceContext>
	);
}



} //namespace gincu