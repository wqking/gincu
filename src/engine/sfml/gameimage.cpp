#include "engine/gameimage.h"
#include "engine/renderengine.h"
#include "engine/errorhandler.h"
#include "engine/gametransform.h"
#include "engine/sfml/gameimageresource.h"

namespace gincu {

GameImage::GameImage()
	: resource()
{
}

GameImage::GameImage(const std::shared_ptr<GameImageResource> & resource)
{
	this->setResource(resource);
}

GameImage::GameImage(const std::shared_ptr<GameImageResource> & resource, const GameRect & rect)
	: resource(resource), rect(rect)
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
	return { this->rect.width, this->rect.height };
}

void GameImage::setResource(const std::shared_ptr<GameImageResource> & resource)
{
	this->resource = resource;
	if(this->resource) {
		auto size = this->resource->texture.getSize();
		this->rect = GameRect{ 0, 0, (CoordType)size.x, (CoordType)size.y };
	}
}


} //namespace gincu
