#ifndef GIMAGE_H
#define GIMAGE_H

#include "gincu/ggeometry.h"
#include "gincu/gmatrix.h"

#include <string>
#include <memory>

namespace gincu {

class GTransform;
struct GRenderInfo;
class GImageData;
class GRenderContext;

class GImage
{
public:
	GImage();
	~GImage();
	explicit GImage(const std::shared_ptr<GImageData> & data);
	GImage(const std::shared_ptr<GImageData> & data, const GRect & rect);

	void load(const std::string & fileName);

	void draw(GRenderContext * renderContext, const GMatrix44 & matrix, const GRenderInfo * renderInfo);

	GSize getSize() const;

	void setResource(const std::shared_ptr<GImageData> & data);
	const std::shared_ptr<GImageData> & getData() const { return this->data; }

	void setRect(const GRect & rect) { this->rect = rect; }
	const GRect & getRect() const { return this->rect; }

	bool isValid() const { return this->data.get() != nullptr; }

private:
	std::shared_ptr<GImageData> data;
	GRect rect;
};


} //namespace gincu

#endif
