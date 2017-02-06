#include "gincu/gentity.h"
#include "gincu/gcomponent.h"
#include "gincu/gcomponentsbuffer.h"
#include "gincu/gheappool.h"

namespace gincu {

void * GEntity::operator new (const std::size_t size)
{
	return GHeapPool::getInstance()->allocate(size);
}

void GEntity::operator delete(void * p)
{
	GHeapPool::getInstance()->free(p);
}

GEntity::GEntity()
	: componentsBuffer(nullptr)
{
}

GEntity::~GEntity()
{
	this->setComponentsBuffer(nullptr);
}

GEntity * GEntity::addComponent(GComponent * component)
{
	component->setEntity(this);

	this->doAddComponent(component, this->componentsBuffer);

	return this;
}

void GEntity::removeComponent(GComponent * component)
{
	this->doRemoveComponent(component, this->componentsBuffer);
}

void GEntity::setComponentsBuffer(GComponentsBuffer * componentsBuffer)
{
	if(this->componentsBuffer != componentsBuffer) {
		this->doSetComponentsBuffer(componentsBuffer, this->componentsBuffer);
		this->componentsBuffer = componentsBuffer;
	}
}

GComponent * GEntity::getComponentByTypeId(const unsigned int typeId) const
{
	return this->doGetComponentByTypeId(typeId);
}


} //namespace gincu
