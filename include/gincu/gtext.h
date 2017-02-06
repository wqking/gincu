#ifndef GTEXT_H
#define GTEXT_H

#include "gincu/gcolor.h"
#include "gincu/ggeometry.h"
#include "gincu/grenderanchor.h"

#include <string>
#include <memory>

namespace gincu{

class GTransform;
struct GRenderInfo;
class GTextResource;
class GImageResource;

class GText
{
public:
	GText();
	explicit GText(const int fontSize);
	~GText();

	void setText(const std::string & text);
	void setColor(const GColor textColor);
	void setTextAndColor(const std::string & text, const GColor textColor);

	void draw(const GTransform & transform, const GRenderInfo * renderInfo);

	GSize getSize() const;

	const std::shared_ptr<GTextResource> & getResource() const { return this->resource; }

	const GImageResource * getTexture() const { return nullptr; }

private:
	std::shared_ptr<GTextResource> resource;
};


} //namespace gincu

#endif
