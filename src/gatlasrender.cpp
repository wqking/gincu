#include "gincu/gatlasrender.h"
#include "gincu/grenderengine.h"

namespace gincu {

GAtlasRender::GAtlasRender()
	: atlas(), index(0)
{
}

GAtlasRender::GAtlasRender(const GAtlas & atlas)
	: atlas(atlas), index(0)
{
}

void GAtlasRender::draw(const GMatrix44 & matrix, const GRenderInfo * renderInfo)
{
	if(this->index >= 0 && this->index < this->atlas.getImageCount()) {
		GRenderEngine::getInstance()->draw(*this, matrix, renderInfo);
	}
}

GSize GAtlasRender::getSize() const
{
	const GRect & rect = this->getRect();
	return { rect.width, rect.height };
}


} //namespace gincu
