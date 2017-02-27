#include "gincu/gvertexarray.h"
#include "gincu/gdevicecontext.h"

namespace gincu {

GVertexArray::GVertexArray()
	: data(GDeviceContext::getInstance()->createVertexArrayData(nullptr))
{
}

GVertexArray::~GVertexArray()
{
}

int GVertexArray::getCount() const
{
	return this->data->getCount();
}

void GVertexArray::resize(const int size)
{
	this->checkCopyOnWrite();

	this->data->resize(size);
}

void GVertexArray::setAt(const int index, const GPoint & position, const GColor color, const GPoint & textureUv)
{
	this->checkCopyOnWrite();

	this->data->setAt(index, position,color, textureUv);
}

void GVertexArray::append(const GPoint & position, const GColor color, const GPoint & textureUv)
{
	this->checkCopyOnWrite();

	this->data->append(position, color, textureUv);
}

GPoint GVertexArray::getPositionAt(const int index)
{
	return this->data->getPositionAt(index);
}

GPoint GVertexArray::getTextureUvAt(const int index)
{
	return this->data->getTextureUvAt(index);
}

GColor GVertexArray::getColorAt(const int index)
{
	return this->data->getColorAt(index);
}

GColor GVertexArray::getColor() const
{
	return this->data->getColor();
}

void GVertexArray::setColor(const GColor color)
{
	this->checkCopyOnWrite();

	this->data->setColor(color);
}

GSize GVertexArray::getTextureSize() const
{
	return this->data->getTextureSize();
}

void GVertexArray::setTextureSize(const GSize & size)
{
	this->checkCopyOnWrite();
	
	this->data->setTextureSize(size);
}

GRect GVertexArray::getBoundingRect() const
{
	return this->data->getBoundingRect();
}

void GVertexArray::checkCopyOnWrite()
{
	if(this->data.use_count() != 1) {
		this->data = GDeviceContext::getInstance()->createVertexArrayData(this->data.get());
	}
}


} //namespace gincu


