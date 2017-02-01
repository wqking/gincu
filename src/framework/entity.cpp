#include "framework/entity.h"
#include "framework/component.h"
#include "framework/componentsbuffer.h"
#include "framework/memorypool.h"

namespace gincu {

void * Entity::operator new (const std::size_t size)
{
	return MemoryPool::getInstance()->allocate(size);
}

void Entity::operator delete(void * p)
{
	MemoryPool::getInstance()->free(p);
}

Entity::Entity()
	:
		componentList(componentTypeId_PrimaryCount),
		componentsBuffer(nullptr)
{
}

Entity::~Entity()
{
	this->setComponentsBuffer(nullptr);
}

Entity * Entity::addComponent(Component * component)
{
	component->setEntity(this);

	const int typeId = component->getTypeId();
	if((int)this->componentList.size() <= typeId) {
		this->componentList.resize(typeId + 1);
	}

	if(this->componentsBuffer != nullptr && this->componentList[typeId]) {
		this->componentsBuffer->remove(this->componentList[typeId].get());
	}
	
	this->componentList[typeId].reset(component);
	
	if(this->componentsBuffer != nullptr) {
		this->componentsBuffer->add(component);
	}

	return this;
}

void Entity::removeComponent(Component * component)
{
	const int typeId = component->getTypeId();
	if(typeId >= 0 && typeId < (int)this->componentList.size()) {
		if(this->componentsBuffer != nullptr) {
			this->componentsBuffer->remove(component);
		}

		this->componentList[typeId].reset();
	}
}

void Entity::setComponentsBuffer(ComponentsBuffer * componentsBuffer)
{
	if(this->componentsBuffer != componentsBuffer) {
		if(this->componentsBuffer != nullptr) {
			for(auto & component : this->componentList) {
				if(component) {
					this->componentsBuffer->remove(component.get());
				}
			}
		}

		this->componentsBuffer = componentsBuffer;

		if(this->componentsBuffer != nullptr) {
			for(auto & component : this->componentList) {
				if(component) {
					this->componentsBuffer->add(component.get());
				}
			}
		}
	}
}

Component * Entity::getComponentByTypeId(const int typeId) const
{
	if(typeId >= 0 && typeId < (int)this->componentList.size()) {
		return this->componentList[typeId].get();
	}

	return nullptr;
}


} //namespace gincu
