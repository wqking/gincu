#include "gincu/ecs/gcomponentcamera.h"
#include "gincu/ecs/gcomponenttransform.h"
#include "gincu/ecs/gentity.h"
#include "gincu/ecs/gentityutil.h"
#include "gincu/gapplication.h"

namespace gincu {

GComponentCamera::GComponentCamera()
	:
		super(this),
		camera()
{
}

GComponentCamera * GComponentCamera::setWorldSize(const GSize & worldSize)
{
	this->camera.setWorldSize(worldSize);
	this->doInitializeComponentTransform(getComponentByTypeFromComponent<GComponentTransform>(this));
	return this;
}

GComponentCamera * GComponentCamera::setMask(const uint32_t mask)
{
	if(mask != this->getMask()) {
		this->camera.setMask(mask);

		GComponentManager * componentManager = getComponentManagerFromEntity(this->getEntity());
		if(componentManager != nullptr) {
			componentManager->cameraMaskChanged(this);
		}
	}
	
	return this;
}

void GComponentCamera::onEntityEvent(GComponent * component, const GEntityEventType eventType)
{
	switch(eventType) {
	case GEntityEventType::componentAdded:
		if(component->getType() == GComponentType::transform) {
			this->doInitializeComponentTransform(static_cast<GComponentTransform *>(component));
		}
		break;

	case GEntityEventType::componentRemoving:
		if(component == this) {
			this->getEntity()->removeEventCallback(cpgf::makeCallback(this, &GComponentCamera::onEntityEvent));
		}
		break;

	}
}

void GComponentCamera::doInitializeComponentTransform(GComponentTransform * componentTransform)
{
	if(componentTransform != nullptr) {
		componentTransform->getTransform().setProjectionMode(true);
		const GSize & size = this->camera.getWorldSize();
		componentTransform->setOrigin({ size.width, size.height });
	}
}

void GComponentCamera::doAfterSetEntity()
{
	this->getEntity()->addEventCallback(cpgf::makeCallback(this, &GComponentCamera::onEntityEvent));

	this->doInitializeComponentTransform(getComponentByTypeFromComponent<GComponentTransform>(this));
}


} //namespace gincu

