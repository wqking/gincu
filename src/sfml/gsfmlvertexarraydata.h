#ifndef GSFMLVERTEXARRAYDATA_H
#define GSFMLVERTEXARRAYDATA_H

#include "gincu/gvertexarray.h"

#include <SFML/Graphics.hpp>

#include <vector>

namespace gincu {

class GSfmlVertexArrayData : public GVertexArrayData
{
public:
	GSfmlVertexArrayData() : textureSize(), boundingRect() {
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

		this->vertexArray[index] = sf::Vertex(
			gameVector2ToSfml(position),
			gameColorToSfml(color),
			gameVector2ToSfml(textureUV)
		);
	}
	
	virtual void append(const GPoint & position, const GColor color, const GPoint & textureUV) override {
		this->boundingRect.width = -1;

		this->vertexArray.push_back(sf::Vertex(
			gameVector2ToSfml(position),
			gameColorToSfml(color),
			gameVector2ToSfml(textureUV)
		));
	}
	
	virtual GColor getColor() const override {
		if(! this->vertexArray.empty()) {
			return sfmlColorToGame(this->vertexArray.front().color);
		}
		else {
			return GColor();
		}
	}
	
	virtual void setColor(const GColor color) override {
		auto sfmlColor = gameColorToSfml(color);
		for(auto & vertex : this->vertexArray) {
			vertex.color = sfmlColor;
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
			const auto & vertexList = this->vertexArray;
			if(! vertexList.empty()) {
				sf::Vector2f position = vertexList[0].position;
				GCoord left = position.x;
				GCoord top = position.y;
				GCoord right = position.x;
				GCoord bottom = position.y;

				for(std::size_t i = 1; i < vertexList.size(); ++i) {
					position = vertexList[i].position;
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

	std::vector<sf::Vertex> vertexArray;
	GSize textureSize;
	mutable GRect boundingRect;
};


} //namespace gincu



#endif
