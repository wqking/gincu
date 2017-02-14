#ifndef GCOMPONENTMANAGER_H
#define GCOMPONENTMANAGER_H

#include "gincu/ggeometry.h"

#include <vector>
#include <map>

namespace gincu {

class GComponent;
class GComponentTouchHandler;
class GComponentTransform;
class GComponentLocalTransform;
class GComponentCamera;

class GComponentManager
{
private:
	typedef std::vector<GComponent *> ComponentListType;

public:
	GComponentManager();

	void add(GComponent * component);
	void remove(GComponent * component);
	void clear();

	void parentChanged(GComponentLocalTransform * localTransform);
	void zOrderChanged(GComponentTransform * transform); // this can be either a global or local transform
	void cameraIdChanged(GComponentTransform * transform);
	void cameraMaskChanged(GComponentCamera * camera);
	
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
	mutable std::vector<GComponentTransform *> rootTransformList;
	mutable bool needSortRootTransformList;
	mutable bool needSortCameraList;
};


} //namespace gincu



#endif
