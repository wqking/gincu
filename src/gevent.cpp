#include "gincu/gevent.h"

namespace gincu {

GEvent::GEvent()
	: GEvent(GEventType::none)
{
}

GEvent::GEvent(const GEventType type)
	:
		type(type),
		touch(),
		//resize(),
		tag(),
		propagation(false)
{
}

GEvent::GEvent(const GEventType type, const GTouchEvent & touch)
	:
		type(type),
		touch(touch),
		tag(),
		propagation(false)
{
}

GEvent::GEvent(const GEventType type, const GResizeEvent & resize)
	:
		type(type),
		resize(resize),
		tag(),
		propagation(false)
{
}

GEvent::GEvent(const GEventType type, GRenderContext * renderContext)
	:
		type(type),
		renderContext(renderContext),
		tag(),
		propagation(false)
{
}

bool isTouchEvent(const GEventType type)
{
	switch(type) {
	case GEventType::touchMoved:
	case GEventType::touchPressed:
	case GEventType::touchReleased:
		return true;

	default:
		return false;
	}
}


} //namespace gincu

