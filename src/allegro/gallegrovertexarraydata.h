#ifndef GALLEGROVERTEXARRAYDATA_H
#define GALLEGROVERTEXARRAYDATA_H

#include "gincu/gvertexarray.h"

#include "allegro5/allegro_primitives.h"

#include <vector>

namespace gincu {

class GAllegroVertexArrayData : public GVertexArrayData
{
public:
	GAllegroVertexArrayData() : textureSize(), boundingRect() {
	}

	virtual int getCount() const override {
		return (int)this->vertexArray.size();
	}

	virtual void resize(const int size) override {
		this->boundingRect.width = -1;

		this->vertexArray.resize(size);
	}
	
	virtual void setAt(const int index, const GPoint & position, const GColor color, const GPoint & textureUV) override {
		this->boundingRect.width = -1;
		
		this->doPutVertex(index, position, color, textureUV);
	}
	
	virtual void append(const GPoint & position, const GColor color, const GPoint & textureUV) override {
		this->boundingRect.width = -1;

		const int index = (int)this->vertexArray.size();
		this->vertexArray.resize(index + 1);
		this->doPutVertex(index, position, color, textureUV);
	}
	
	virtual GColor getColor() const override {
		if(! this->vertexArray.empty()) {
			return allegroColorToGame(this->vertexArray.front().color);
		}
		else {
			return GColor();
		}
	}
	
	virtual void setColor(const GColor color) override {
		auto allegroColor = gameColorToAllegro(color);
		for(ALLEGRO_VERTEX & vertex : this->vertexArray) {
			vertex.color = allegroColor;
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
				GCoord left = this->vertexArray[0].x;
				GCoord top = this->vertexArray[0].y;
				GCoord right = left;
				GCoord bottom = right;

				for(std::size_t i = 1; i < this->vertexArray.size(); ++i) {
					const GPoint position = { this->vertexArray[i].x, this->vertexArray[i].y };
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
		ALLEGRO_VERTEX & vertex = this->vertexArray[index];
		vertex.x = position.x;
		vertex.y = position.y;
		vertex.color = gameColorToAllegro(color);
		vertex.u = textureUV.x;
		vertex.v = textureUV.y;

		return index;
	}
	
public:
	std::vector<ALLEGRO_VERTEX> vertexArray;
	GSize textureSize;
	mutable GRect boundingRect;

};


} //namespace gincu



#endif
