#ifndef GIMAGE_H
#define GIMAGE_H

#include "gincu/ggeometry.h"
#include "gincu/gmatrix.h"
#include "gincu/gtexture.h"

#include <string>
#include <memory>

namespace gincu {

class GTransform;
struct GRenderInfo;
class GTextureData;
class GRenderContext;

class GImage
{
public:
	GImage();
	~GImage();
	explicit GImage(const GTexture & texture);
	GImage(const GTexture & texture, const GRect & rect);

	void draw(GRenderContext * renderContext, const GMatrix44 & matrix, const GRenderInfo * renderInfo);

	GSize getSize() const;

	const GTexture & getTexture() const { return this->texture; }

	void setRect(const GRect & rect) { this->rect = rect; }
	const GRect & getRect() const;

	bool isValid() const { return this->texture.isValid(); }

private:
	GTexture texture;
	mutable GRect rect;
};


} //namespace gincu

#endif
