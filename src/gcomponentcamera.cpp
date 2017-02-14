#include "gincu/gcomponentcamera.h"
#include "gincu/gcomponenttransform.h"
#include "gincu/gentity.h"
#include "gincu/gentityutil.h"
#include "gincu/gapplication.h"

namespace gincu {

GComponentCamera::GComponentCamera()
	:
		super(this),
		size(GApplication::getInstance()->getWindowSize())
{
}

void GComponentCamera::setSize(const GSize & size)
{
	this->size = size;
	this->doInitializeComponentTransform(getComponentByTypeFromComponent<GComponentTransform>(this));
}

void GComponentCamera::onEntityEvent(GComponent * component, const GEntityEventType eventType)
{
	switch(eventType) {
	case GEntityEventType::componentAdded:
		if(component->getTypeId() == componentTypeId_Transform) {
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
		componentTransform->getTransform().setOrigin({ this->size.width, this->size.height });
	}
}

void GComponentCamera::doAfterSetEntity()
{
	this->getEntity()->addEventCallback(cpgf::makeCallback(this, &GComponentCamera::onEntityEvent));
	this->doInitializeComponentTransform(getComponentByTypeFromComponent<GComponentTransform>(this));
}


} //namespace gincu

