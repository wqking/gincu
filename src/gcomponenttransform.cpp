#include "gincu/gcomponenttransform.h"
#include "gincu/gcomponentanchor.h"
#include "gincu/gentity.h"
#include "gincu/gentityutil.h"

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
		visible(visible)
{
}

GComponentTransform::~GComponentTransform()
{
}


GComponentLocalTransform::GComponentLocalTransform()
	:
		super(),
		parent(nullptr)
{
	// must set explicitly because the super is another component.
	this->setTypeId(GComponentLocalTransform::getComponentType());
}

GComponentLocalTransform::GComponentLocalTransform(const GPoint & position, const GScale & scale, const bool visible)
	:
		super(position, scale, visible),
		parent(nullptr)
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
	}
	
	return this;
}

GComponentLocalTransform * GComponentLocalTransform::getParent() const
{
	return this->parent;
}

void GComponentLocalTransform::addChild(GComponentLocalTransform * child)
{
	this->children.push_back(child);
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
				GTransform parentTransform = parentGlobalTransform->getTransform();
				parentTransform.translate(this->parent->getTransform().getOrigin());
				globalTransform->setTransform(parentTransform.multiply(this->getTransform()));
			}
		}
		else {
			globalTransform->setTransform(this->getTransform());
		}
	}

	for(GComponentLocalTransform * child : this->children) {
		child->applyGlobal();
	}
}


} //namespace gincu
