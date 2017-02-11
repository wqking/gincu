#include "gincu/gcomponentmanager.h"
#include "gincu/gcomponent.h"
#include "gincu/gcomponenttransform.h"
#include "gincu/gcomponentrender.h"
#include "gincu/gcomponentanimation.h"
#include "gincu/gcomponenttouchhandler.h"
#include "gincu/grenderengine.h"

#include <algorithm>

namespace gincu {

GComponentManager::GComponentManager()
	: componentListHotArray(componentTypeId_PrimaryCount)
{
}

void GComponentManager::add(GComponent * component)
{
	this->doGetComponentList(component->getTypeId())->push_back(component);
}

void GComponentManager::remove(GComponent * component)
{
	ComponentListType * componentList = this->doGetComponentList(component->getTypeId());
	componentList->erase(std::remove(componentList->begin(), componentList->end(), component), componentList->end());
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
	ComponentListType * componentList = this->doGetComponentList(GComponentRender::getComponentType());

	for(GComponent * component : *componentList) {
		static_cast<GComponentRender *>(component)->draw();
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

