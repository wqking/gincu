#include "engine/resourcemanager.h"
#include "engine/sfml/gameimageresource.h"
#include "engine/sfml/gamefontresource.h"

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
	if(it == this->imageResourceMap.end()) {
		std::shared_ptr<GameImageResource> imageResource(std::make_shared<GameImageResource>());
		this->imageResourceMap.insert(std::make_pair(resourceName, imageResource));
		const std::string fileName = "resources/" + resourceName;
		imageResource->load(fileName);
		resource = imageResource;
	}
	else {
		resource = it->second;
	}

	return GameImage(resource);
}

const GameFont & ResourceManager::getFont() const
{
	if(! this->font) {
		this->font.reset(new GameFont());
		this->font->getResource()->font.loadFromFile("resources/arialbd.ttf");
	}
	
	return *this->font.get();
}


} //namespace gincu
