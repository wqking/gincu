#include "gincu/gcomponentmanager.h"
#include "gincu/gcomponent.h"
#include "gincu/gcomponenttransform.h"
#include "gincu/gcomponentrender.h"
#include "gincu/gcomponentcamera.h"
#include "gincu/gcomponentanimation.h"
#include "gincu/gcomponenttouchhandler.h"
#include "gincu/grenderengine.h"
#include "gincu/gutil.h"

#include <algorithm>

#include "gincu/gcamera.h" // test

namespace gincu {

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

	if(component->getTypeId() == componentTypeId_Transform) {
		if(getParentLocalTransform(component->getEntity()) == nullptr) {
			this->rootTransformList.push_back(static_cast<GComponentTransform *>(component));
			this->needSortRootTransformList = true;
		}
	}
	if(component->getTypeId() == componentTypeId_Camera) {
		this->needSortCameraList = true;
	}
}

void GComponentManager::remove(GComponent * component)
{
	ComponentListType * componentList = this->doGetComponentList(component->getTypeId());
	removeValueFromContainer(*componentList, component);

	if(component->getTypeId() == componentTypeId_Transform) {
		if(getParentLocalTransform(component->getEntity()) == nullptr) {
			removeValueFromContainer(this->rootTransformList, component);
		}
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
	});
}

} //unnamed namespace

void GComponentManager::render()
{
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
	struct Item {
		GComponentTouchHandler * touchHandler;
		std::vector<int> zOrderList;
	};

	std::vector<Item> itemList;

	ComponentListType * componentList = this->doGetComponentList(GComponentTouchHandler::getComponentType());
	for(GComponent * component : *componentList) {
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

