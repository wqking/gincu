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
	this->setComponentManager(nullptr);
}

GEntity * GEntity::addComponent(GComponent * component)
{
	component->setEntity(this);

	this->doAddComponent(component, this->componentManager);

	this->eventCallbackList(component, GEntityEventType::componentAdded);

	return this;
}

void GEntity::removeComponent(GComponent * component)
{
	this->eventCallbackList(component, GEntityEventType::componentRemoving);

	this->doRemoveComponent(component, this->componentManager);
}

void GEntity::addEventCallback(const EventCallback & callback)
{
	this->eventCallbackList.add(callback);
}

void GEntity::removeEventCallback(const EventCallback & callback)
{
	this->eventCallbackList.remove(callback);
}

void GEntity::setComponentManager(GComponentManager * componentManager)
{
	if(this->componentManager != componentManager) {
		this->doSetComponentManager(componentManager, this->componentManager);
		this->componentManager = componentManager;
	}
}

GComponent * GEntity::getComponentByTypeId(const GComponentType typeId) const
{
	return this->doGetComponentByTypeId((unsigned int)typeId);
}


} //namespace gincu
