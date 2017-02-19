#ifndef GATLASRENDER_H
#define GATLASRENDER_H

#include "gincu/gatlas.h"
#include "gincu/gmatrix.h"

namespace gincu {

class GTexture;
class GRenderContext;

class GAtlasRender
{
public:
	GAtlasRender();
	explicit GAtlasRender(const GAtlas & atlas);

	const GAtlas & getAtlas() const { return this->atlas; }
	int getIndex() const { return this->index; }
	void setIndex(const int index) { this->index = index; }
	int getImageCount() const { return this->atlas.getImageCount(); }

	const GRect & getRect() const { return this->atlas.getRectList()[this->index]; }

	const GTexture & getTexture() const { return this->atlas.getTexture(); }

private:
	GAtlas atlas;
	int index;
};

void drawRender(const GAtlasRender & render, GRenderContext * renderContext, const GMatrix44 & matrix, const GRenderInfo * renderInfo);
GSize getRenderSize(const GAtlasRender & render);


} //namespace gincu


#endif
