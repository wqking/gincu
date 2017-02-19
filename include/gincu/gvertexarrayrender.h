#ifndef GVERTEXARRAYRENDER_H
#define GVERTEXARRAYRENDER_H

#include "gincu/gvertexarray.h"
#include "gincu/gtexture.h"
#include "gincu/gprimitive.h"
#include "gincu/gmatrix.h"
#include "gincu/ggeometry.h"

namespace gincu {

enum class GPrimitive;
class GRenderContext;
struct GRenderInfo;

class GVertexArrayRender
{
public:
	GVertexArrayRender();
	GVertexArrayRender(const GPrimitive primitive, const GVertexArray & vertexArray);
	GVertexArrayRender(const GPrimitive primitive, const GVertexArray & vertexArray, const GTexture & texture);

	GPrimitive getPrimitive() const { return this->primitive; }
	void setPrimitive(const GPrimitive primitive) { this->primitive = primitive; }

	const GVertexArray & getVertexArray() const { return this->vertexArray; }
	void setVertexArray(const GVertexArray & vertexArray) { this->vertexArray = vertexArray; }

	const GTexture & getTexture() const { return this->texture; }
	void setTexture(const GTexture & texture) { this->texture = texture; }

private:
	GPrimitive primitive;
	GVertexArray vertexArray;
	GTexture texture;
};

void drawRender(const GVertexArrayRender & render, GRenderContext * renderContext, const GMatrix44 & matrix, const GRenderInfo * renderInfo);
GSize getRenderSize(const GVertexArrayRender & render);


} //namespace gincu


#endif
