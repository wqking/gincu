#ifndef GCOMPONENT_H
#define GCOMPONENT_H

#include <utility>
#include <string>

namespace gincu {

class GEntity;

class GComponent
{
public:
	void * operator new (const std::size_t size);
	void operator delete(void * p);

	explicit GComponent(const unsigned int typeId);
	virtual ~GComponent();

	template <typename T>
	explicit GComponent(const T *) : GComponent(T::getComponentType()){
	}

	void setEntity(GEntity * entity);

	unsigned int getTypeId() const { return typeId; }
	GEntity * getEntity() const { return entity; }

protected:
	void setTypeId(const unsigned int typeId) { this->typeId = typeId; }

private:
	virtual void doAfterSetEntity();

private:
	int typeId;
	GEntity * entity;
};

constexpr unsigned int componentTypeId_Render = 0;
constexpr unsigned int componentTypeId_Transform = 1;
constexpr unsigned int componentTypeId_LocalTransform = 2;
constexpr unsigned int componentTypeId_TouchHandler = 3;
constexpr unsigned int componentTypeId_Anchor = 4;
constexpr unsigned int componentTypeId_Animation = 5;
constexpr unsigned int componentTypeId_PrimaryCount = 6;

// Usually we should not use componentTypeId_User directly.
// Use registerComponentId or GComponentIdRegister.
constexpr int componentTypeId_User = componentTypeId_PrimaryCount;

// Return a unique component id for name.
// Same name returns the same id.
unsigned int registerComponentId(const std::string & name);

// A utility class to register type id automatically.
// This should be singleton.
class GComponentIdRegister
{
public:
	explicit GComponentIdRegister(const std::string & name)
		: componentId(registerComponentId(name))
	{}
	
	unsigned int getComponentId() const { return this->componentId; }
	
private:
	unsigned int componentId;
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
