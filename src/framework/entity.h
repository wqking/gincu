#ifndef ENTITY_H
#define ENTITY_H

#include <memory>
#include <vector>

namespace gincu {

class Component;
class ComponentsBuffer;

class Entity
{
private:
	typedef std::unique_ptr<Component> ComponentPointer;

public:
	void * operator new (const std::size_t size);
	void operator delete(void * p);

	Entity();
	~Entity();

	Entity * addComponent(Component * component);
	void removeComponent(Component * component);
	
	void setComponentsBuffer(ComponentsBuffer * componentsBuffer);

	Component * getComponentByTypeId(const int typeId) const;
	
	template <typename T>
	T * getComponentByType() const {
		return static_cast<T *>(this->getComponentByTypeId(T::getComponentType()));
	}
	
private:
	std::vector<ComponentPointer> componentList;
	ComponentsBuffer * componentsBuffer;
};


} //namespace gincu

#endif
