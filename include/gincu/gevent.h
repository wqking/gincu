#ifndef GEVENT_H
#define GEVENT_H

#include "gincu/ggeometry.h"

#include "cpgf/gcallback.h"

#include <memory>

namespace gincu {

enum class GEventType
{
	none,

	render,
	update,

	execute, // execute in main thread

	touchMoved,
	touchPressed,
	touchReleased,

	windowClosed,
	windowResized,
	windowActivated,
	windowDeactivated,
};

class GRenderContext;
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
	GEvent(const GEventType type, const GResizeEvent & resize);
	GEvent(const GEventType type, GRenderContext * renderContext);
	GEvent(const GEventType type, const std::shared_ptr<void> & sharedData);
	GEvent(const GEventType type, const cpgf::GCallback<void ()> & callback); // execute

	GEventType getType() const { return this->type; }
	void setType(const GEventType type) { this->type = type; }
	
	const GTouchEvent & getTouch() const { return this->touch; }
	void setTouch(const GTouchEvent & touch) { this->touch = touch; }

	const std::shared_ptr<void> & getSharedData() const { return this->sharedData; }
	void setSharedData(const std::shared_ptr<void> & sharedData) { this->sharedData = sharedData; }

	const cpgf::GCallback<void ()> & getCallback() const { return *(static_cast<cpgf::GCallback<void ()> *>(this->sharedData.get())); }

	TagType getTag() const { return this->tag; }
	void setTag(const TagType tag) { this->tag = tag; }
	
	const GResizeEvent & getResize() const { return this->resize; }

	GRenderContext * getRenderContext() const { return this->renderContext; }
	
	bool doesAllowPropagate() const { return this->propagation; }
	void setAllowPropagate(const bool allow) const { this->propagation = allow; }

private:
	GEventType type;

	union {
		GTouchEvent touch;
		GResizeEvent resize;
		GRenderContext * renderContext;
	};

	std::shared_ptr<void> sharedData;

	TagType tag;

	mutable bool propagation;
};


bool isTouchEvent(const GEventType type);



} //namespace gincu


#endif

