#ifndef ENTITY_H
#define ENTITY_H

#include "framework/entitypolicy.h"

#include <memory>
#include <vector>

namespace gincu {

class Component;
class ComponentsBuffer;

class Entity : public EntityBase
{
public:
	void * operator new (const std::size_t size);
	void operator delete(void * p);

	Entity();
	~Entity();

	Entity * addComponent(Component * component);
	void removeComponent(Component * component);
	
	void setComponentsBuffer(ComponentsBuffer * componentsBuffer);

	Component * getComponentByTypeId(const unsigned int typeId) const;
	
	template <typename T>
	T * getComponentByType() const {
		return static_cast<T *>(this->getComponentByTypeId(T::getComponentType()));
	}
	
private:
	ComponentsBuffer * componentsBuffer;
};


} //namespace gincu

#endif
