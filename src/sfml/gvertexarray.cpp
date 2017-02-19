#include "gincu/gvertexarray.h"
#include "gvertexarraydata.h"
#include "gsfmlutil.h"

namespace gincu {

GVertexArray::GVertexArray()
	: data(std::make_shared<GVertexArrayData>())
{
}

GVertexArray::~GVertexArray()
{
}

int GVertexArray::getCount() const
{
	return (int)this->data->vertexArray.size();
}

void GVertexArray::resize(const int size)
{
	this->boundingRect.width = -1;

	this->data->vertexArray.resize(size);
}

void GVertexArray::setAt(const int index, const GPoint & position, const GColor color, const GPoint & textureUV)
{
	this->boundingRect.width = -1;

	this->data->vertexArray[index] = sf::Vertex(
		gameVector2ToSfml(position),
		gameColorToSfml(color),
		gameVector2ToSfml(textureUV)
	);
}

void GVertexArray::append(const GPoint & position, const GColor color, const GPoint & textureUV)
{
	this->boundingRect.width = -1;

	this->data->vertexArray.push_back(sf::Vertex(
		gameVector2ToSfml(position),
		gameColorToSfml(color),
		gameVector2ToSfml(textureUV)
	));
}

const GRect & GVertexArray::getBoundingRect() const
{
	if(this->boundingRect.width <= 0) {
		const auto & vertexList = this->data->vertexArray;
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


} //namespace gincu


