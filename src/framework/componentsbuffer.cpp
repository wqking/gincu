#include "framework/componentsbuffer.h"
#include "framework/component.h"
#include "framework/componenttransform.h"
#include "framework/componentrender.h"
#include "framework/componenttouchhandler.h"

#include <algorithm>

namespace gincu {

ComponentsBuffer::ComponentsBuffer()
	: componentListBuffer(componentTypeId_PrimaryCount)
{
}

void ComponentsBuffer::add(Component * component)
{
	this->doGetComponentList(component->getTypeId())->push_back(component);
}

void ComponentsBuffer::remove(Component * component)
{
	ComponentListType * componentList = this->doGetComponentList(component->getTypeId());
	componentList->erase(std::remove(componentList->begin(), componentList->end(), component), componentList->end());
}

void ComponentsBuffer::updateLocalTransforms()
{
	ComponentListType * componentList = this->doGetComponentList(ComponentLocalTransform::getComponentType());
	for(Component * component : *componentList) {
		if(component != nullptr && static_cast<ComponentLocalTransform *>(component)->getParent() == nullptr) {
			static_cast<ComponentLocalTransform *>(component)->applyGlobal();
		}
	}
}

void ComponentsBuffer::render()
{
	ComponentListType * componentList = this->doGetComponentList(ComponentRender::getComponentType());
	for(Component * component : *componentList) {
		static_cast<ComponentRender *>(component)->draw();
	}
}

void ComponentsBuffer::findTouchHandlers(const GamePoint & position, std::vector<ComponentTouchHandler *> * outputResult)
{
	ComponentListType * componentList = this->doGetComponentList(ComponentTouchHandler::getComponentType());
	for(Component * component : *componentList) {
		if(static_cast<ComponentTouchHandler *>(component)->canHandle(position)) {
			outputResult->push_back(static_cast<ComponentTouchHandler *>(component));
		}
	}
}

ComponentsBuffer::ComponentListType * ComponentsBuffer::doGetComponentList(const unsigned int typeId)
{
	if((int)this->componentListBuffer.size() <= typeId) {
		this->componentListBuffer.resize(typeId + 1);
	}
	
	return &this->componentListBuffer[typeId];
}


} //namespace gincu

