#ifndef GSDLVERTEXARRAYDATA_H
#define GSDLVERTEXARRAYDATA_H

#include "gincu/gvertexarray.h"

#include <vector>

namespace gincu {

class GSdlVertexArrayData : public GVertexArrayData
{
private:
	static constexpr int sizePerVertex = 8;

public:
	GSdlVertexArrayData() : textureSize(), boundingRect() {
	}

	virtual int getCount() const override {
		return (int)this->vertexArray.size() / sizePerVertex;
	}

	virtual void resize(const int size) override {
		this->boundingRect.width = -1;

		this->vertexArray.resize(size * sizePerVertex);
	}
	
	virtual void setAt(const int index, const GPoint & position, const GColor color, const GPoint & textureUV) override {
		this->boundingRect.width = -1;
		
		this->doPutVertex(index, position, color, textureUV);
	}
	
	virtual void append(const GPoint & position, const GColor color, const GPoint & textureUV) override {
		this->boundingRect.width = -1;

		const int index = (int)this->vertexArray.size();
		this->vertexArray.resize(index + sizePerVertex);
		this->doPutVertex(index, position, color, textureUV);
	}
	
	virtual GColor getColor() const override {
		if(this->vertexArray.size() >= sizePerVertex) {
			return this->doGetColor(4);
		}
		else {
			return GColor();
		}
	}
	
	virtual void setColor(const GColor color) override {
		for(std::size_t i = 4; i < this->vertexArray.size(); i += sizePerVertex) {
			this->doSetColor(i, color);
		}
	}
	
	virtual GSize getTextureSize() const {
		return this->textureSize;
	}
	
	virtual void setTextureSize(const GSize & size) {
		this->textureSize = size;
	}

	virtual GRect getBoundingRect() const override {
		if(this->boundingRect.width <= 0) {
			if(! this->vertexArray.empty()) {
				GCoord left = this->vertexArray[0];
				GCoord top = this->vertexArray[1];
				GCoord right = left;
				GCoord bottom = right;

				for(std::size_t i = sizePerVertex; i < this->vertexArray.size(); i += sizePerVertex) {
					const GPoint position = { this->vertexArray[i + 0], this->vertexArray[i + 1] };
					if(position.x < left) {
						left = position.x;
					}
					else if(position.x > right) {
						right = position.x;
					}

					if(position.y < top) {
						top = position.y;
					}
					else if(position.y > bottom) {
						bottom = position.y;
					}

					this->boundingRect = { left, top, right - left, bottom - top };
				}
			}
			else {
				this->boundingRect = GRect();
			}
		}
		return this->boundingRect;
	}

private:
	int doPutVertex(int index, const GPoint & position, const GColor color, const GPoint & textureUV)
	{
		const float textureWidth = std::max(1.0f, this->textureSize.width);
		const float textureHeight = std::max(1.0f, this->textureSize.height);

		const float textureLeft = textureUV.x / textureWidth;
		const float textureTop = textureUV.y / textureHeight;

		this->vertexArray[index++] = position.x;
		this->vertexArray[index++] = position.y;
		this->vertexArray[index++] = textureLeft;
		this->vertexArray[index++] = textureTop;
		index = this->doSetColor(index, color);
		
		return index;
	}
	
	int doSetColor(int index, const GColor color)
	{
		this->vertexArray[index++] = (float)colorGetRed(color) / 255.0f;
		this->vertexArray[index++] = (float)colorGetGreen(color) / 255.0f;
		this->vertexArray[index++] = (float)colorGetBlue(color) / 255.0f;
		this->vertexArray[index++] = (float)colorGetAlpha(color) / 255.0f;

		return index;
	}

	GColor doGetColor(const int index) const
	{
		return colorMakeARGB(
			(int)(this->vertexArray[index + 3] * 255.0f),
			(int)(this->vertexArray[index + 0] * 255.0f),
			(int)(this->vertexArray[index + 1] * 255.0f),
			(int)(this->vertexArray[index + 2] * 255.0f)
		);
	}

public:
	std::vector<float> vertexArray;
	GSize textureSize;
	mutable GRect boundingRect;

};


} //namespace gincu



#endif
