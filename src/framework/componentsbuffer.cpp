#include "framework/componentsbuffer.h"
#include "framework/component.h"
#include "framework/componenttransform.h"
#include "framework/componentrender.h"
#include "framework/componenttouchhandler.h"
#include "engine/renderengine.h"

#include <algorithm>

namespace gincu {

namespace {

const RenderInfo * getRenderBatchGroup(const ComponentRender * render)
{
	if(render == nullptr) {
		return nullptr;
	}
	else {
		const RenderInfo * renderInfo = render->getBatchGroup();
		if(renderInfo->texture == nullptr) {
			return nullptr;
		}
		else {
			return renderInfo;
		}
	}
}


} //unnamed namespace

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
	if(componentList->empty()) {
		return;
	}

	//for(Component * component : *componentList) {
	//	static_cast<ComponentRender *>(component)->draw();
	//}
	//return;

	const int count = (int)componentList->size();
	ComponentRender * previousRender;
	ComponentRender * currentRender = nullptr;
	ComponentRender * nextRender = static_cast<ComponentRender *>(componentList->at(0));
	RenderEngine * renderEngine = RenderEngine::getInstance();
	bool inBatchDraw = false;

	const RenderInfo * previousGroup;
	const RenderInfo * currentGroup = nullptr;
	const RenderInfo * nextGroup = getRenderBatchGroup(nextRender);

	for(int i = 0; i < count; ++i) {
		previousRender = currentRender;
		currentRender = nextRender;
		nextRender = (i < count - 1 ? static_cast<ComponentRender *>(componentList->at(i + 1)) : nullptr);

		previousGroup = currentGroup;
		currentGroup = nextGroup;
		nextGroup = getRenderBatchGroup(nextRender);

		if(! inBatchDraw) {
			if(currentGroup != nullptr
				&& nextGroup != nullptr
				&& *currentGroup == *nextGroup
			) {
				renderEngine->beginBatchDraw();
				inBatchDraw = true;
			}
		}
		else {
			if(currentGroup == nullptr) {
				renderEngine->endBatchDraw();
				inBatchDraw = false;
			}
			else if(currentGroup != nullptr
				&& previousGroup != nullptr
				&& *currentGroup != *previousGroup) {
				renderEngine->endBatchDraw();
				inBatchDraw = false;
			}
		}

		currentRender->draw();
	}

	if(inBatchDraw) {
		renderEngine->endBatchDraw();
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
	if(this->componentListBuffer.size() <= typeId) {
		this->componentListBuffer.resize(typeId + 1);
	}
	
	return &this->componentListBuffer[typeId];
}


} //namespace gincu

