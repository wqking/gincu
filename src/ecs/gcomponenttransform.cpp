#include "gincu/ecs/gcomponenttransform.h"
#include "gincu/ecs/gcomponentanchor.h"
#include "gincu/ecs/gentity.h"
#include "gincu/ecs/gentityutil.h"

#include <algorithm>

namespace gincu {

GComponentTransform::GComponentTransform()
	:
		GComponentTransform(GPoint())
{
}

GComponentTransform::GComponentTransform(const GPoint & position, const GScale & scale, const bool visible)
	:
		super(position, scale, visible),
		cameraId(0)
{
}

GComponentTransform::~GComponentTransform()
{
}

GComponentTransform * GComponentTransform::setCameraId(const unsigned int cameraId)
{
	if(this->cameraId != cameraId) {
		const unsigned int oldCameraId = this->cameraId;

		this->cameraId = cameraId;

		GComponentManager * componentManager = getComponentManagerFromEntity(this->getEntity());
		if(componentManager != nullptr) {
			componentManager->cameraIdChanged(this, oldCameraId);
		}
	}
	
	return this;
}

void GComponentTransform::doAfterZOrderChanged()
{
	GComponentManager * componentManager = getComponentManagerFromEntity(this->getEntity());
	if(componentManager != nullptr) {
		componentManager->zOrderChanged(this);
	}
}


} //namespace gincu
