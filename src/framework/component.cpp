#include "framework/component.h"
#include "framework/memorypool.h"

#include <map>

namespace gincu {

namespace {

int availableComponentId = componentTypeId_User;

std::map<std::string, int> * getComponentNameIdMap()
{
	static std::map<std::string, int> componentNameIdMap;
	return &componentNameIdMap;
}

} //unnamed namespace


void * Component::operator new (const std::size_t size)
{
	return MemoryPool::getInstance()->allocate(size);
}

void Component::operator delete(void * p)
{
	MemoryPool::getInstance()->free(p);
}

Component::Component(const int typeId)
	:
		typeId(typeId),
		entity(nullptr)
{
}

Component::~Component()
{
}

void Component::setEntity(Entity * entity)
{
	this->entity = entity;
	
	this->doAfterSetEntity();
}

void Component::doAfterSetEntity()
{
}


int registerComponentId(const std::string & name)
{
	int id = 0;

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
