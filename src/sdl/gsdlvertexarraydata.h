#ifndef GSDLVERTEXARRAYDATA_H
#define GSDLVERTEXARRAYDATA_H

#include "gincu/gvertexarray.h"

#include <vector>

namespace gincu {

class GSdlVertexArrayData : public GVertexArrayData
{
public:
	virtual int getCount() const override {
		return (int)this->vertexArray.size();
	}

	virtual void resize(const int size) override {
		this->boundingRect.width = -1;

		this->vertexArray.resize(size);
	}
	
	virtual void setAt(const int index, const GPoint & position, const GColor color, const GPoint & textureUV) override {
		this->boundingRect.width = -1;
	}
	
	virtual void append(const GPoint & position, const GColor color, const GPoint & textureUV) override {
		this->boundingRect.width = -1;

	}
	
	virtual GColor getColor() const override {
		if(! this->vertexArray.empty()) {
			return 0;
		}
		else {
			return GColor();
		}
	}
	
	virtual void setColor(const GColor color) override {
		for(auto & vertex : this->vertexArray) {
		}
	}
	
	virtual GRect getBoundingRect() const override {
		if(this->boundingRect.width <= 0) {
			const auto & vertexList = this->vertexArray;
			if(! vertexList.empty()) {
			}
			else {
				this->boundingRect = GRect();
			}
		}
		return this->boundingRect;
	}

	std::vector<int> vertexArray;
	mutable GRect boundingRect;
};


} //namespace gincu



#endif
