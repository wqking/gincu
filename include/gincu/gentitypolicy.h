#ifndef GENTITYPOLICY_H
#define GENTITYPOLICY_H

#include "gincu/gcomponent.h"
#include "gincu/gcomponentmanager.h"

#include <memory>
#include <vector>
#include <map>
#include <array>

namespace gincu {

class GComponent;
class GComponentManager;

// Define how an GEntity stores the components.
// Different policy may result different time and memory usage.
enum class GEntityStoragePolicy
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


class GEntityDynamicArrayBase
{
private:
	typedef std::unique_ptr<GComponent> ComponentPointer;

public:
	explicit GEntityDynamicArrayBase(const std::size_t initialSize);
	~GEntityDynamicArrayBase();

protected:
	void doAddComponent(GComponent * component, GComponentManager * componentManager);
	void doRemoveComponent(GComponent * component, GComponentManager * componentManager);
	void doSetComponentManager(GComponentManager * newComponentManager, GComponentManager * oldComponentManager);
	GComponent * doGetComponentByTypeId(const unsigned int typeId) const;

private:
	std::vector<ComponentPointer> componentList;
};

template <std::size_t InitialSize>
class GEntityDynamicArray : public GEntityDynamicArrayBase
{
private:
	typedef GEntityDynamicArrayBase super;

public:
	GEntityDynamicArray() : super(InitialSize) {}
};


class GEntityDynamicMap
{
private:
	typedef std::unique_ptr<GComponent> ComponentPointer;

protected:
	void doAddComponent(GComponent * component, GComponentManager * componentManager);
	void doRemoveComponent(GComponent * component, GComponentManager * componentManager);
	void doSetComponentManager(GComponentManager * newComponentManager, GComponentManager * oldComponentManager);
	GComponent * doGetComponentByTypeId(const unsigned int typeId) const;

private:
	std::map<unsigned int, ComponentPointer> componentMap;
};

template <const std::size_t ArraySize>
class GEntityStaticArray
{
private:
	typedef std::unique_ptr<GComponent> ComponentPointer;

protected:
	void doAddComponent(GComponent * component, GComponentManager * componentManager) {
		const unsigned int typeId = (unsigned int)component->getTypeId();
		if(typeId >= ArraySize) {
			return;
		}

		if(componentManager != nullptr && this->componentList[typeId]) {
			componentManager->remove(this->componentList[typeId].get());
		}

		this->componentList[typeId].reset(component);

		if(componentManager != nullptr) {
			componentManager->add(component);
		}
	}

	void doRemoveComponent(GComponent * component, GComponentManager * componentManager) {
		const unsigned int typeId = (unsigned int)component->getTypeId();
		if(typeId < ArraySize) {
			if(componentManager != nullptr) {
				componentManager->remove(component);
			}

			this->componentList[typeId].reset();
		}
	}

	void doSetComponentManager(GComponentManager * newComponentManager, GComponentManager * oldComponentManager) {
		if(oldComponentManager != nullptr) {
			for(auto & component : this->componentList) {
				if(component) {
					oldComponentManager->remove(component.get());
				}
			}
		}


		if(newComponentManager != nullptr) {
			for(auto & component : this->componentList) {
				if(component) {
					newComponentManager->add(component.get());
				}
			}
		}
	}

	GComponent * doGetComponentByTypeId(const unsigned int typeId) const {
		if(typeId < ArraySize) {
			return this->componentList[typeId].get();
		}

		return nullptr;
	}

private:
	std::array<ComponentPointer, ArraySize> componentList;
};


template <const std::size_t ArraySize>
class GEntityMixedArray
{
private:
	typedef std::unique_ptr<GComponent> ComponentPointer;

protected:
	void doAddComponent(GComponent * component, GComponentManager * componentManager) {
		ComponentPointer * componentSlot;
		const unsigned int typeId = (unsigned int)component->getTypeId();
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

		if(componentManager != nullptr && *componentSlot) {
			componentManager->remove(componentSlot->get());
		}

		componentSlot->reset(component);

		if(componentManager != nullptr) {
			componentManager->add(component);
		}
	}

	void doRemoveComponent(GComponent * component, GComponentManager * componentManager) {
		const unsigned int typeId = (unsigned int)component->getTypeId();
		if(typeId < ArraySize) {
			if(componentManager != nullptr) {
				componentManager->remove(component);
			}

			this->componentList[typeId].reset();
		}
		else {
			const unsigned int coldIndex = typeId - ArraySize;
			if(coldIndex < this->coldComponentList.size()) {
				if(componentManager != nullptr) {
					componentManager->remove(component);
				}

				this->coldComponentList[coldIndex].reset();
			}
		}
	}

