#ifndef RENDERENGINERESOURCE_H
#define RENDERENGINERESOURCE_H

#include <SFML/Graphics.hpp>

#include <memory>

namespace gincu {

class RenderEngineResource
{
public:
	RenderEngineResource() :
		window(),
		view(),
		batchDrawVertexArray(sf::Triangles),
		batchDrawTexture(nullptr),
		inBatchDraw(false)
	{}

	void clearBatchDrawState() {
		this->batchDrawVertexArray.clear();
		this->batchDrawTexture = nullptr;
		this->inBatchDraw = false;
	}

	std::unique_ptr<sf::RenderWindow> window;
	sf::View view;

	sf::VertexArray batchDrawVertexArray;
	sf::Texture * batchDrawTexture;
	bool inBatchDraw;
};


} //namespace gincu



#endif
