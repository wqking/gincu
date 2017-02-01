#include "engine/gameimage.h"
#include "engine/renderengine.h"
#include "engine/errorhandler.h"
#include "engine/gametransform.h"
#include "engine/sfml/gameimageresource.h"

namespace gincu {

GameImage::GameImage()
	:
	resource()
{
}

GameImage::~GameImage()
{
}

void GameImage::load(const std::string & fileName)
{
	this->resource.reset(new GameImageResource());
	this->resource->load(fileName);
}

void GameImage::draw(const GameTransform & transform)
{
	RenderEngine::getInstance()->draw(*this, transform);
}

GameSize GameImage::getSize() const
{
	auto size = this->resource->texture.getSize();
	return { (CoordType)size.x, (CoordType)size.y };
}


} //namespace gincu
