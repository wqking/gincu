#include "gincu/gimage.h"
#include "gincu/grendercontext.h"
#include "gincu/gerrorhandler.h"
#include "gincu/gtransform.h"
#include "gincu/grenderinfo.h"

namespace gincu {

GImage::GImage()
	: texture(), rect()
{
}

GImage::GImage(const GTexture & texture)
	: texture(texture), rect()
{
}

GImage::GImage(const GTexture & texture, const GRect & rect)
	: texture(texture), rect(rect)
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
		const GSize size = this->texture.getSize();
		this->rect = createRect(GPoint(), size);
	}

	return this->rect;
}

GSize GImage::getSize() const
{
	const GRect tempRect = this->getRect();

	return { tempRect.width, tempRect.height };
}


} //namespace gincu
