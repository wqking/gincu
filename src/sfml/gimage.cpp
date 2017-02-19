#include "gincu/gimage.h"
#include "gincu/grendercontext.h"
#include "gincu/gerrorhandler.h"
#include "gincu/gtransform.h"
#include "gincu/grenderinfo.h"
#include "gimagedata.h"

namespace gincu {

GImage::GImage()
	: data(), rect()
{
}

GImage::GImage(const std::shared_ptr<GImageData> & data)
	: data(data), rect()
{
}

GImage::GImage(const std::shared_ptr<GImageData> & data, const GRect & rect)
	: data(data), rect(rect)
{
}

GImage::~GImage()
{
}

void GImage::draw(GRenderContext * renderContext, const GMatrix44 & matrix, const GRenderInfo * renderInfo)
{
	renderContext->draw(*this, matrix, renderInfo);
}

const GRect & GImage::getRect() const
{
	if(this->rect.width <= 0) {
		if(this->data) {
			auto size = this->data->texture.getSize();
			this->rect = GRect{ 0, 0, (GCoord)size.x, (GCoord)size.y };
		}
	}

	return this->rect;
}

GSize GImage::getSize() const
{
	const GRect tempRect = this->getRect();

	return { tempRect.width, tempRect.height };
}

void GImage::doSetData(const std::shared_ptr<GImageData> & data)
{
	this->data = data;
	if(this->data) {
		auto size = this->data->texture.getSize();
		this->rect = GRect{ 0, 0, (GCoord)size.x, (GCoord)size.y };
	}
}


} //namespace gincu
