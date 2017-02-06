#include "gincu/gcomponent.h"
#include "gincu/gheappool.h"

#include <map>

namespace gincu {

namespace {

unsigned int availableComponentId = componentTypeId_User;

std::map<std::string, unsigned int> * getComponentNameIdMap()
{
	static std::map<std::string, unsigned int> componentNameIdMap;
	return &componentNameIdMap;
}

} //unnamed namespace


void * GComponent::operator new (const std::size_t size)
{
	return GHeapPool::getInstance()->allocate(size);
}

void GComponent::operator delete(void * p)
{
	GHeapPool::getInstance()->free(p);
}

GComponent::GComponent(const unsigned int typeId)
	:
		typeId(typeId),
		entity(nullptr)
{
}

GComponent::~GComponent()
{
}

void GComponent::setEntity(GEntity * entity)
{
	this->entity = entity;
	
	this->doAfterSetEntity();
}

void GComponent::doAfterSetEntity()
{
}


unsigned int registerComponentId(const std::string & name)
{
	unsigned int id = 0;

	auto componentNameIdMap = getComponentNameIdMap();
	auto it = componentNameIdMap->find(name);
	if(it != componentNameIdMap->end()) {
		id = it->second;
	}
	else {
		id = availableComponentId;
		++availableComponentId;
		componentNameIdMap->insert(std::make_pair(name, id));
	}
	
	return id;
}


} //namespace gincu
