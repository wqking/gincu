#ifndef GRENDERENGINEDATA_H
#define GRENDERENGINEDATA_H

#include "gincu/grenderinfo.h"
#include "gincu/gtransform.h"

#include <SFML/Graphics.hpp>

#include <memory>

namespace gincu {

enum class GCachedRenderType
{
	none,
	texture
};

struct GCachedRenderItem
{
	GCachedRenderItem() : type(GCachedRenderType::none), imageData() {}

	void reset() {
		this->type = GCachedRenderType::none;
		this->imageData.reset();
	}

	GCachedRenderType type;
	std::shared_ptr<GImageData> imageData;
	GRect imageRect;
	GTransform imageTransform;
	GRenderInfo imageRenderInfo;
};

class GRenderEngineData
{
public:
	GRenderEngineData() :
		window(),
		view(),
		batchDrawVertexArray(sf::Triangles),
		batchDrawRenderInfo(),
		inBatchDraw(false)
	{}

	void clearBatchDrawState() {
		this->batchDrawVertexArray.clear();
		this->batchDrawRenderInfo.texture = nullptr;
		this->batchDrawImageData.reset();
		this->inBatchDraw = false;
	}

	std::unique_ptr<sf::RenderWindow> window;
	sf::View view;

	sf::VertexArray batchDrawVertexArray;
	GRenderInfo batchDrawRenderInfo;
	std::shared_ptr<GImageData> batchDrawImageData;
	bool inBatchDraw;

	GCachedRenderItem cachedRenderItem;
};


} //namespace gincu



#endif
