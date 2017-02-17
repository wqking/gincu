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

class GEvent
{
public:
	GEvent() : GEvent(GEventType::none) {}

	explicit GEvent(const GEventType type)
		:
			type(type),
			touch(),
			resize(),
			propagation(false)
	{}

	explicit GEvent(const GEventType type, const GTouchEvent & touch)
		:
			type(type),
			touch(touch),
			resize(),
			propagation(false)
	{}

	explicit GEvent(const GEventType type, const GResizeEvent & resize)
		:
			type(type),
			touch(),
			resize(resize),
			propagation(false)
	{}
	
	GEventType getType() const { return this->type; }
	void setType(const GEventType type) { this->type = type; }
	
	const GTouchEvent & getTouch() const { return this->touch; }
	void setTouch(const GTouchEvent & touch) { this->touch = touch; }
	
	const GResizeEvent & getResize() const { return this->resize; }
	
	bool doesAllowPropagate() const { return this->propagation; }
	void setAllowPropagate(const bool allow) const { this->propagation = allow; }

private:
	GEventType type;

	GTouchEvent touch;
	GResizeEvent resize;

	mutable bool propagation;
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

