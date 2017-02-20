#include "gincu/ecs/gcomponentmanager.h"
#include "gincu/ecs/gcomponent.h"
#include "gincu/ecs/gcomponenttransform.h"
#include "gincu/ecs/gcomponentlocaltransform.h"
#include "gincu/ecs/gcomponentrender.h"
#include "gincu/ecs/gcomponentcamera.h"
#include "gincu/ecs/gentityutil.h"
#include "gincu/grendercontext.h"
#include "gincu/gutil.h"

#include <algorithm>
#include <iterator>

#include "gincu/gcamera.h" // test

namespace gincu {

namespace {

void doRenderEntity(GRenderContext * renderContext, GEntity * entity);

void doRenderLocalTransformList(GRenderContext * renderContext, const std::vector<GComponentLocalTransform *> & transformList, GComponentRender * parentRender)
{
	const int count = (int)transformList.size();
	int index = 0;

	while(index < count && transformList[index]->getZOrder() < 0) {
		doRenderEntity(renderContext, transformList[index]->getEntity());
		++index;
	}

	if(parentRender != nullptr) {
		parentRender->draw(renderContext);
	}

	while(index < count) {
		doRenderEntity(renderContext, transformList[index]->getEntity());
		++index;
	}
}

void doRenderEntity(GRenderContext * renderContext, GEntity * entity)
{
	GComponentRender * render = entity->getComponentByType<GComponentRender>();
	GComponentLocalTransform * localTransform = entity->getComponentByType<GComponentLocalTransform>();
	if(localTransform != nullptr) {
		doRenderLocalTransformList(renderContext, localTransform->getSortedChildren(), render);
	}
	else {
		if(render != nullptr) {
			render->draw(renderContext);
		}
	}
}

void doSortTransformList(std::vector<GComponentTransform *> & transformList)
{
	std::stable_sort(transformList.begin(), transformList.end(), [](const GComponentTransform * a, const GComponentTransform * b) {
		return getZOrder(a->getEntity()) < getZOrder(b->getEntity());
	});
}

void doFindTouchHandlers(
		std::vector<GTouchHandlerFindResult> * outputResult,
		const std::vector<GComponent *> & touchHandlerList,
		const GPoint & worldPosition
	)
{
	struct Item {
		GComponentTouchHandler * touchHandler;
		std::vector<int> zOrderList;
	};

	std::vector<Item> itemList;

	for(GComponent * component : touchHandlerList) {
		if(static_cast<GComponentTouchHandler *>(component)->canHandle(worldPosition)) {
			itemList.push_back({ static_cast<GComponentTouchHandler *>(component), std::vector<int>() });
		}
	}

	if(itemList.empty()) {
		return;
	}
	else if(itemList.size() == 1) {
		outputResult->push_back({ itemList.front().touchHandler, worldPosition });
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
		outputResult->at(count - i - 1) = { itemList[i].touchHandler, worldPosition };
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

		// Can't call removeTransform because it checks belongs.
		removeValueFromContainer(this->rootTransformList, transform);
	}
	else {
		if(this->camera->belongs(transform->getCameraId())) {
			if(getParentLocalTransform(transform->getEntity()) == nullptr) {
				this->addTransform(transform);
			}
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

void GComponentManager::CameraInfo::render(GRenderContext * renderContext)
{
	if(this->needSortRootTransformList) {
		this->needSortRootTransformList = false;
		doSortTransformList(this->rootTransformList);
	}

	GCamera c = this->camera->getCamera();
	GComponentTransform * componentTransform = getComponentByTypeFromComponent<GComponentTransform>(this->camera);
	if(componentTransform != nullptr) {
		const GSize worldSize = c.getWorldSize();
		componentTransform->getTransform().setOrigin({ worldSize.width, worldSize.height });
		componentTransform->getTransform().setProjectionMode(true);
		const GRect viewport = c.getViewportPixels();
		c.apply(computeRenderableMatrix(componentTransform, getSize(viewport)));
	}
	renderContext->switchCamera(c);

	for(GComponentTransform * transform : this->rootTransformList) {
		doRenderEntity(renderContext, transform->getEntity());
	}
}

void GComponentManager::CameraInfo::findTouchHandlers(std::vector<GTouchHandlerFindResult> * outputResult, const GPoint & screenPosition)
{
	const GRect viewport = this->camera->getCamera().getViewportPixels();
	if(isInRect(screenPosition, viewport)) {
		doFindTouchHandlers(outputResult, this->touchHandlerList, this->camera->getCamera().mapScreenToCamera(screenPosition));
	}
}


GComponentManager::GComponentManager()
	:
		componentListHotArray(componentTypePrimaryCount),
		needSortRootTransformList(false),
		needSortCameraList(false)
{
}

void GComponentManager::add(GComponent * component)
{
	this->doGetComponentList(component->getType())->push_back(component);

	switch(component->getType()) {
	case GComponentType::transform:
		if(getParentLocalTransform(component->getEntity()) == nullptr) {
			this->rootTransformList.push_back(static_cast<GComponentTransform *>(component));
			this->needSortRootTransformList = true;

			for(CameraInfoPointer & cameraInfo : this->cameraInfoList) {
				cameraInfo->addTransform(static_cast<GComponentTransform *>(component));
			}
		}
		break;
	
	case GComponentType::touchHandler:
		for(CameraInfoPointer & cameraInfo : this->cameraInfoList) {
			cameraInfo->addTouchHandler(component);
		}
		break;
		
	case GComponentType::camera: {
		this->needSortCameraList = true;
		GComponentCamera * camera = static_cast<GComponentCamera *>(component);
		this->cameraInfoList.push_back(std::make_shared<CameraInfo>(camera));
		this->cameraInfoList.back()->loadRootTransformList(this->rootTransformList);
		this->cameraInfoList.back()->loadTouchHandlerList(*this->doGetComponentList(GComponentTouchHandler::getComponentType()));
	}
		break;
		
	default:
		break;
	}
}

void GComponentManager::remove(GComponent * component)
{
	ComponentListType * componentList = this->doGetComponentList(component->getType());
	removeValueFromContainer(*componentList, component);

	switch(component->getType()) {
	case GComponentType::transform:
		if(getParentLocalTransform(component->getEntity()) == nullptr) {
			removeValueFromContainer(this->rootTransformList, component);

			for(CameraInfoPointer & cameraInfo : this->cameraInfoList) {
				cameraInfo->removeTransform(static_cast<GComponentTransform *>(component));
			}
		}
		break;
		
	case GComponentType::touchHandler:
		for(CameraInfoPointer & cameraInfo : this->cameraInfoList) {
			cameraInfo->removeTouchHandler(component);
		}
		break;
		
	case GComponentType::camera:
		removeIfFromContainer(this->cameraInfoList, [=](const CameraInfoPointer & a) {
			return a->camera == component;
		});
		break;
		
	default:
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
	if(getParentLocalTransform(transform->getEntity()) == nullptr) {
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

void GComponentManager::updateLocalTransforms()
{
	ComponentListType * componentList = this->doGetComponentList(GComponentLocalTransform::getComponentType());
	for(GComponent * component : *componentList) {
		if(component != nullptr && static_cast<GComponentLocalTransform *>(component)->getParent() == nullptr) {
			static_cast<GComponentLocalTransform *>(component)->applyGlobal();
		}
	}
}

void GComponentManager::render(GRenderContext * renderContext)
{
	if(this->needSortCameraList) {
		this->needSortCameraList = false;
		
		std::stable_sort(this->cameraInfoList.begin(), this->cameraInfoList.end(),
			[=](const CameraInfoPointer & a, const CameraInfoPointer & b) {
				return getZOrder(a->camera->getEntity()) < getZOrder(b->camera->getEntity());
		});
	}
	for(CameraInfoPointer & cameraInfo : this->cameraInfoList) {
		cameraInfo->render(renderContext);
	}
}

void GComponentManager::findTouchHandlers(std::vector<GTouchHandlerFindResult> * outputResult, const GPoint & screenPosition)
{
	for(auto it = this->cameraInfoList.rbegin(); it != this->cameraInfoList.rend(); ++it) {
		(*it)->findTouchHandlers(outputResult, screenPosition);
	}
}

GComponentManager::ComponentListType * GComponentManager::doGetComponentList(const GComponentType typeId)
{
	if((unsigned int)typeId < this->componentListHotArray.size()) {
		return &this->componentListHotArray[(unsigned int)typeId];
	}
	else {
		return &this->componentListColdMap[typeId];
	}
}


} //namespace gincu

