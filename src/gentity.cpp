#include "gincu/gentity.h"
#include "gincu/gcomponent.h"
#include "gincu/gcomponentmanager.h"
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
	: componentManager(nullptr)
{
}

GEntity::~GEntity()
{
	this->setComponentsBuffer(nullptr);
}

GEntity * GEntity::addComponent(GComponent * component)
{
	component->setEntity(this);

	this->doAddComponent(component, this->componentManager);

	return this;
}

void GEntity::removeComponent(GComponent * component)
{
	this->doRemoveComponent(component, this->componentManager);
}

void GEntity::setComponentsBuffer(GComponentManager * componentManager)
{
	if(this->componentManager != componentManager) {
		this->doSetComponentsBuffer(componentManager, this->componentManager);
		this->componentManager = componentManager;
	}
}

GComponent * GEntity::getComponentByTypeId(const unsigned int typeId) const
{
	return this->doGetComponentByTypeId(typeId);
}


} //namespace gincu
