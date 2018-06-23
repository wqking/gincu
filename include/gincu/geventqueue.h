#ifndef GEVENTQUEUE_H
#define GEVENTQUEUE_H

#include "gincu/gevent.h"

#include "cpgf/gcallback.h"

#include "eventpp/eventqueue.h"

namespace gincu {

struct GEventQueuePolicies
{
	static GEventType getEvent(const GEvent & e) {
		return e.getType();
	}

	using Callback = cpgf::GCallback<void (const GEvent &)>;
};

class GEventQueue : public eventpp::EventQueue<GEventType, void (const GEvent &), GEventQueuePolicies>
{
private:
	using super = eventpp::EventQueue<GEventType, void (const GEvent &), GEventQueuePolicies>;

public:
	using EventListener = Callback;

public:
	static void dispatchAll();

public:
	GEventQueue();
	~GEventQueue();

	template <typename Iterator>
	void addListeners(Iterator begin, const Iterator end, const EventListener & listener) {
		while(begin != end) {
			this->appendListener(*begin, listener);
			++begin;
		}
	}

	using super::removeListener;

	void removeListener(const GEventType type, const EventListener & listener) {
		forEach(type, [this, type, &listener](const Handle & handle, const EventListener & foundListener) {
			if(foundListener == listener) {
				super::removeListener(type, handle);
			}
		});
	}

	template <typename Iterator>
	void removeListeners(Iterator begin, const Iterator end, const EventListener & listener) {
		while(begin != end) {
			this->removeListener(*begin, listener);
			++begin;
		}
	}
};


} //namespace gincu


#endif
