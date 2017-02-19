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

	void draw(GRenderContext * renderContext, const GMatrix44 & matrix, const GRenderInfo * renderInfo);

	GSize getSize() const;

	const std::shared_ptr<GImageData> & getData() const { return this->data; }

	void setRect(const GRect & rect) { this->rect = rect; }
	const GRect & getRect() const;

	bool isValid() const { return this->data.get() != nullptr; }

private:
	void doSetData(const std::shared_ptr<GImageData> & data);

private:
	std::shared_ptr<GImageData> data;
	mutable GRect rect;
};


} //namespace gincu

#endif
