#ifndef COMPONENT_H
#define COMPONENT_H

#include <utility>
#include <string>

namespace gincu {

class Entity;

class Component
{
public:
	void * operator new (const std::size_t size);
	void operator delete(void * p);

	explicit Component(const int typeId);
	virtual ~Component();

	template <typename T>
	explicit Component(const T *) : Component(T::getComponentType()){
	}

	void setEntity(Entity * entity);

	int getTypeId() const { return typeId; }
	Entity * getEntity() const { return entity; }

protected:
	void setTypeId(const int typeId) { this->typeId = typeId; }

private:
	virtual void doAfterSetEntity();

private:
	int typeId;
	Entity * entity;
};

constexpr int componentTypeId_Render = 0;
constexpr int componentTypeId_Transform = 1;
constexpr int componentTypeId_LocalTransform = 2;
constexpr int componentTypeId_TouchHandler = 3;
constexpr int componentTypeId_Anchor = 4;
constexpr int componentTypeId_PrimaryCount = 5;

// Usually we should not use componentTypeId_User directly.
// Use registerComponentId or ComponentIdRegister.
constexpr int componentTypeId_User = componentTypeId_PrimaryCount;

// Return a unique component id for name.
// Same name returns the same id.
int registerComponentId(const std::string & name);

// A utility class to register type id automatically.
// This should be singleton.
class ComponentIdRegister
{
public:
	explicit ComponentIdRegister(const std::string & name)
		: componentId(registerComponentId(name))
	{}
	
	int getComponentId() const { return this->componentId; }
	
private:
	int componentId;
};

// In current implementation, component can be created by "new" directly.
// But using the function createComponent can allow future extension, such as do some initializations.
template <typename ComponentType, typename... Params>
ComponentType * createComponent(Params... params)
{
	ComponentType * component = new ComponentType(std::forward<Params>(params)...);
	return component;
}


} //namespace gincu

#endif
