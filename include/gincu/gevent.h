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
	GPoint screenPosition;
	GPoint worldPosition;
	GEntity * touchedEntity;
	unsigned int finger : 7;
	unsigned int down : 1;
};

typedef GSize GResizeEvent;

class GEvent
{
public:
	typedef const void * TagType;

public:
	GEvent();
	explicit GEvent(const GEventType type);
	GEvent(const GEventType type, const GTouchEvent & touch);
	explicit GEvent(const GEventType type, const GResizeEvent & resize);
	
	GEventType getType() const { return this->type; }
	void setType(const GEventType type) { this->type = type; }
	
	const GTouchEvent & getTouch() const { return this->touch; }
	void setTouch(const GTouchEvent & touch) { this->touch = touch; }

	TagType getTag() const { return this->tag; }
	void setTag(const TagType tag) { this->tag = tag; }
	
	const GResizeEvent & getResize() const { return this->resize; }
	
	bool doesAllowPropagate() const { return this->propagation; }
	void setAllowPropagate(const bool allow) const { this->propagation = allow; }

private:
	GEventType type;

	union {
		GTouchEvent touch;
		GResizeEvent resize;
	};

	TagType tag;

	mutable bool propagation;
};


bool isTouchEvent(const GEventType type);



} //namespace gincu


#endif

