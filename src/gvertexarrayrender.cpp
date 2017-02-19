#include "gincu/gvertexarrayrender.h"
#include "gincu/grendercontext.h"

namespace gincu {

GVertexArrayRender::GVertexArrayRender()
	: primitive(), vertexArray(), texture()
{
}

GVertexArrayRender::GVertexArrayRender(const GPrimitive primitive, const GVertexArray & vertexArray)
	: primitive(primitive), vertexArray(vertexArray), texture()
{
}

GVertexArrayRender::GVertexArrayRender(const GPrimitive primitive, const GVertexArray & vertexArray, const GTexture & texture)
	: primitive(primitive), vertexArray(vertexArray), texture(texture)
{
}


void drawRender(const GVertexArrayRender & render, GRenderContext * renderContext, const GMatrix44 & matrix, const GRenderInfo * renderInfo)
{
	renderContext->draw(render.getVertexArray(), render.getPrimitive(), render.getTexture(), matrix, renderInfo);
}

GSize getRenderSize(const GVertexArrayRender & render)
{
	return getSize(render.getVertexArray().getBoundingRect());
}



} //namespace gincu

