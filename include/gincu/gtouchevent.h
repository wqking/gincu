#ifndef GTOUCHEVENT_H
#define GTOUCHEVENT_H

#include "gincu/ggeometry.h"

namespace gincu {

enum class TouchEventType
{
	eventMoved,
	eventPressed,
	eventReleased
};

class Entity;

struct TouchEvent
{
	TouchEventType type;
	bool down;
	GamePoint position;
	GamePoint deltaPosition;
	Entity * target;
	Entity * touchedEntity;
};


} //namespace gincu

#endif
