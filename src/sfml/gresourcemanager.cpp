#include "gincu/gresourcemanager.h"
#include "gincu/gspritesheet.h"
#include "gincu/sfml/gimageresource.h"
#include "gincu/sfml/gfontresource.h"

#include <cassert>

namespace gincu {

namespace {

GResourceManager * instance = nullptr;

} //unnamed namespace

GResourceManager * GResourceManager::getInstance()
{
	return instance;
}

GResourceManager::GResourceManager()
	: resourcePath("resources/")
{
	assert(instance == nullptr);

	instance = this;
}

GResourceManager::~GResourceManager()
{
}

GImage GResourceManager::getImage(const std::string & resourceName) const
{
	std::shared_ptr<GImageResource> resource;
	auto it = this->imageResourceMap.find(resourceName);
	if(it != this->imageResourceMap.end()) {
		resource = it->second;
	}
	else {
		resource = std::make_shared<GImageResource>();
		this->imageResourceMap.insert(std::make_pair(resourceName, resource));
		const std::string fileName = this->resourcePath + resourceName;
		resource->load(fileName);
	}

	return GImage(resource);
}

GSpriteSheet GResourceManager::getSpriteSheet(const std::string & resourceName, const GSpriteSheetFormat format) const
{
	std::shared_ptr<GSpriteSheetResource> resource;

	auto it = this->spriteSheetResourceMap.find(resourceName);
	if(it != this->spriteSheetResourceMap.end()) {
		resource = it->second;
	}
	else {
		resource = std::make_shared<GSpriteSheetResource>();
		resource->load(resourceName, format);
		this->spriteSheetResourceMap.insert(std::make_pair(resourceName, resource));
	}

	return GSpriteSheet(resource);
}

GFileInputStream GResourceManager::getFileStream(const std::string & resourceName) const
{
	GFileInputStream stream;
	stream.open(this->resourcePath + resourceName);
	return stream;
}

const GFont & GResourceManager::getFont() const
{
	if(! this->font) {
		this->font.reset(new GFont());
		this->font->getResource()->font.loadFromFile(this->resourcePath + "arialbd.ttf");
	}
	
	return *this->font.get();
}


} //namespace gincu
