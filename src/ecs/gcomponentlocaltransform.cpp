#include "gincu/ecs/gcomponentlocaltransform.h"
#include "gincu/ecs/gcomponentanchor.h"
#include "gincu/ecs/gentity.h"
#include "gincu/ecs/gentityutil.h"

#include <algorithm>

namespace gincu {

GComponentLocalTransform::GComponentLocalTransform()
	:
		GComponentLocalTransform(GPoint())
{
}

GComponentLocalTransform::GComponentLocalTransform(const GPoint & position, const GScale & scale, const bool visible)
	:
		super(position, scale, visible),
		parent(nullptr),
		needSortChildren(false)
{
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

				globalTransform->setTransform(
					GTransform(translateMatrix(parentGlobalTransform->getTransform().getMatrix(), this->parent->getTransform().getOrigin()) * this->getTransform().getMatrix())
				);
			}
		}
		else {
			globalTransform->setVisible(this->isVisible());
			globalTransform->setZOrder(this->getZOrder());
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
