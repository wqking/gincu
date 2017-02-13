#ifndef GATLASRENDER_H
#define GATLASRENDER_H

#include "gincu/gatlas.h"

namespace gincu {

class GImageData;

class GAtlasRender
{
public:
	GAtlasRender();
	explicit GAtlasRender(const GAtlas & atlas);

	void draw(const GTransform & transform, const GRenderInfo * renderInfo);

	GSize getSize() const;

	const GAtlas & getAtlas() const { return this->atlas; }
	int getIndex() const { return this->index; }
	void setIndex(const int index) { this->index = index; }

	const GRect & getRect() const { return this->atlas.getRectList()[this->index]; }

	const GImageData * getTexture() const { return this->atlas.getImageData().get(); }

private:
	GAtlas atlas;
	int index;
};


} //namespace gincu


#endif
