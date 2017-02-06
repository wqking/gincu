#include "gincu/gimage.h"
#include "gincu/grenderengine.h"
#include "gincu/gerrorhandler.h"
#include "gincu/gtransform.h"
#include "gincu/grenderinfo.h"
#include "gincu/sfml/gimageresource.h"

namespace gincu {

GImage::GImage()
	: resource()
{
}

GImage::GImage(const std::shared_ptr<GImageResource> & resource)
{
	this->setResource(resource);
}

GImage::GImage(const std::shared_ptr<GImageResource> & resource, const GRect & rect)
	: resource(resource), rect(rect)
{
}

GImage::~GImage()
{
}

void GImage::load(const std::string & fileName)
{
	this->resource.reset(new GImageResource());
	this->resource->load(fileName);
}

void GImage::draw(const GTransform & transform, const GRenderInfo * renderInfo)
{
	GRenderEngine::getInstance()->draw(*this, transform, renderInfo);
}

GSize GImage::getSize() const
{
	return { this->rect.width, this->rect.height };
}

void GImage::setResource(const std::shared_ptr<GImageResource> & resource)
{
	this->resource = resource;
	if(this->resource) {
		auto size = this->resource->texture.getSize();
		this->rect = GRect{ 0, 0, (GCoord)size.x, (GCoord)size.y };
	}
}


} //namespace gincu
