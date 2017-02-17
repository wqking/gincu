#ifndef GCOMPONENT_H
#define GCOMPONENT_H

#include <utility>
#include <string>

namespace gincu {

class GEntity;

enum class GComponentType
{
	render = 0,
	transform = 1,
	localTransform = 2,
	touchHandler = 3,
	anchor = 4,
	animation = 5,
	camera = 6
};

class GComponent
{
public:
	void * operator new (const std::size_t size);
	void operator delete(void * p);

	explicit GComponent(const GComponentType typeId);
	virtual ~GComponent();

	template <typename T>
	explicit GComponent(const T *) : GComponent(T::getComponentType()){
	}

	void setEntity(GEntity * entity);

	GComponentType getTypeId() const { return typeId; }
	GEntity * getEntity() const { return entity; }

protected:
	void setTypeId(const GComponentType typeId) { this->typeId = typeId; }

private:
	virtual void doAfterSetEntity();

private:
	GComponentType typeId;
	GEntity * entity;
};

constexpr unsigned int componentTypePrimaryCount = 7;

// Usually we should not use componentTypeUser directly.
// Use registerComponentId or GComponentIdRegister.
constexpr GComponentType componentTypeUser = (GComponentType)componentTypePrimaryCount;

// Return a unique component id for name.
// Same name returns the same id.
GComponentType registerComponentId(const std::string & name);

// A utility class to register type id automatically.
// This should be singleton.
class GComponentIdRegister
{
public:
	explicit GComponentIdRegister(const std::string & name)
		: componentId(registerComponentId(name))
	{}
	
	GComponentType getComponentId() const { return this->componentId; }
	
private:
	GComponentType componentId;
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
