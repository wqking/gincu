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
		std::shared_ptr<GameImageResource> imageResource(std::make_shared<GameImageResource>());
		this->imageResourceMap.insert(std::make_pair(resourceName, imageResource));
		const std::string fileName = this->resourcePath + resourceName;
		imageResource->load(fileName);
		resource = imageResource;
	}

	return GameImage(resource);
}

std::shared_ptr<GameSpriteSheet> ResourceManager::getSpriteSheet(const std::string & resourceName, const SpriteSheetFormat format) const
{
	auto it = this->spriteSheetMap.find(resourceName);
	if(it != this->spriteSheetMap.end()) {
		return it->second;
	}
	else {
		std::shared_ptr<GameSpriteSheet> spriteSheet(std::make_shared<GameSpriteSheet>());
		spriteSheet->load(resourceName, format);
		this->spriteSheetMap.insert(std::make_pair(resourceName, spriteSheet));
		return spriteSheet;
	}
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
