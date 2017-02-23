#ifndef GSDLCAMERADATA_H
#define GSDLCAMERADATA_H

#include "gincu/gcamera.h"
#include "gsdlutil.h"

namespace gincu {

class GSdlCameraData : public GCameraData
{
public:
	virtual void apply(const GMatrix44 & matrix, const GRect & viewport) override
	{
	}
	
	virtual GPoint mapScreenToWorld(const GPoint & point, const GRect & viewportPixels) const override
	{
		return GPoint();
	}
};

} //namespace gincu

#endif
