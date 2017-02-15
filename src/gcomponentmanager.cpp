#include "gincu/gcomponentmanager.h"
#include "gincu/gcomponent.h"
#include "gincu/gcomponenttransform.h"
#include "gincu/gcomponentrender.h"
#include "gincu/gcomponentcamera.h"
#include "gincu/gcomponentanimation.h"
#include "gincu/gcomponenttouchhandler.h"
#include "gincu/grenderengine.h"
#include "gincu/gentityutil.h"
#include "gincu/gutil.h"

#include <algorithm>
#include <iterator>

#include "gincu/gcamera.h" // test

namespace gincu {

namespace {

void doRenderEntity(GEntity * entity);

void doRenderLocalTransformList(const std::vector<GComponentLocalTransform *> & transformList, GComponentRender * parentRender)
{
	const int count = (int)transformList.size();
	int index = 0;

	while(index < count && transformList[index]->getZOrder() < 0) {
		doRenderEntity(transformList[index]->getEntity());
		++index;
	}

	if(parentRender != nullptr) {
		parentRender->draw();
	}

	while(index < count) {
		doRenderEntity(transformList[index]->getEntity());
		++index;
	}
}

void doRenderEntity(GEntity * entity)
{
	GComponentRender * render = entity->getComponentByType<GComponentRender>();
	GComponentLocalTransform * localTransform = entity->getComponentByType<GComponentLocalTransform>();
	if(localTransform != nullptr) {
		doRenderLocalTransformList(localTransform->getSortedChildren(), render);
	}
	else {
		if(render != nullptr) {
			render->draw();
		}
	}
}

void doSortTransformList(std::vector<GComponentTransform *> & transformList)
{
	std::stable_sort(transformList.begin(), transformList.end(), [](const GComponentTransform * a, const GComponentTransform * b) {
		return a->getZOrder() < b->getZOrder();
/*
		int zOrderA, zOrderB;
		GComponentLocalTransform * localTransform;

		localTransform = a->getEntity()->getComponentByType<GComponentLocalTransform>();
		if(localTransform != nullptr) {
			zOrderA = localTransform->getZOrder();
		}
		else {
			zOrderA = a->getZOrder();
		}

		localTransform = b->getEntity()->getComponentByType<GComponentLocalTransform>();
		if(localTransform != nullptr) {
			zOrderB = localTransform->getZOrder();
		}
		else {
			zOrderB = b->getZOrder();
		}

		return zOrderA < zOrderB;
*/
	});
}

void doFindTouchHandlers(
		const std::vector<GComponent *> & touchHandlerList,
		const GPoint & position,
		std::vector<GComponentTouchHandler *> * outputResult
	)
{
	struct Item {
		GComponentTouchHandler * touchHandler;
		std::vector<int> zOrderList;
	};

	std::vector<Item> itemList;

	for(GComponent * component : touchHandlerList) {
		if(static_cast<GComponentTouchHandler *>(component)->canHandle(position)) {
			itemList.push_back({ static_cast<GComponentTouchHandler *>(component), std::vector<int>() });
		}
	}

	if(itemList.empty()) {
		return;
	}
	else if(itemList.size() == 1) {
		outputResult->push_back(itemList.front().touchHandler);
		return;
	}

	for(Item & item : itemList) {
		GEntity * entity = item.touchHandler->getEntity();

		while(entity != nullptr) {
			GComponentLocalTransform * localTransform = entity->getComponentByType<GComponentLocalTransform>();
			if(localTransform != nullptr) {
				item.zOrderList.push_back(localTransform->getZOrder());

				GComponentLocalTransform * parentLocalTransform = localTransform->getParent();
				if(parentLocalTransform != nullptr) {
					entity = parentLocalTransform->getEntity();
				}
				else {
					entity = nullptr;
				}
			}
			else {
				GComponentTransform * transform = entity->getComponentByType<GComponentTransform>();
				if(transform != nullptr) {
					item.zOrderList.push_back(transform->getZOrder());
				}
				else {
					item.zOrderList.push_back(0);
				}
				entity = nullptr;
			}
		}
	}

	std::stable_sort(itemList.begin(), itemList.end(), [](const Item & a, const Item & b) {
		int indexA = (int)a.zOrderList.size() - 1;
		int indexB = (int)b.zOrderList.size() - 1;

		while(indexA >= 0 && indexB >= 0) {
			if(a.zOrderList[indexA--] < b.zOrderList[indexB--]) {
				return true;
			}
		}

		if(indexA >= 0) {
			return a.zOrderList[indexA] < 0;
		}
		if(indexB >= 0) {
			return b.zOrderList[indexB] < 0;
		}

		return false;
	});

	const int count = (int)itemList.size();
	outputResult->resize(count);
	for(int i =  count - 1; i >= 0; --i) {
		outputResult->at(count - i - 1) = itemList[i].touchHandler;
	}
}


} //unnamed namespace


GComponentManager::CameraInfo::CameraInfo()
	: CameraInfo(nullptr)
{
}

GComponentManager::CameraInfo::CameraInfo(GComponentCamera * camera)
	:
		camera(camera),
		needSortRootTransformList(false)
{
}

void GComponentManager::CameraInfo::loadRootTransformList(const std::vector<GComponentTransform *> & componentList)
{
	this->rootTransformList.clear();

	std::copy_if(
		componentList.begin(),
		componentList.end(),
		std::back_inserter(this->rootTransformList),
		[=](const GComponentTransform * component) {
			return this->camera->belongs(component->getCameraId());
		}
	);
	this->needSortRootTransformList = true;
}

void GComponentManager::CameraInfo::loadTouchHandlerList(const std::vector<GComponent *> & componentList)
{
	this->touchHandlerList.clear();

	std::copy_if(
		componentList.begin(),
		componentList.end(),
		std::back_inserter(this->touchHandlerList),
		[=](const GComponent * component) {
			return this->belongs(component);
		}
	);
}

void GComponentManager::CameraInfo::zOrderChanged(GComponentTransform * transform)
{
	if(this->belongs(transform)) {
		this->needSortRootTransformList = true;
	}
}

void GComponentManager::CameraInfo::cameraIdChanged(GComponentTransform * transform, const unsigned int oldCameraId)
{
	if(this->camera->belongs(oldCameraId)) {
		if(this->camera->belongs(transform->getCameraId())) {
			return;
		}
		
		this->removeTransform(transform);
	}
	else {
		if(this->camera->belongs(transform->getCameraId())) {
			this->addTransform(transform);
		}
	}
}

void GComponentManager::CameraInfo::addTransform(GComponentTransform * component)
{
	if(this->camera->belongs(component->getCameraId())) {
		this->rootTransformList.push_back(component);
		this->needSortRootTransformList = true;
	}
}

void GComponentManager::CameraInfo::removeTransform(GComponentTransform * component)
{
	if(this->camera->belongs(component->getCameraId())) {
		removeValueFromContainer(this->rootTransformList, component);
	}
}

void GComponentManager::CameraInfo::addTouchHandler(GComponent * component)
{
	if(this->belongs(component)) {
		this->touchHandlerList.push_back(component);
	}
}

void GComponentManager::CameraInfo::removeTouchHandler(GComponent * component)
{
	if(this->belongs(component)) {
		removeValueFromContainer(this->touchHandlerList, component);
	}
}

bool GComponentManager::CameraInfo::belongs(const GComponent * component)
{
	GComponentTransform * transform = getComponentByTypeFromComponent<GComponentTransform>(component);
	if(transform != nullptr) {
		return this->camera->belongs(transform->getCameraId());
	}
	else {
		return false;
	}
}

void GComponentManager::CameraInfo::render()
{
	if(this->needSortRootTransformList) {
		this->needSortRootTransformList = false;
		doSortTransformList(this->rootTransformList);
	}

	GCamera c = this->camera->getCamera();
	GComponentTransform * transform = getComponentByTypeFromComponent<GComponentTransform>(this->camera);
	if(transform != nullptr) {
		c.apply(transform->getTransform());
	}
	GRenderEngine::getInstance()->switchCamera(c);

	for(GComponentTransform * transform : this->rootTransformList) {
		doRenderEntity(transform->getEntity());
	}
}

void GComponentManager::CameraInfo::findTouchHandlers(const GPoint & position, std::vector<GComponentTouchHandler *> * outputResult)
{
	doFindTouchHandlers(this->touchHandlerList, position, outputResult);
}


GComponentManager::GComponentManager()
	:
		componentListHotArray(componentTypeId_PrimaryCount),
		needSortRootTransformList(false),
		needSortCameraList(false)
{
}

void GComponentManager::add(GComponent * component)
{
	this->doGetComponentList(component->getTypeId())->push_back(component);

	switch(component->getTypeId()) {
	case componentTypeId_Transform:
		if(getParentLocalTransform(component->getEntity()) == nullptr) {
			this->rootTransformList.push_back(static_cast<GComponentTransform *>(component));
			this->needSortRootTransformList = true;

			for(CameraInfoPointer & cameraInfo : this->cameraInfoList) {
				cameraInfo->addTransform(static_cast<GComponentTransform *>(component));
			}
		}
		break;
	
	case componentTypeId_TouchHandler:
		for(CameraInfoPointer & cameraInfo : this->cameraInfoList) {
			cameraInfo->addTouchHandler(component);
		}
		break;
		
	case componentTypeId_Camera:
		this->needSortCameraList = true;
		GComponentCamera * camera = static_cast<GComponentCamera *>(component);
		this->cameraInfoList.push_back(std::make_shared<CameraInfo>(camera));
		this->cameraInfoList.back()->loadRootTransformList(this->rootTransformList);
		this->cameraInfoList.back()->loadTouchHandlerList(*this->doGetComponentList(GComponentTouchHandler::getComponentType()));
		break;
	}
}

void GComponentManager::remove(GComponent * component)
{
	ComponentListType * componentList = this->doGetComponentList(component->getTypeId());
	removeValueFromContainer(*componentList, component);

	switch(component->getTypeId()) {
	case componentTypeId_Transform:
		if(getParentLocalTransform(component->getEntity()) == nullptr) {
			removeValueFromContainer(this->rootTransformList, component);

			for(CameraInfoPointer & cameraInfo : this->cameraInfoList) {
				cameraInfo->removeTransform(static_cast<GComponentTransform *>(component));
			}
		}
		break;
		
	case componentTypeId_TouchHandler:
		for(CameraInfoPointer & cameraInfo : this->cameraInfoList) {
			cameraInfo->removeTouchHandler(component);
		}
		break;
		
	case componentTypeId_Camera:
		removeIfValueFromContainer(this->cameraInfoList, [=](const CameraInfoPointer & a) {
			return a->camera == component;
		});
		break;
	}
}

void GComponentManager::clear()
{
	this->componentListHotArray.clear();
	this->componentListColdMap.clear();
	this->rootTransformList.clear();
	this->needSortRootTransformList = false;
}

void GComponentManager::parentChanged(GComponentLocalTransform * localTransform)
{
	GComponentTransform * transform = getComponentByTypeFromComponent<GComponentTransform>(localTransform);
	if(transform != nullptr) {
		if(localTransform->getParent() == nullptr) {
			this->rootTransformList.push_back(transform);
			this->needSortRootTransformList = true;
			
			if(! this->needSortCameraList) {
				if(getComponentByTypeFromComponent<GComponentCamera>(localTransform) != nullptr) {
					this->needSortCameraList = true;
				}
			}
		}
		else {
			removeValueFromContainer(this->rootTransformList, transform);
		}
	}
}

void GComponentManager::zOrderChanged(GComponentTransform * transform)
{
	if(transform->getTypeId() == componentTypeId_Transform
		&& getParentLocalTransform(transform->getEntity()) == nullptr) {
		for(CameraInfoPointer & cameraInfo : this->cameraInfoList) {
			cameraInfo->zOrderChanged(transform);
		}
	}
}

void GComponentManager::cameraIdChanged(GComponentTransform * transform, const unsigned int oldCameraId)
{
	for(CameraInfoPointer & cameraInfo : this->cameraInfoList) {
		cameraInfo->cameraIdChanged(transform, oldCameraId);
	}
}

void GComponentManager::cameraMaskChanged(GComponentCamera * camera)
{
	auto it = std::find_if(this->cameraInfoList.begin(), this->cameraInfoList.end(),
		[=](const CameraInfoPointer & info) { return info->camera == camera; }
	);
	if(it != this->cameraInfoList.end()) {
		(*it)->loadRootTransformList(this->rootTransformList);
		(*it)->loadTouchHandlerList(*this->doGetComponentList(GComponentTouchHandler::getComponentType()));
	}
}

void GComponentManager::updateAnimation()
{
	ComponentListType * componentList = this->doGetComponentList(GComponentAnimation::getComponentType());
	for(GComponent * component : *componentList) {
		static_cast<GComponentAnimation *>(component)->update();
	}
}

void GComponentManager::updateLocalTransforms()
{
	ComponentListType * componentList = this->doGetComponentList(GComponentLocalTransform::getComponentType());
	for(GComponent * component : *componentList) {
		if(component != nullptr && static_cast<GComponentLocalTransform *>(component)->getParent() == nullptr) {
			static_cast<GComponentLocalTransform *>(component)->applyGlobal();
		}
	}
}

void GComponentManager::render()
{
	if(this->needSortCameraList) {
		this->needSortCameraList = false;
		// TODO
	}
	for(CameraInfoPointer & cameraInfo : this->cameraInfoList) {
		cameraInfo->render();
	}
	return;

/*
	const float w = 900, h = 600;
	GCamera camera;
	GTransform transform;
	transform.setProjectionMode(true);
	camera.setViewport({ 0, 0, w, h });
	transform.setOrigin({ w, h });
	GComponentAnchor anchor(GRenderAnchor::leftTop);
	transform.setPosition({ w / 2, h / 2 });
//	anchor.setFlipX(true);
	anchor.apply(transform, { w, h });
	camera.apply(transform);
	GRenderEngine::getInstance()->switchCamera(camera);
*/

	if(this->needSortRootTransformList) {
		this->needSortRootTransformList = false;
		doSortTransformList(this->rootTransformList);
	}

	for(GComponentTransform * transform : this->rootTransformList) {
		doRenderEntity(transform->getEntity());
	}
}

void GComponentManager::findTouchHandlers(const GPoint & position, std::vector<GComponentTouchHandler *> * outputResult)
{
	for(CameraInfoPointer & cameraInfo : this->cameraInfoList) {
		cameraInfo->findTouchHandlers(position, outputResult);
	}
	return;

	doFindTouchHandlers(*this->doGetComponentList(GComponentTouchHandler::getComponentType()), position, outputResult);
}

GComponentManager::ComponentListType * GComponentManager::doGetComponentList(const unsigned int typeId)
{
	if(typeId < this->componentListHotArray.size()) {
		return &this->componentListHotArray[typeId];
	}
	else {
		return &this->componentListColdMap[typeId];
	}
}


} //namespace gincu

