#include "framework/componenttransform.h"
#include "framework/componentanchor.h"
#include "framework/entity.h"

namespace gincu {

ComponentTransform::ComponentTransform()
	:
		ComponentTransform(GamePoint())
{
}

ComponentTransform::ComponentTransform(const GamePoint & position, const GameScale & scale, const bool visible)
	:
		super(this),
		transform(position, scale),
		visible(visible)
{
}

ComponentTransform::~ComponentTransform()
{
}


ComponentLocalTransform::ComponentLocalTransform()
	:
		super(),
		parent(nullptr)
{
	// must set explicitly because the super is another component.
	this->setTypeId(ComponentLocalTransform::getComponentType());
}

ComponentLocalTransform::ComponentLocalTransform(const GamePoint & position, const GameScale & scale, const bool visible)
	:
		super(position, scale, visible),
		parent(nullptr)
{
	// must set explicitly because the super is another component.
	this->setTypeId(ComponentLocalTransform::getComponentType());
}

ComponentLocalTransform::~ComponentLocalTransform()
{
	this->setParent(nullptr);

	// can't iterate through on this->children because child->setParent will invalid any iterator.
	std::vector<ComponentLocalTransform *> tempChildrenList;
	tempChildrenList.swap(this->children);
	for(ComponentLocalTransform * child : tempChildrenList) {
		child->setParent(nullptr);
	}
}

ComponentLocalTransform * ComponentLocalTransform::setParent(ComponentLocalTransform * parent)
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

ComponentLocalTransform * ComponentLocalTransform::getParent() const
{
	return this->parent;
}

void ComponentLocalTransform::addChild(ComponentLocalTransform * child)
{
	this->children.push_back(child);
}

void ComponentLocalTransform::removeChild(ComponentLocalTransform * child)
{
	auto it = std::find(this->children.begin(), this->children.end(), child);
	if(it != this->children.end()) {
		this->children.erase(it);
	}
}

void ComponentLocalTransform::applyGlobal()
{
	ComponentTransform * globalTransform = this->getEntity()->getComponentByType<ComponentTransform>();
	if(globalTransform != nullptr) {
		if(this->parent != nullptr) {
			ComponentTransform * parentGlobalTransform = this->parent->getEntity()->getComponentByType<ComponentTransform>();
			if(parentGlobalTransform != nullptr) {
				GameTransform parentTransform = parentGlobalTransform->getTransform();
				parentTransform.translate(this->parent->getTransform().getOrigin());
				globalTransform->setTransform(parentTransform.multiply(this->getTransform()));
			}
		}
		else {
			globalTransform->setTransform(this->getTransform());
		}
	}

	for(ComponentLocalTransform * child : this->children) {
		child->applyGlobal();
	}
}


} //namespace gincu
