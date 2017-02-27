#include "gincu/gtextrender.h"
#include "gincu/grendercontext.h"
#include "gincu/gerrorhandler.h"
#include "gincu/gresourcemanager.h"
#include "gincu/gtransform.h"
#include "gincu/gdevicecontext.h"

namespace gincu {

GTextRender::GTextRender()
	:
		data(GDeviceContext::getInstance()->createTextRenderData(nullptr))
{
}

GTextRender::~GTextRender()
{
}

void GTextRender::setText(const std::string & text)
{
	this->checkCopyOnWrite();

	this->data->setText(text);
}

void GTextRender::setFontSize(const int fontSize)
{
	this->checkCopyOnWrite();

	this->data->setFontSize(fontSize);
}

void GTextRender::checkCopyOnWrite()
{
	// if use_count > 1 means the data is used by render engine, so we can't modify it because multi thread conflict,
	// thus we have to duplicate it.
	if(this->data.use_count() != 1) {
		this->data = GDeviceContext::getInstance()->createTextRenderData(this->data.get());
	}
}

void drawRender(const GTextRender & render, GRenderContext * renderContext, const GMatrix44 & matrix, const GRenderInfo * renderInfo)
{
	renderContext->draw(render, matrix, renderInfo);
}

GSize getRenderSize(const GTextRender & render)
{
	return render.getData()->getBoundingSize();
}


} //namespace gincu
