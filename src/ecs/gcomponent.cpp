#include "gincu/ecs/gcomponent.h"

#include "cpgf/gmemorypool.h"

#include <map>

namespace gincu {

namespace {

unsigned int availableComponentId = (unsigned int)componentTypeUser;

std::map<std::string, unsigned int> * getComponentNameIdMap()
{
	static std::map<std::string, unsigned int> componentNameIdMap;
	return &componentNameIdMap;
}

} //unnamed namespace


void * GComponent::operator new (const std::size_t size)
{
	return cpgf::GMemoryPool::getInstance()->allocate(size);
}

void * GComponent::operator new (const std::size_t /*size*/, void * ptr)
{
	return ptr;
}

void GComponent::operator delete(void * p, size_t size)
{
	cpgf::GMemoryPool::getInstance()->free(p, size);
}

GComponent::GComponent(const GComponentType type)
	:
		type(type),
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


GComponentType registerComponentId(const std::string & name)
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
	
	return (GComponentType)id;
}


} //namespace gincu
