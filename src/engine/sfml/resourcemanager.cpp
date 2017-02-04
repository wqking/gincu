#include "engine/resourcemanager.h"
#include "engine/sfml/gameimageresource.h"
#include "engine/sfml/gamefontresource.h"
#include "engine/gamespritesheet.h"

#include <cassert>

namespace gincu {

namespace {

ResourceManager * instance = nullptr;

} //unnamed namespace

ResourceManager * ResourceManager::getInstance()
{
	return instance;
}

ResourceManager::ResourceManager()
	: resourcePath("resources/")
{
	assert(instance == nullptr);

	instance = this;
}

ResourceManager::~ResourceManager()
{
}

GameImage ResourceManager::getImage(const std::string & resourceName) const
{
	std::shared_ptr<GameImageResource> resource;
	auto it = this->imageResourceMap.find(resourceName);
	if(it != this->imageResourceMap.end()) {
		resource = it->second;
	}
	else {
		resource = std::make_shared<GameImageResource>();
		this->imageResourceMap.insert(std::make_pair(resourceName, resource));
		const std::string fileName = this->resourcePath + resourceName;
		resource->load(fileName);
	}

	return GameImage(resource);
}

GameSpriteSheet ResourceManager::getSpriteSheet(const std::string & resourceName, const SpriteSheetFormat format) const
{
	std::shared_ptr<GameSpriteSheetResource> resource;

	auto it = this->spriteSheetResourceMap.find(resourceName);
	if(it != this->spriteSheetResourceMap.end()) {
		resource = it->second;
	}
	else {
		resource = std::make_shared<GameSpriteSheetResource>();
		resource->load(resourceName, format);
		this->spriteSheetResourceMap.insert(std::make_pair(resourceName, resource));
	}

	return GameSpriteSheet(resource);
}

FileInputStream ResourceManager::getFileStream(const std::string & resourceName) const
{
	FileInputStream stream;
	stream.open(this->resourcePath + resourceName);
	return stream;
}

const GameFont & ResourceManager::getFont() const
{
	if(! this->font) {
		this->font.reset(new GameFont());
		this->font->getResource()->font.loadFromFile(this->resourcePath + "arialbd.ttf");
	}
	
	return *this->font.get();
}


} //namespace gincu