	void doSetComponentManager(GComponentManager * newComponentManager, GComponentManager * oldComponentManager) {
		if(oldComponentManager != nullptr) {
			for(auto & component : this->componentList) {
				if(component) {
					oldComponentManager->remove(component.get());
				}
			}
			for(auto & component : this->coldComponentList) {
				if(component) {
					oldComponentManager->remove(component.get());
				}
			}
		}


		if(newComponentManager != nullptr) {
			for(auto & component : this->componentList) {
				if(component) {
					newComponentManager->add(component.get());
				}
			}
			for(auto & component : this->coldComponentList) {
				if(component) {
					newComponentManager->add(component.get());
				}
			}
		}
	}

	GComponent * doGetComponentByTypeId(const unsigned int typeId) const {
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
class GEntityMixedMap
{
private:
	typedef std::unique_ptr<GComponent> ComponentPointer;

protected:
	void doAddComponent(GComponent * component, GComponentManager * componentManager) {
		ComponentPointer * componentSlot;
		const unsigned int typeId = (unsigned int)component->getTypeId();
		if(typeId < ArraySize) {
			componentSlot = &this->componentList[typeId];
		}
		else {
			componentSlot = &this->coldComponentMap[typeId];
		}

		if(componentManager != nullptr && *componentSlot) {
			componentManager->remove(componentSlot->get());
		}

		componentSlot->reset(component);

		if(componentManager != nullptr) {
			componentManager->add(component);
		}
	}

	void doRemoveComponent(GComponent * component, GComponentManager * componentManager) {
		const unsigned int typeId = (unsigned int)component->getTypeId();
		if(typeId < ArraySize) {
			if(componentManager != nullptr) {
				componentManager->remove(component);
			}

			this->componentList[typeId].reset();
		}
		else {
			auto it = this->coldComponentMap.find(typeId);
			if(it != this->coldComponentMap.end()) {
				if(componentManager != nullptr) {
					componentManager->remove(component);
				}
				it->second.reset();
			}
		}
	}

	void doSetComponentManager(GComponentManager * newComponentManager, GComponentManager * oldComponentManager) {
		if(oldComponentManager != nullptr) {
			for(auto & component : this->componentList) {
				if(component) {
					oldComponentManager->remove(component.get());
				}
			}
			for(auto & item : this->coldComponentMap) {
				if(item.second) {
					oldComponentManager->remove(item.second.get());
				}
			}
		}


		if(newComponentManager != nullptr) {
			for(auto & component : this->componentList) {
				if(component) {
					newComponentManager->add(component.get());
				}
			}
			for(auto & item : this->coldComponentMap) {
				if(item.second) {
					newComponentManager->add(item.second.get());
				}
			}
		}
	}

	GComponent * doGetComponentByTypeId(const unsigned int typeId) const {
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


template <GEntityStoragePolicy Policy, std::size_t InitialSize>
struct GEntityStoragePolicySelector
{
};

template <std::size_t InitialSize>
struct GEntityStoragePolicySelector <GEntityStoragePolicy::dynamicArray, InitialSize>
{
	typedef GEntityDynamicArray<InitialSize> Result;
};

template <std::size_t InitialSize>
struct GEntityStoragePolicySelector <GEntityStoragePolicy::dynamicMap, InitialSize>
{
	typedef GEntityDynamicMap Result;
};

template <std::size_t InitialSize>
struct GEntityStoragePolicySelector <GEntityStoragePolicy::staticArray, InitialSize>
{
	typedef GEntityStaticArray<InitialSize> Result;
};

template <std::size_t InitialSize>
struct GEntityStoragePolicySelector <GEntityStoragePolicy::mixedArray, InitialSize>
{
	typedef GEntityMixedArray<InitialSize> Result;
};

template <std::size_t InitialSize>
struct GEntityStoragePolicySelector <GEntityStoragePolicy::mixedMap, InitialSize>
{
	typedef GEntityMixedMap<InitialSize> Result;
};


#ifndef GINCU_ENTITY_STORAGE_POLICY
#define GINCU_ENTITY_STORAGE_POLICY mixedMap
#endif

#ifndef GINCU_ENTITY_STORAGE_POLICY_INITIAL_SIZE
#define GINCU_ENTITY_STORAGE_POLICY_INITIAL_SIZE componentTypePrimaryCount
#endif

typedef GEntityStoragePolicySelector<GEntityStoragePolicy:: GINCU_ENTITY_STORAGE_POLICY, GINCU_ENTITY_STORAGE_POLICY_INITIAL_SIZE>::Result EntityBase;


} //namespace gincu


#endif
