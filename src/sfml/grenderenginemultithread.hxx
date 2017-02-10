#include "gincu/grenderengine.h"
#include "gincu/gtransform.h"
#include "gincu/gimage.h"
#include "gincu/gspritesheetrender.h"
#include "gincu/gtextrender.h"
#include "gincu/grectrender.h"
#include "gincu/gapplication.h"
#include "gincu/grenderinfo.h"
#include "gsfmlutil.h"
#include "gimagedata.h"
#include "gtextrenderdata.h"
#include "grectrenderdata.h"
#include "grenderenginedata.h"

#include <cassert>

namespace gincu {

void GRenderEngine::doInitialize()
{
	this->data->window->setActive(false);
}

void GRenderEngine::render()
{
	this->data->window->clear(gameColorToSfml(GApplication::getInstance()->getConfigInfo().backgroundColor));

	this->renderList();

	this->endBatchDraw();

	this->data->window->display();
}

void GRenderEngine::draw(const GTextRender & text, const GTransform & transform, const GRenderInfo * renderInfo)
{
	this->endBatchDraw();

	sf::RenderStates renderStates(transform.getSfmlTransform());
	copyBlendAndShaderToSfml(&renderStates, renderInfo);
	this->data->window->draw(text.getData()->text, renderStates);
}

void GRenderEngine::draw(const GRectRender & rect, const GTransform & transform, const GRenderInfo * renderInfo)
{
	this->endBatchDraw();

	sf::RenderStates renderStates(transform.getSfmlTransform());
	copyBlendAndShaderToSfml(&renderStates, renderInfo);
	this->data->window->draw(rect.getData()->rectangle, renderStates);
}

void GRenderEngine::beginBatchDraw()
{
	this->data->clearBatchDrawState();
	this->data->inBatchDraw = true;
}

void GRenderEngine::endBatchDraw()
{
	this->flush();

	if(this->data->inBatchDraw) {
		if(this->data->batchDrawImageData) {
			sf::RenderStates renderStates(&this->data->batchDrawImageData->texture);
			copyBlendAndShaderToSfml(&renderStates, &this->data->batchDrawRenderInfo);
			this->data->window->draw(this->data->batchDrawVertexArray, renderStates);
		}

		this->data->clearBatchDrawState();
	}
}

void GRenderEngine::flush()
{
	GCachedRenderItem & cachedItem = this->data->cachedRenderItem;
	switch(cachedItem.type) {
	case GCachedRenderType::texture:
		this->data->directDrawTexture(cachedItem.imageData, cachedItem.imageRect, cachedItem.imageTransform, &cachedItem.imageRenderInfo);
		break;

	case GCachedRenderType::none:
		break;
	}

	cachedItem.reset();
}

void GRenderEngine::doDrawTexture(const std::shared_ptr<GImageData> & texture, const GRect & rect, const GTransform & transform, const GRenderInfo * renderInfo)
{
	if(! texture) {
		return;
	}

	GCachedRenderItem & cachedItem = this->data->cachedRenderItem;
	if(cachedItem.type != GCachedRenderType::none && cachedItem.type != GCachedRenderType::texture) {
		this->flush();
	}

	bool needCache = false;
	if(this->data->inBatchDraw) {
		if(texture == this->data->batchDrawImageData
			&& *renderInfo == this->data->batchDrawRenderInfo) {
			this->data->batchDrawTexture(texture, rect, transform, renderInfo);
		}
		else {
			this->endBatchDraw();
			needCache = true;
		}
	}
	else {
		if(texture == cachedItem.imageData
			&& *renderInfo == cachedItem.imageRenderInfo) {
			this->beginBatchDraw();
			this->data->batchDrawTexture(cachedItem.imageData, cachedItem.imageRect, cachedItem.imageTransform, &cachedItem.imageRenderInfo);
			this->data->batchDrawTexture(texture, rect, transform, renderInfo);
		}
		else {
			if(cachedItem.imageData) {
				this->flush();
			}
			needCache = true;
		}
	}
	if(needCache) {
		cachedItem.type = GCachedRenderType::texture;
		cachedItem.imageData = texture;
		cachedItem.imageRect = rect;
		cachedItem.imageTransform = transform;
		cachedItem.imageRenderInfo = *renderInfo;
	}
}


} //namespace gincu
