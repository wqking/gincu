#ifndef GTEXTRENDER_H
#define GTEXTRENDER_H

#include "gincu/gcolor.h"
#include "gincu/ggeometry.h"
#include "gincu/gmatrix.h"

#include <string>
#include <memory>

namespace gincu{

class GTransform;
struct GRenderInfo;
class GTextRenderData;
class GImageData;
class GRenderContext;

class GTextRender
{
public:
	GTextRender();
	~GTextRender();

	void setText(const std::string & text);
	void setColor(const GColor textColor);
	void setFontSize(const int fontSize);

	void draw(GRenderContext * renderContext, const GMatrix44 & matrix, const GRenderInfo * renderInfo);

	GSize getSize() const;

	const std::shared_ptr<GTextRenderData> & getData() const { return this->data; }

private:
	void checkCopyOnWrite();

private:
	std::shared_ptr<GTextRenderData> data;
};


} //namespace gincu

#endif
