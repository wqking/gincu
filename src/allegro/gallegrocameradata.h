#ifndef GALLEGROCAMERADATA_H
#define GALLEGROCAMERADATA_H

#include "gincu/gcamera.h"
#include "gallegroutil.h"

#include "allegro5/allegro.h"

namespace gincu {

class GAllegroCameraData : public GCameraData
{
public:
	virtual void apply(const GMatrix44 & matrix, const GRect & /*viewport*/, const GRect & viewportPixels) override
	{
		this->matrix = matrix;
		this->viewportPixels = viewportPixels;
	}
	
	virtual GPoint mapScreenToWorld(const GPoint & point, const GRect & viewportPixels) const override
	{
		return point;
	}

	GMatrix44 matrix;
	GRect viewportPixels;
};

} //namespace gincu

#endif
