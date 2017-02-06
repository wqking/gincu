#ifndef GCOMPONENTSBUFFER_H
#define GCOMPONENTSBUFFER_H

#include "gincu/ggeometry.h"

#include <vector>

namespace gincu {

class GComponent;
class GComponentTouchHandler;

// This is NOT for pooled component allocation
class GComponentsBuffer
{
private:
	typedef std::vector<GComponent *> ComponentListType;

public:
	GComponentsBuffer();

	void add(GComponent * component);
	void remove(GComponent * component);
	
	void updateLocalTransforms();
	void render();
	void findTouchHandlers(const GPoint & position, std::vector<GComponentTouchHandler *> * outputResult);
	
private:
	ComponentListType * doGetComponentList(const unsigned int typeId);

private:
	std::vector<ComponentListType> componentListBuffer;
};


} //namespace gincu



#endif
