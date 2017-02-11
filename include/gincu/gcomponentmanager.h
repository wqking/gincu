#ifndef GCOMPONENTMANAGER_H
#define GCOMPONENTMANAGER_H

#include "gincu/ggeometry.h"

#include <vector>
#include <map>

namespace gincu {

class GComponent;
class GComponentTouchHandler;

class GComponentManager
{
private:
	typedef std::vector<GComponent *> ComponentListType;

public:
	GComponentManager();

	void add(GComponent * component);
	void remove(GComponent * component);
	
	void updateAnimation();
	void updateLocalTransforms();
	void render();

	void findTouchHandlers(const GPoint & position, std::vector<GComponentTouchHandler *> * outputResult);

	void updateDuringRender() {
		this->updateAnimation();
		this->updateLocalTransforms();
		this->render();
	}
	
private:
	ComponentListType * doGetComponentList(const unsigned int typeId);

private:
	std::vector<ComponentListType> componentListHotArray;
	std::map<unsigned int, ComponentListType> componentListColdMap;
};


} //namespace gincu



#endif
