#include "gincu/gcomponentsbuffer.h"
#include "gincu/gcomponent.h"
#include "gincu/gcomponenttransform.h"
#include "gincu/gcomponentrender.h"
#include "gincu/gcomponenttouchhandler.h"
#include "gincu/grenderengine.h"

#include <algorithm>

namespace gincu {

namespace {

const GRenderInfo * getRenderBatchGroup(const GComponentRender * render)
{
	if(render == nullptr) {
		return nullptr;
	}
	else {
		const GRenderInfo * renderInfo = render->getBatchGroup();
		if(renderInfo->texture == nullptr) {
			return nullptr;
		}
		else {
			return renderInfo;
		}
	}
}


} //unnamed namespace

GComponentsBuffer::GComponentsBuffer()
	: componentListBuffer(componentTypeId_PrimaryCount)
{
}

void GComponentsBuffer::add(GComponent * component)
{
	this->doGetComponentList(component->getTypeId())->push_back(component);
}

void GComponentsBuffer::remove(GComponent * component)
{
	ComponentListType * componentList = this->doGetComponentList(component->getTypeId());
	componentList->erase(std::remove(componentList->begin(), componentList->end(), component), componentList->end());
}

void GComponentsBuffer::updateLocalTransforms()
{
	ComponentListType * componentList = this->doGetComponentList(GComponentLocalTransform::getComponentType());
	for(GComponent * component : *componentList) {
		if(component != nullptr && static_cast<GComponentLocalTransform *>(component)->getParent() == nullptr) {
			static_cast<GComponentLocalTransform *>(component)->applyGlobal();
		}
	}
}

void GComponentsBuffer::render()
{
	ComponentListType * componentList = this->doGetComponentList(GComponentRender::getComponentType());
	if(componentList->empty()) {
		return;
	}

	//for(GComponent * component : *componentList) {
	//	static_cast<GComponentRender *>(component)->draw();
	//}
	//return;

	const int count = (int)componentList->size();
	GComponentRender * currentRender = nullptr;
	GComponentRender * nextRender = static_cast<GComponentRender *>(componentList->at(0));
	GRenderEngine * renderEngine = GRenderEngine::getInstance();
	bool inBatchDraw = false;

	const GRenderInfo * previousGroup;
	const GRenderInfo * currentGroup = nullptr;
	const GRenderInfo * nextGroup = getRenderBatchGroup(nextRender);

	for(int i = 0; i < count; ++i) {
		currentRender = nextRender;
		nextRender = (i < count - 1 ? static_cast<GComponentRender *>(componentList->at(i + 1)) : nullptr);

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

void GComponentsBuffer::findTouchHandlers(const GPoint & position, std::vector<GComponentTouchHandler *> * outputResult)
{
	ComponentListType * componentList = this->doGetComponentList(GComponentTouchHandler::getComponentType());
	for(GComponent * component : *componentList) {
		if(static_cast<GComponentTouchHandler *>(component)->canHandle(position)) {
			outputResult->push_back(static_cast<GComponentTouchHandler *>(component));
		}
	}
}

GComponentsBuffer::ComponentListType * GComponentsBuffer::doGetComponentList(const unsigned int typeId)
{
	if(this->componentListBuffer.size() <= typeId) {
		this->componentListBuffer.resize(typeId + 1);
	}
	
	return &this->componentListBuffer[typeId];
}


} //namespace gincu

