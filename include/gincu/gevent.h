#ifndef GEVENT_H
#define GEVENT_H

#include "gincu/ggeometry.h"

namespace gincu {

enum class GEventType
{
	none,
	touchMoved,
	touchPressed,
	touchReleased,
	windowClosed,
	windowResized,
	windowActivated,
	windowDeactivated,
};

class GEntity;

struct GTouchEvent
{
	int finger;
	bool down;
	GPoint screenPosition;
	GPoint worldPosition;
	GEntity * target;
	GEntity * touchedEntity;
};

typedef GSize GResizeEvent;

struct GEvent
{
	GEvent()
		:
			type(),
			touch(),
			resize(),
			propagation(false)
	{}

	GEventType type;

	GTouchEvent touch;
	GResizeEvent resize;

	mutable bool propagation;

	void allowPropagation() const {
		this->propagation = true;
	}
};

inline bool isTouchEvent(const GEventType type)
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


#endif

