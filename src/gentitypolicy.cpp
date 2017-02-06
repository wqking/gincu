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

void GEntityDynamicArrayBase::doAddComponent(GComponent * component, GComponentsBuffer * componentsBuffer)
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

void GEntityDynamicArrayBase::doRemoveComponent(GComponent * component, GComponentsBuffer * componentsBuffer)
{
	const unsigned int typeId = component->getTypeId();
	if(typeId < this->componentList.size()) {
		if(componentsBuffer != nullptr) {
			componentsBuffer->remove(component);
		}

		this->componentList[typeId].reset();
	}
}

void GEntityDynamicArrayBase::doSetComponentsBuffer(GComponentsBuffer * newComponentsBuffer, GComponentsBuffer * oldComponentsBuffer)
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

GComponent * GEntityDynamicArrayBase::doGetComponentByTypeId(const unsigned int typeId) const
{
	if(typeId < this->componentList.size()) {
		return this->componentList[typeId].get();
	}

	return nullptr;
}


void GEntityDynamicMap::doAddComponent(GComponent * component, GComponentsBuffer * componentsBuffer)
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

void GEntityDynamicMap::doRemoveComponent(GComponent * component, GComponentsBuffer * componentsBuffer)
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

void GEntityDynamicMap::doSetComponentsBuffer(GComponentsBuffer * newComponentsBuffer, GComponentsBuffer * oldComponentsBuffer)
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

GComponent * GEntityDynamicMap::doGetComponentByTypeId(const unsigned int typeId) const
{
	auto it = this->componentMap.find(typeId);
	if(it != this->componentMap.end()) {
		return it->second.get();
	}

	return nullptr;
}


} //namespace gincu
