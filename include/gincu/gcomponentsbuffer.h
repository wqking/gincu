#ifndef GCOMPONENTSBUFFER_H
#define GCOMPONENTSBUFFER_H

#include "gincu/ggeometry.h"

#include <vector>

namespace gincu {

class Component;
class ComponentTouchHandler;

// This is NOT for pooled component allocation
class ComponentsBuffer
{
private:
	typedef std::vector<Component *> ComponentListType;

public:
	ComponentsBuffer();

	void add(Component * component);
	void remove(Component * component);
	
	void updateLocalTransforms();
	void render();
	void findTouchHandlers(const GamePoint & position, std::vector<ComponentTouchHandler *> * outputResult);
	
private:
	ComponentListType * doGetComponentList(const unsigned int typeId);

private:
	std::vector<ComponentListType> componentListBuffer;
};


} //namespace gincu



#endif
