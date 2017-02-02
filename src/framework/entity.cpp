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
	: componentsBuffer(nullptr)
{
}

Entity::~Entity()
{
	this->setComponentsBuffer(nullptr);
}

Entity * Entity::addComponent(Component * component)
{
	component->setEntity(this);

	this->doAddComponent(component, this->componentsBuffer);

	return this;
}

void Entity::removeComponent(Component * component)
{
	this->doRemoveComponent(component, this->componentsBuffer);
}

void Entity::setComponentsBuffer(ComponentsBuffer * componentsBuffer)
{
	if(this->componentsBuffer != componentsBuffer) {
		this->doSetComponentsBuffer(componentsBuffer, this->componentsBuffer);
		this->componentsBuffer = componentsBuffer;
	}
}

Component * Entity::getComponentByTypeId(const unsigned int typeId) const
{
	return this->doGetComponentByTypeId(typeId);
}


} //namespace gincu
