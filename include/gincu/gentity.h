#ifndef GENTITY_H
#define GENTITY_H

#include "gincu/gentitypolicy.h"

#include <memory>
#include <vector>

namespace gincu {

class GComponent;
class GComponentManager;

class GEntity : public EntityBase
{
public:
	void * operator new (const std::size_t size);
	void operator delete(void * p);

	GEntity();
	~GEntity();

	GEntity * addComponent(GComponent * component);
	void removeComponent(GComponent * component);
	
	void setComponentManager(GComponentManager * componentManager);
	GComponentManager * getComponentManager() const { return this->componentManager; }

	GComponent * getComponentByTypeId(const unsigned int typeId) const;
	
	template <typename T>
	T * getComponentByType() const {
		return static_cast<T *>(this->getComponentByTypeId(T::getComponentType()));
	}
	
private:
	GComponentManager * componentManager;
};


} //namespace gincu

#endif
