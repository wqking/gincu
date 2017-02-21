#ifndef GVERTEXARRAY_H
#define GVERTEXARRAY_H

#include "gincu/gcolor.h"
#include "gincu/ggeometry.h"

#include <memory>

namespace gincu {

class GVertexArrayData;

class GVertexArray
{
public:
	static constexpr GColor defaultColor = colorWhite;

public:
	GVertexArray();
	~GVertexArray();

	int getCount() const;
	void resize(const int size);
	void setAt(const int index, const GPoint & position, const GColor color = defaultColor, const GPoint & textureUV = GPoint());
	void append(const GPoint & position, const GColor color = defaultColor, const GPoint & textureUV = GPoint());
	
	GColor getColor() const;
	void setColor(const GColor color);
	
	const GRect & getBoundingRect() const;

	const std::shared_ptr<GVertexArrayData> & getData() const { return this->data; }

private:
	std::shared_ptr<GVertexArrayData> data;
	mutable GRect boundingRect;
};


} //namespace gincu


#endif

