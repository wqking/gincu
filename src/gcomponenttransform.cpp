#include "gincu/gcomponenttransform.h"
#include "gincu/gcomponentanchor.h"
#include "gincu/gentity.h"
#include "gincu/gentityutil.h"

#include <algorithm>

namespace gincu {

GComponentTransform::GComponentTransform()
	:
		GComponentTransform(GPoint())
{
}

GComponentTransform::GComponentTransform(const GPoint & position, const GScale & scale, const bool visible)
	:
		super(this),
		transform(position, scale),
		zOrder(0),
		visible(visible),
		cameraId(0)
{
}

GComponentTransform::~GComponentTransform()
{
}

GComponentTransform * GComponentTransform::setCameraId(const unsigned int cameraId)
{
	if(this->cameraId != cameraId) {
		this->cameraId = cameraId;

		GComponentManager * componentManager = getComponentManagerFromEntity(this->getEntity());
		if(componentManager != nullptr) {
			componentManager->cameraIdChanged(this);
		}
	}
	
	return this;
}

GComponentTransform * GComponentTransform::setZOrder(const int zOrder)
{
	if(this->zOrder != zOrder) {
		this->zOrder = zOrder;
		
		this->doAfterZOrderChanged();

		GComponentManager * componentManager = getComponentManagerFromEntity(this->getEntity());
		if(componentManager != nullptr) {
			componentManager->zOrderChanged(this);
		}
	}

	return this;
}

void GComponentTransform::doAfterZOrderChanged()
{
}


GComponentLocalTransform::GComponentLocalTransform()
	:
		super(),
		parent(nullptr),
		needSortChildren(false)
{
	// must set explicitly because the super is another component.
	this->setTypeId(GComponentLocalTransform::getComponentType());
}

GComponentLocalTransform::GComponentLocalTransform(const GPoint & position, const GScale & scale, const bool visible)
	:
		super(position, scale, visible),
		parent(nullptr),
		needSortChildren(false)
{
	// must set explicitly because the super is another component.
	this->setTypeId(GComponentLocalTransform::getComponentType());
}

GComponentLocalTransform::~GComponentLocalTransform()
{
	this->setParent(nullptr);

	// can't iterate through on this->children because child->setParent will invalid any iterator.
	std::vector<GComponentLocalTransform *> tempChildrenList;
	tempChildrenList.swap(this->children);
	for(GComponentLocalTransform * child : tempChildrenList) {
		child->setParent(nullptr);
	}
}

GComponentLocalTransform * GComponentLocalTransform::setParent(GComponentLocalTransform * parent)
{
	if(this->parent != parent) {
		if(this->parent != nullptr) {
			this->parent->removeChild(this);
		}
	
		this->parent = parent;
		
		if(this->parent != nullptr) {
			this->parent->addChild(this);
		}

		GComponentManager * componentManager = getComponentManagerFromEntity(this->getEntity());
		if(componentManager != nullptr) {
			componentManager->parentChanged(this);
		}
	}
	
	return this;
}

void GComponentLocalTransform::addChild(GComponentLocalTransform * child)
{
	this->children.push_back(child);
	this->needSortChildren = true;
}

void GComponentLocalTransform::removeChild(GComponentLocalTransform * child)
{
	auto it = std::find(this->children.begin(), this->children.end(), child);
	if(it != this->children.end()) {
		this->children.erase(it);
	}
}

void GComponentLocalTransform::applyGlobal()
{
	GComponentTransform * globalTransform = this->getEntity()->getComponentByType<GComponentTransform>();
	if(globalTransform != nullptr) {
		if(this->parent != nullptr) {
			GComponentTransform * parentGlobalTransform = this->parent->getEntity()->getComponentByType<GComponentTransform>();
			if(parentGlobalTransform != nullptr) {
				globalTransform->setVisible(parentGlobalTransform->isVisible() && this->isVisible());
				// don't call setCameraId to avoid trigger events.
				globalTransform->cameraId = parentGlobalTransform->getCameraId();

				GTransform parentTransform = parentGlobalTransform->getTransform();
				parentTransform.translate(this->parent->getTransform().getOrigin());
				globalTransform->setTransform(parentTransform.multiply(this->getTransform()));
			}
		}
		else {
			globalTransform->setVisible(this->isVisible());

			globalTransform->setTransform(this->getTransform());
		}
	}

	for(GComponentLocalTransform * child : this->children) {
		child->applyGlobal();
	}
}

const std::vector<GComponentLocalTransform *> & GComponentLocalTransform::getSortedChildren() const
{
	if(this->needSortChildren) {
		this->needSortChildren = false;
		std::stable_sort(this->children.begin(), this->children.end(), [](const GComponentLocalTransform * a, const GComponentLocalTransform * b) {
			return a->getZOrder() < b->getZOrder();
		});
	}

	return this->children;
}

void GComponentLocalTransform::doAfterZOrderChanged()
{
	if(this->parent != nullptr) {
		this->parent->needSortChildren = true;
	}
}


} //namespace gincu
