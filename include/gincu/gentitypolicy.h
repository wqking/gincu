#ifndef GENTITYPOLICY_H
#define GENTITYPOLICY_H

#include "gincu/gcomponent.h"
#include "gincu/gcomponentsbuffer.h"

#include <memory>
#include <vector>
#include <map>
#include <array>

namespace gincu {

class Component;
class ComponentsBuffer;

// Define how an Entity stores the components.
// Different policy may result different time and memory usage.
enum class EntityStoragePolicy
{
	// Use std::vector to hold all components, each component is at the index of componentTypeId
	// Time complexity: O(1)
	// Memory complexity: O(N)
	dynamicArray,

	// Use std::map to hold all components
	// Time complexity: O(logN)
	// Memory complexity: O(logN)
	dynamicMap,

	// Use std::array to hold all components, each component is at the index of componentTypeId
	// Time complexity: O(1)
	// Memory complexity: O(N)
	// Canveat: The InitialSize must be large enough to hold all component types, and there may waste a lot of memory for unused component type.
	staticArray,

	// Use std::array to hold hot components, std::vector to hold all cold components
	// Time complexity: O(1)
	// Memory complexity: O(N)
	mixedArray,

	// Use std::array to hold hot components, std::map to hold all cold components
	// Time complexity: O(1) for hot components, O(logN) for cold components
	// Memory complexity: O(logN)
	mixedMap,
};


class EntityDynamicArrayBase
{
private:
	typedef std::unique_ptr<Component> ComponentPointer;

public:
	explicit EntityDynamicArrayBase(const std::size_t initialSize);
	~EntityDynamicArrayBase();

protected:
	void doAddComponent(Component * component, ComponentsBuffer * componentsBuffer);
	void doRemoveComponent(Component * component, ComponentsBuffer * componentsBuffer);
	void doSetComponentsBuffer(ComponentsBuffer * newComponentsBuffer, ComponentsBuffer * oldComponentsBuffer);
	Component * doGetComponentByTypeId(const unsigned int typeId) const;

private:
	std::vector<ComponentPointer> componentList;
};

template <std::size_t InitialSize>
class EntityDynamicArray : public EntityDynamicArrayBase
{
private:
	typedef EntityDynamicArrayBase super;

public:
	EntityDynamicArray() : super(InitialSize) {}
};


class EntityDynamicMap
{
private:
	typedef std::unique_ptr<Component> ComponentPointer;

protected:
	void doAddComponent(Component * component, ComponentsBuffer * componentsBuffer);
	void doRemoveComponent(Component * component, ComponentsBuffer * componentsBuffer);
	void doSetComponentsBuffer(ComponentsBuffer * newComponentsBuffer, ComponentsBuffer * oldComponentsBuffer);
	Component * doGetComponentByTypeId(const unsigned int typeId) const;

private:
	std::map<unsigned int, ComponentPointer> componentMap;
};

template <const std::size_t ArraySize>
class EntityStaticArray
{
private:
	typedef std::unique_ptr<Component> ComponentPointer;

protected:
	void doAddComponent(Component * component, ComponentsBuffer * componentsBuffer) {
		const unsigned int typeId = component->getTypeId();
		if(typeId >= ArraySize) {
			return;
		}

		if(componentsBuffer != nullptr && this->componentList[typeId]) {
			componentsBuffer->remove(this->componentList[typeId].get());
		}

		this->componentList[typeId].reset(component);

		if(componentsBuffer != nullptr) {
			componentsBuffer->add(component);
		}
	}

	void doRemoveComponent(Component * component, ComponentsBuffer * componentsBuffer) {
		const unsigned int typeId = component->getTypeId();
		if(typeId < ArraySize) {
			if(componentsBuffer != nullptr) {
				componentsBuffer->remove(component);
			}

			this->componentList[typeId].reset();
		}
	}

