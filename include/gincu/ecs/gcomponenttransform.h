#ifndef GCOMPONENTTRANSFORM_H
#define GCOMPONENTTRANSFORM_H

#include "gincu/ecs/gcomponenttransformbase.h"

#include <vector>

namespace gincu {

class GComponentTransform : public GComponentTransformBase<GComponentTransform>
{
private:
	typedef GComponentTransformBase<GComponentTransform> super;

public:
	inline static constexpr GComponentType getComponentType() {
		return GComponentType::transform;
	}

public:
	GComponentTransform();
	explicit GComponentTransform(const GPoint & position, const GScale & scale = {1.0f, 1.0f}, const bool visible = true);
	~GComponentTransform();

	unsigned int getCameraId() const { return this->cameraId; }
	GComponentTransform * setCameraId(const unsigned int cameraId);
	
private:
	virtual void doAfterZOrderChanged();

private:
	unsigned int cameraId; // must between [0, 31]

private:
	friend class GComponentLocalTransform;
};


} //namespace gincu

#endif
