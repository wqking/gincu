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

#include <thread>

namespace gincu {


namespace {

void threadMain(GRenderEngine * renderEngine)
{
}

} //unnamed namespace

GRenderEngineData::GRenderEngineData()
	:
		window(),
		view(),
		updaterReady(false),
		renderReady(false),
		updaterQueue(nullptr),
		renderQueue(nullptr)
{
}

void GRenderEngine::doInitialize()
{
	this->data->window->setActive(false);

	this->data->updaterQueue = &this->data->queueStorage[0];
	this->data->renderQueue = &this->data->queueStorage[1];
}

void GRenderEngine::doFinalize()
{
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
}

void GRenderEngine::draw(const GRectRender & rect, const GTransform & transform, const GRenderInfo * renderInfo)
{
}

void GRenderEngine::beginBatchDraw()
{
}

void GRenderEngine::endBatchDraw()
{
}

void GRenderEngine::flush()
{
}

void GRenderEngine::doDrawTexture(const std::shared_ptr<GImageData> & texture, const GRect & rect, const GTransform & transform, const GRenderInfo * renderInfo)
{
	if(! texture) {
		return;
	}

}


} //namespace gincu
