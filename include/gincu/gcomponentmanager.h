#ifndef GCOMPONENTMANAGER_H
#define GCOMPONENTMANAGER_H

#include "gincu/ggeometry.h"
#include "gincu/gcomponenttouchhandler.h"

#include <vector>
#include <map>
#include <memory>

namespace gincu {

class GComponent;
class GComponentTouchHandler;
class GComponentTransform;
class GComponentLocalTransform;
class GComponentCamera;
class GRenderContext;

class GComponentManager
{
private:
	typedef std::vector<GComponent *> ComponentListType;
	
	struct CameraInfo
	{
		CameraInfo();
		explicit CameraInfo(GComponentCamera * camera);
		
		void loadRootTransformList(const std::vector<GComponentTransform *> & componentList);
		void loadTouchHandlerList(const std::vector<GComponent *> & componentList);

		void zOrderChanged(GComponentTransform * transform);
		void cameraIdChanged(GComponentTransform * transform, const unsigned int oldCameraId);
		
		void addTransform(GComponentTransform * component);
		void removeTransform(GComponentTransform * component);
		void addTouchHandler(GComponent * component);
		void removeTouchHandler(GComponent * component);

		bool belongs(const GComponent * component);

		void render(GRenderContext * renderContext);
		void findTouchHandlers(std::vector<GTouchHandlerFindResult> * outputResult, const GPoint & screenPosition);

		GComponentCamera * camera;
		std::vector<GComponentTransform *> rootTransformList;
		bool needSortRootTransformList;
		std::vector<GComponent *> touchHandlerList;
	};
	
	typedef std::shared_ptr<CameraInfo> CameraInfoPointer;

public:
	GComponentManager();

	void add(GComponent * component);
	void remove(GComponent * component);
	void clear();

	void parentChanged(GComponentLocalTransform * localTransform);
	void zOrderChanged(GComponentTransform * transform);
	void cameraIdChanged(GComponentTransform * transform, const unsigned int oldCameraId);
	void cameraMaskChanged(GComponentCamera * camera);
	
	void updateAnimation();
	void updateLocalTransforms();
	void render(GRenderContext * renderContext);

	void findTouchHandlers(std::vector<GTouchHandlerFindResult> * outputResult, const GPoint & screenPosition);

	void updateDuringRender(GRenderContext * renderContext) {
		this->updateAnimation();
		this->updateLocalTransforms();
		this->render(renderContext);
	}
	
private:
	ComponentListType * doGetComponentList(const GComponentType typeId);

private:
	std::vector<ComponentListType> componentListHotArray;
	std::map<GComponentType, ComponentListType> componentListColdMap;
	mutable std::vector<GComponentTransform *> rootTransformList;
	mutable bool needSortRootTransformList;
	mutable std::vector<CameraInfoPointer> cameraInfoList;
	mutable bool needSortCameraList;
};


} //namespace gincu



#endif