	void doSetComponentsBuffer(ComponentsBuffer * newComponentsBuffer, ComponentsBuffer * oldComponentsBuffer) {
		if(oldComponentsBuffer != nullptr) {
			for(auto & component : this->componentList) {
				if(component) {
					oldComponentsBuffer->remove(component.get());
				}
			}
		}


		if(newComponentsBuffer != nullptr) {
			for(auto & component : this->componentList) {
				if(component) {
					newComponentsBuffer->add(component.get());
				}
			}
		}
	}

	Component * doGetComponentByTypeId(const unsigned int typeId) const {
		if(typeId < ArraySize) {
			return this->componentList[typeId].get();
		}

		return nullptr;
	}

private:
	std::array<ComponentPointer, ArraySize> componentList;
};


template <const std::size_t ArraySize>
class EntityMixedArray
{
private:
	typedef std::unique_ptr<Component> ComponentPointer;

protected:
	void doAddComponent(Component * component, ComponentsBuffer * componentsBuffer) {
		ComponentPointer * componentSlot;
		const unsigned int typeId = component->getTypeId();
		if(typeId < ArraySize) {
			componentSlot = &this->componentList[typeId];
		}
		else {
			const unsigned int coldIndex = typeId - ArraySize;
			if(coldIndex >= this->coldComponentList.size()) {
				this->coldComponentList.resize(coldIndex + 1);
			}
			componentSlot = &this->coldComponentList[coldIndex];
		}

		if(componentsBuffer != nullptr && *componentSlot) {
			componentsBuffer->remove(componentSlot->get());
		}

		componentSlot->reset(component);

		if(componentsBuffer != nullptr) {
			componentsBuffer->add(component);
		}
	}

	void doRemoveComponent(Component * component, ComponentsBuffer * componentsBuffer) {
		const unsigned int typeId = component->getTypeId();
		if(typeId < ArraySize) {
			if(componentsBuffer != nullptr) {
				componentsBuffer->remove(component);
			}

			this->componentList[typeId].reset();
		}
		else {
			const unsigned int coldIndex = typeId - ArraySize;
			if(coldIndex < this->coldComponentList.size()) {
				if(componentsBuffer != nullptr) {
					componentsBuffer->remove(component);
				}

				this->coldComponentList[coldIndex].reset();
			}
		}
	}

	void doSetComponentsBuffer(ComponentsBuffer * newComponentsBuffer, ComponentsBuffer * oldComponentsBuffer) {
		if(oldComponentsBuffer != nullptr) {
			for(auto & component : this->componentList) {
				if(component) {
					oldComponentsBuffer->remove(component.get());
				}
			}
			for(auto & component : this->coldComponentList) {
				if(component) {
					oldComponentsBuffer->remove(component.get());
				}
			}
		}


		if(newComponentsBuffer != nullptr) {
			for(auto & component : this->componentList) {
				if(component) {
					newComponentsBuffer->add(component.get());
				}
			}
			for(auto & component : this->coldComponentList) {
				if(component) {
					newComponentsBuffer->add(component.get());
				}
			}
		}
	}

	Component * doGetComponentByTypeId(const unsigned int typeId) const {
		if(typeId < ArraySize) {
			return this->componentList[typeId].get();
		}
		else {
			const unsigned int coldIndex = typeId - ArraySize;
			if(coldIndex < this->coldComponentList.size()) {
				return this->coldComponentList[coldIndex].get();
			}
		}

		return nullptr;
	}

private:
	std::array<ComponentPointer, ArraySize> componentList;
	std::vector<ComponentPointer> coldComponentList;
};


template <const std::size_t ArraySize>
class EntityMixedMap
{
private:
	typedef std::unique_ptr<Component> ComponentPointer;

protected:
	void doAddComponent(Component * component, ComponentsBuffer * componentsBuffer) {
		ComponentPointer * componentSlot;
		const unsigned int typeId = component->getTypeId();
		if(typeId < ArraySize) {
			componentSlot = &this->componentList[typeId];
		}
		else {
			componentSlot = &this->coldComponentMap[typeId];
		}

		if(componentsBuffer != nullptr && *componentSlot) {
			componentsBuffer->remove(componentSlot->get());
		}

		componentSlot->reset(component);

		if(componentsBuffer != nullptr) {
			componentsBuffer->add(component);
		}
	}

