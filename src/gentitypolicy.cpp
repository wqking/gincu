#include "gincu/gentitypolicy.h"
#include "gincu/gcomponent.h"

namespace gincu {

EntityDynamicArrayBase::EntityDynamicArrayBase(const std::size_t initialSize)
	: componentList(initialSize)
{
}

EntityDynamicArrayBase::~EntityDynamicArrayBase()
{
}

void EntityDynamicArrayBase::doAddComponent(Component * component, ComponentsBuffer * componentsBuffer)
{
	const unsigned int typeId = component->getTypeId();
	if(this->componentList.size() <= typeId) {
		this->componentList.resize(typeId + 1);
	}

	if(componentsBuffer != nullptr && this->componentList[typeId]) {
		componentsBuffer->remove(this->componentList[typeId].get());
	}

	this->componentList[typeId].reset(component);

	if(componentsBuffer != nullptr) {
		componentsBuffer->add(component);
	}
}

void EntityDynamicArrayBase::doRemoveComponent(Component * component, ComponentsBuffer * componentsBuffer)
{
	const unsigned int typeId = component->getTypeId();
	if(typeId < this->componentList.size()) {
		if(componentsBuffer != nullptr) {
			componentsBuffer->remove(component);
		}

		this->componentList[typeId].reset();
	}
}

void EntityDynamicArrayBase::doSetComponentsBuffer(ComponentsBuffer * newComponentsBuffer, ComponentsBuffer * oldComponentsBuffer)
{
	if(oldComponentsBuffer != nullptr) {
		for(auto & component : this->componentList) {
			if(component) {
				oldComponentsBuffer->remove(component.get());
			}
		}
	}


	if(newComponentsBuffer != nullptr) {
		for(auto & component : this->componentList) {
			if(component) {
				newComponentsBuffer->add(component.get());
			}
		}
	}
}

Component * EntityDynamicArrayBase::doGetComponentByTypeId(const unsigned int typeId) const
{
	if(typeId < this->componentList.size()) {
		return this->componentList[typeId].get();
	}

	return nullptr;
}


void EntityDynamicMap::doAddComponent(Component * component, ComponentsBuffer * componentsBuffer)
{
	const unsigned int typeId = component->getTypeId();

	auto it = this->componentMap.find(typeId);
	if(it != this->componentMap.end()) {
		if(componentsBuffer != nullptr) {
			componentsBuffer->remove(it->second.get());
		}
		it->second.reset(component);
	}
	else {
		this->componentMap.insert(std::make_pair(typeId, ComponentPointer(component)));
	}

	if(componentsBuffer != nullptr) {
		componentsBuffer->add(component);
	}

}

void EntityDynamicMap::doRemoveComponent(Component * component, ComponentsBuffer * componentsBuffer)
{
	const unsigned int typeId = component->getTypeId();
	auto it = this->componentMap.find(typeId);
	if(it != this->componentMap.end()) {
		if(componentsBuffer != nullptr) {
			componentsBuffer->remove(component);
		}
		it->second.reset();
	}
}

void EntityDynamicMap::doSetComponentsBuffer(ComponentsBuffer * newComponentsBuffer, ComponentsBuffer * oldComponentsBuffer)
{
	if(oldComponentsBuffer != nullptr) {
		for(auto & item : this->componentMap) {
			if(item.second) {
				oldComponentsBuffer->remove(item.second.get());
			}
		}
	}

	if(newComponentsBuffer != nullptr) {
		for(auto & item : this->componentMap) {
			if(item.second) {
				newComponentsBuffer->add(item.second.get());
			}
		}
	}
}

Component * EntityDynamicMap::doGetComponentByTypeId(const unsigned int typeId) const
{
	auto it = this->componentMap.find(typeId);
	if(it != this->componentMap.end()) {
		return it->second.get();
	}

	return nullptr;
}


} //namespace gincu
