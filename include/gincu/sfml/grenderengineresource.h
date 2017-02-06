#ifndef GRENDERENGINERESOURCE_H
#define GRENDERENGINERESOURCE_H

#include "gincu/grenderinfo.h"

#include <SFML/Graphics.hpp>

#include <memory>

namespace gincu {

class GRenderEngineResource
{
public:
	GRenderEngineResource() :
		window(),
		view(),
		batchDrawVertexArray(sf::Triangles),
		batchDrawRenderInfo(),
		inBatchDraw(false)
	{}

	void clearBatchDrawState() {
		this->batchDrawVertexArray.clear();
		this->batchDrawRenderInfo.texture = nullptr;
		this->inBatchDraw = false;
	}

	std::unique_ptr<sf::RenderWindow> window;
	sf::View view;

	sf::VertexArray batchDrawVertexArray;
	GRenderInfo batchDrawRenderInfo;
	bool inBatchDraw;
};


} //namespace gincu



#endif
