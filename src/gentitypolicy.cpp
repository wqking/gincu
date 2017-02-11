#include "gincu/gentitypolicy.h"
#include "gincu/gcomponent.h"

namespace gincu {

GEntityDynamicArrayBase::GEntityDynamicArrayBase(const std::size_t initialSize)
	: componentList(initialSize)
{
}

GEntityDynamicArrayBase::~GEntityDynamicArrayBase()
{
}

void GEntityDynamicArrayBase::doAddComponent(GComponent * component, GComponentManager * componentManager)
{
	const unsigned int typeId = component->getTypeId();
	if(this->componentList.size() <= typeId) {
		this->componentList.resize(typeId + 1);
	}

	if(componentManager != nullptr && this->componentList[typeId]) {
		componentManager->remove(this->componentList[typeId].get());
	}

	this->componentList[typeId].reset(component);

	if(componentManager != nullptr) {
		componentManager->add(component);
	}
}

void GEntityDynamicArrayBase::doRemoveComponent(GComponent * component, GComponentManager * componentManager)
{
	const unsigned int typeId = component->getTypeId();
	if(typeId < this->componentList.size()) {
		if(componentManager != nullptr) {
			componentManager->remove(component);
		}

		this->componentList[typeId].reset();
	}
}

void GEntityDynamicArrayBase::doSetComponentManager(GComponentManager * newComponentManager, GComponentManager * oldComponentManager)
{
	if(oldComponentManager != nullptr) {
		for(auto & component : this->componentList) {
			if(component) {
				oldComponentManager->remove(component.get());
			}
		}
	}


	if(newComponentManager != nullptr) {
		for(auto & component : this->componentList) {
			if(component) {
				newComponentManager->add(component.get());
			}
		}
	}
}

GComponent * GEntityDynamicArrayBase::doGetComponentByTypeId(const unsigned int typeId) const
{
	if(typeId < this->componentList.size()) {
		return this->componentList[typeId].get();
	}

	return nullptr;
}


void GEntityDynamicMap::doAddComponent(GComponent * component, GComponentManager * componentManager)
{
	const unsigned int typeId = component->getTypeId();

	auto it = this->componentMap.find(typeId);
	if(it != this->componentMap.end()) {
		if(componentManager != nullptr) {
			componentManager->remove(it->second.get());
		}
		it->second.reset(component);
	}
	else {
		this->componentMap.insert(std::make_pair(typeId, ComponentPointer(component)));
	}

	if(componentManager != nullptr) {
		componentManager->add(component);
	}

}

void GEntityDynamicMap::doRemoveComponent(GComponent * component, GComponentManager * componentManager)
{
	const unsigned int typeId = component->getTypeId();
	auto it = this->componentMap.find(typeId);
	if(it != this->componentMap.end()) {
		if(componentManager != nullptr) {
			componentManager->remove(component);
		}
		it->second.reset();
	}
}

void GEntityDynamicMap::doSetComponentManager(GComponentManager * newComponentManager, GComponentManager * oldComponentManager)
{
	if(oldComponentManager != nullptr) {
		for(auto & item : this->componentMap) {
			if(item.second) {
				oldComponentManager->remove(item.second.get());
			}
		}
	}

	if(newComponentManager != nullptr) {
		for(auto & item : this->componentMap) {
			if(item.second) {
				newComponentManager->add(item.second.get());
			}
		}
	}
}

GComponent * GEntityDynamicMap::doGetComponentByTypeId(const unsigned int typeId) const
{
	auto it = this->componentMap.find(typeId);
	if(it != this->componentMap.end()) {
		return it->second.get();
	}

	return nullptr;
}


} //namespace gincu