	void doRemoveComponent(Component * component, ComponentsBuffer * componentsBuffer) {
		const unsigned int typeId = component->getTypeId();
		if(typeId < ArraySize) {
			if(componentsBuffer != nullptr) {
				componentsBuffer->remove(component);
			}

			this->componentList[typeId].reset();
		}
		else {
			auto it = this->coldComponentMap.find(typeId);
			if(it != this->coldComponentMap.end()) {
				if(componentsBuffer != nullptr) {
					componentsBuffer->remove(component);
				}
				it->second.reset();
			}
		}
	}

	void doSetComponentsBuffer(ComponentsBuffer * newComponentsBuffer, ComponentsBuffer * oldComponentsBuffer) {
		if(oldComponentsBuffer != nullptr) {
			for(auto & component : this->componentList) {
				if(component) {
					oldComponentsBuffer->remove(component.get());
				}
			}
			for(auto & item : this->coldComponentMap) {
				if(item.second) {
					oldComponentsBuffer->remove(item.second.get());
				}
			}
		}


		if(newComponentsBuffer != nullptr) {
			for(auto & component : this->componentList) {
				if(component) {
					newComponentsBuffer->add(component.get());
				}
			}
			for(auto & item : this->coldComponentMap) {
				if(item.second) {
					newComponentsBuffer->add(item.second.get());
				}
			}
		}
	}

	Component * doGetComponentByTypeId(const unsigned int typeId) const {
		if(typeId < ArraySize) {
			return this->componentList[typeId].get();
		}
		else {
			auto it = this->coldComponentMap.find(typeId);
			if(it != this->coldComponentMap.end()) {
				return it->second.get();
			}
		}

		return nullptr;
	}

private:
	std::array<ComponentPointer, ArraySize> componentList;
	std::map<unsigned int, ComponentPointer> coldComponentMap;
};


template <EntityStoragePolicy Policy, std::size_t InitialSize>
struct EntityStoragePolicySelector
{
};

template <std::size_t InitialSize>
struct EntityStoragePolicySelector <EntityStoragePolicy::dynamicArray, InitialSize>
{
	typedef EntityDynamicArray<InitialSize> Result;
};

template <std::size_t InitialSize>
struct EntityStoragePolicySelector <EntityStoragePolicy::dynamicMap, InitialSize>
{
	typedef EntityDynamicMap Result;
};

template <std::size_t InitialSize>
struct EntityStoragePolicySelector <EntityStoragePolicy::staticArray, InitialSize>
{
	typedef EntityStaticArray<InitialSize> Result;
};

template <std::size_t InitialSize>
struct EntityStoragePolicySelector <EntityStoragePolicy::mixedArray, InitialSize>
{
	typedef EntityMixedArray<InitialSize> Result;
};

template <std::size_t InitialSize>
struct EntityStoragePolicySelector <EntityStoragePolicy::mixedMap, InitialSize>
{
	typedef EntityMixedMap<InitialSize> Result;
};


#ifndef GINCU_ENTITY_STORAGE_POLICY
#define GINCU_ENTITY_STORAGE_POLICY mixedArray
#endif

#ifndef GINCU_ENTITY_STORAGE_POLICY_INITIAL_SIZE
#define GINCU_ENTITY_STORAGE_POLICY_INITIAL_SIZE componentTypeId_PrimaryCount
#endif

typedef EntityStoragePolicySelector<EntityStoragePolicy:: GINCU_ENTITY_STORAGE_POLICY, GINCU_ENTITY_STORAGE_POLICY_INITIAL_SIZE>::Result EntityBase;


} //namespace gincu


#endif
