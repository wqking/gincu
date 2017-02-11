#include "gincu/gcomponentmanager.h"
#include "gincu/gcomponent.h"
#include "gincu/gcomponenttransform.h"
#include "gincu/gcomponentrender.h"
#include "gincu/gcomponentanimation.h"
#include "gincu/gcomponenttouchhandler.h"
#include "gincu/grenderengine.h"
#include "gincu/gutil.h"

#include <algorithm>

namespace gincu {

GComponentManager::GComponentManager()
	:
		componentListHotArray(componentTypeId_PrimaryCount),
		needSortRootTransformList(false)
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

void GComponentManager::parentChanged(GComponentLocalTransform * localTransform)
{
	GComponentTransform * transform = getComponentByTypeFromComponent<GComponentTransform>(localTransform);
	if(transform != nullptr) {
		if(localTransform->getParent() == nullptr) {
			this->rootTransformList.push_back(transform);
			this->needSortRootTransformList = true;
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

} //unnamed namespace

void GComponentManager::render()
{
	if(this->needSortRootTransformList) {
		this->needSortRootTransformList = false;

		std::stable_sort(this->rootTransformList.begin(), this->rootTransformList.end(), [](const GComponentTransform * a, const GComponentTransform * b) {
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

	for(GComponentTransform * transform : this->rootTransformList) {
		doRenderEntity(transform->getEntity());
	}
}

void GComponentManager::findTouchHandlers(const GPoint & position, std::vector<GComponentTouchHandler *> * outputResult)
{
	ComponentListType * componentList = this->doGetComponentList(GComponentTouchHandler::getComponentType());
	for(GComponent * component : *componentList) {
		if(static_cast<GComponentTouchHandler *>(component)->canHandle(position)) {
			outputResult->push_back(static_cast<GComponentTouchHandler *>(component));
		}
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

