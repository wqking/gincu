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
	GRenderEngineData();

	void clearBatchDrawState();

	void directDrawTexture(const std::shared_ptr<GImageData> & texture, const GRect & rect, const GTransform & transform, const GRenderInfo * renderInfo);
	void batchDrawTexture(const std::shared_ptr<GImageData> & texture, const GRect & rect, const GTransform & transform, const GRenderInfo * renderInfo);
	void beginBatchDraw();
	void endBatchDraw();
	void flush();

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
