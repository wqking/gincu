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

const GRect & GImage::getRect() const
{
	if(this->rect.width <= 0) {
		const GSize size = this->texture.getSize();
		this->rect = createRect(GPoint(), size);
	}

	return this->rect;
}

void drawRender(const GImage & render, GRenderContext * renderContext, const GMatrix44 & matrix, const GRenderInfo * renderInfo)
{
	renderContext->draw(render.getTexture(), render.getRect(), matrix, renderInfo);
}

GSize getRenderSize(const GImage & render)
{
	return getSize(render.getRect());
}


} //namespace gincu
