#include "gincu/gatlasrender.h"
#include "gincu/grendercontext.h"

namespace gincu {

GAtlasRender::GAtlasRender()
	: atlas(), index(0)
{
}

GAtlasRender::GAtlasRender(const GAtlas & atlas)
	: atlas(atlas), index(0)
{
}

void drawRender(const GAtlasRender & render, GRenderContext * renderContext, const GMatrix44 & matrix, const GRenderInfo * renderInfo)
{
	const int index = render.getIndex();
	if(index >= 0 && index < render.getImageCount()) {
		renderContext->draw(render.getTexture(), render.getRect(),  matrix, renderInfo);
	}
}

GSize getRenderSize(const GAtlasRender & render)
{
	return getSize(render.getRect());
}


} //namespace gincu
