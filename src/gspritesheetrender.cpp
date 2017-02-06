#include "gincu/gspritesheetrender.h"
#include "gincu/grenderengine.h"

namespace gincu {

GSpriteSheetRender::GSpriteSheetRender()
	: spriteSheet(), index(0)
{
}

GSpriteSheetRender::GSpriteSheetRender(const GSpriteSheet & spriteSheet)
	: spriteSheet(spriteSheet), index(0)
{
}

void GSpriteSheetRender::draw(const GTransform & transform, const GRenderInfo * renderInfo)
{
	if(this->index >= 0 && this->index < this->spriteSheet.getImageCount()) {
		GRenderEngine::getInstance()->draw(*this, transform, renderInfo);
	}
}

GSize GSpriteSheetRender::getSize() const
{
	const GRect & rect = this->getRect();
	return { rect.width, rect.height };
}


} //namespace gincu
