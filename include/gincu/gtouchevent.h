#ifndef GTOUCHEVENT_H
#define GTOUCHEVENT_H

#include "gincu/ggeometry.h"

namespace gincu {

enum class GTouchEventType
{
	eventMoved,
	eventPressed,
	eventReleased
};

class GEntity;

struct GTouchEvent
{
	GTouchEvent()
		:
			type(GTouchEventType::eventMoved),
			down(false),
			position(),
			deltaPosition(),
			target(nullptr),
			touchedEntity(nullptr),
			propagation(false)
	{}

	GTouchEventType type;
	bool down;
	GPoint position;
	GPoint deltaPosition;
	GEntity * target;
	GEntity * touchedEntity;
	mutable bool propagation;

	void allowPropagation() const {
		this->propagation = true;
	}
};


} //namespace gincu

#endif
