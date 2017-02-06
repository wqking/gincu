#ifndef GIMAGE_H
#define GIMAGE_H

#include "gincu/ggeometry.h"
#include "gincu/grenderanchor.h"

#include <string>
#include <memory>

namespace gincu {

class GTransform;
struct GRenderInfo;
class GImageResource;

class GImage
{
public:
	GImage();
	~GImage();
	explicit GImage(const std::shared_ptr<GImageResource> & resource);
	GImage(const std::shared_ptr<GImageResource> & resource, const GRect & rect);

	void load(const std::string & fileName);

	void draw(const GTransform & transform, const GRenderInfo * renderInfo);

	GSize getSize() const;

	void setResource(const std::shared_ptr<GImageResource> & resource);
	const std::shared_ptr<GImageResource> & getResource() const { return this->resource; }

	void setRect(const GRect & rect) { this->rect = rect; }
	const GRect & getRect() const { return this->rect; }

	bool isValid() const { return this->resource.get() != nullptr; }

	const GImageResource * getTexture() const { return this->resource.get(); }

private:
	std::shared_ptr<GImageResource> resource;
	GRect rect;
};


} //namespace gincu

#endif
