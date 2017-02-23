#ifndef GVERTEXARRAY_H
#define GVERTEXARRAY_H

#include "gincu/gcolor.h"
#include "gincu/ggeometry.h"

#include <memory>

namespace gincu {

class GVertexArrayData
{
public:
	virtual ~GVertexArrayData() {}

	virtual int getCount() const = 0;
	virtual void resize(const int size) = 0;
	virtual void setAt(const int index, const GPoint & position, const GColor color, const GPoint & textureUV) = 0;
	virtual void append(const GPoint & position, const GColor color, const GPoint & textureUV) = 0;
	
	virtual GColor getColor() const = 0;
	virtual void setColor(const GColor color) = 0;
	
	virtual GSize getTextureSize() const = 0;
	virtual void setTextureSize(const GSize & size) = 0;
	
	virtual GRect getBoundingRect() const = 0;
};

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
	
	GSize getTextureSize() const;
	void setTextureSize(const GSize & size);

	GRect getBoundingRect() const;

	const std::shared_ptr<GVertexArrayData> & getData() const { return this->data; }

private:
	void checkCopyOnWrite();

private:
	std::shared_ptr<GVertexArrayData> data;
};


} //namespace gincu


#endif

