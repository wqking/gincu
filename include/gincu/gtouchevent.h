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
	GTouchEventType type;
	bool down;
	GPoint position;
	GPoint deltaPosition;
	GEntity * target;
	GEntity * touchedEntity;
};


} //namespace gincu

#endif
