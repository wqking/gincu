#ifndef GTEXTRENDER_H
#define GTEXTRENDER_H

#include "gincu/gcolor.h"
#include "gincu/ggeometry.h"
#include "gincu/grenderanchor.h"

#include <string>
#include <memory>

namespace gincu{

class GTransform;
struct GRenderInfo;
class GTextRenderData;
class GImageData;

class GTextRender
{
public:
	GTextRender();
	explicit GTextRender(const int fontSize);
	~GTextRender();

	void setText(const std::string & text);
	void setColor(const GColor textColor);
	void setTextAndColor(const std::string & text, const GColor textColor);

	void draw(const GTransform & transform, const GRenderInfo * renderInfo);

	GSize getSize() const;

	const std::shared_ptr<GTextRenderData> & getData() const { return this->data; }

	const GImageData * getTexture() const { return nullptr; }

private:
	std::shared_ptr<GTextRenderData> data;
};


} //namespace gincu

#endif
