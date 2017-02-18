#ifndef GRECTRENDER_H
#define GRECTRENDER_H

#include "gincu/gcolor.h"
#include "gincu/ggeometry.h"
#include "gincu/gmatrix.h"

#include <memory>

namespace gincu {

class GTransform;
struct GRenderInfo;
class GRectRenderData;
class GImageData;
class GRenderContext;

class GRectRender
{
public:
	GRectRender();
	~GRectRender();

	void draw(GRenderContext * renderContext, const GMatrix44 & matrix, const GRenderInfo * renderInfo);

	void setColor(const GColor color);
	GColor getColor() const;

	void setSize(const GSize & size);
	GSize getSize() const;

	const std::shared_ptr<GRectRenderData> & getData() const { return this->data; }

private:
	std::shared_ptr<GRectRenderData> data;
};


} //namespace gincu

#endif
