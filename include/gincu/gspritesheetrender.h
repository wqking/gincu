#ifndef GSPRITESHEETRENDER_H
#define GSPRITESHEETRENDER_H

#include "gincu/gspritesheet.h"

namespace gincu {

class GImageResource;

class GSpriteSheetRender
{
public:
	GSpriteSheetRender();
	explicit GSpriteSheetRender(const GSpriteSheet & spriteSheet);

	void draw(const GTransform & transform, const GRenderInfo * renderInfo);

	GSize getSize() const;

	const GSpriteSheet & getSpriteSheet() const { return this->spriteSheet; }
	int getIndex() const { return this->index; }
	void setIndex(const int index) { this->index = index; }

	const GRect & getRect() const { return this->spriteSheet.getRectList()[this->index]; }

	const GImageResource * getTexture() const { return this->spriteSheet.getImageResource().get(); }

private:
	GSpriteSheet spriteSheet;
	int index;
};


} //namespace gincu


#endif
