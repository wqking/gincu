#include "gincu/gimage.h"
#include "gincu/grendercontext.h"
#include "gincu/gerrorhandler.h"
#include "gincu/gtransform.h"
#include "gincu/grenderinfo.h"
#include "gimagedata.h"

namespace gincu {

GImage::GImage()
	: data()
{
}

GImage::GImage(const std::shared_ptr<GImageData> & data)
{
	this->setResource(data);
}

GImage::GImage(const std::shared_ptr<GImageData> & data, const GRect & rect)
	: data(data), rect(rect)
{
}

GImage::~GImage()
{
}

void GImage::load(const std::string & fileName)
{
	this->data.reset(new GImageData());
	this->data->load(fileName);
}

void GImage::draw(GRenderContext * renderContext, const GMatrix44 & matrix, const GRenderInfo * renderInfo)
{
	renderContext->draw(*this, matrix, renderInfo);
}

GSize GImage::getSize() const
{
	return { this->rect.width, this->rect.height };
}

void GImage::setResource(const std::shared_ptr<GImageData> & data)
{
	this->data = data;
	if(this->data) {
		auto size = this->data->texture.getSize();
		this->rect = GRect{ 0, 0, (GCoord)size.x, (GCoord)size.y };
	}
}


} //namespace gincu
