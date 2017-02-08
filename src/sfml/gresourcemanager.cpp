#include "gincu/gresourcemanager.h"
#include "gincu/gspritesheet.h"
#include "gincu/sfml/gimagedata.h"
#include "gincu/sfml/gfontdata.h"

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
	std::shared_ptr<GImageData> data;
	auto it = this->imageResourceMap.find(resourceName);
	if(it != this->imageResourceMap.end()) {
		data = it->second;
	}
	else {
		data = std::make_shared<GImageData>();
		this->imageResourceMap.insert(std::make_pair(resourceName, data));
		const std::string fileName = this->solveResourcePath(resourceName);
		data->load(fileName);
	}

	return GImage(data);
}

GSpriteSheet GResourceManager::getSpriteSheet(const std::string & resourceName, const GSpriteSheetFormat format) const
{
	std::shared_ptr<GSpriteSheetData> data;

	auto it = this->spriteSheetResourceMap.find(resourceName);
	if(it != this->spriteSheetResourceMap.end()) {
		data = it->second;
	}
	else {
		data = std::make_shared<GSpriteSheetData>();
		data->load(resourceName, format);
		this->spriteSheetResourceMap.insert(std::make_pair(resourceName, data));
	}

	return GSpriteSheet(data);
}

GFileInputStream GResourceManager::getFileStream(const std::string & resourceName) const
{
	GFileInputStream stream;
	stream.open(this->solveResourcePath(resourceName));
	return stream;
}

GFont GResourceManager::getFont() const
{
	if(! this->font) {
		this->font.reset(new GFont());
		this->font->getData()->font.loadFromFile(this->solveResourcePath("arialbd.ttf"));
	}
	
	return *this->font.get();
}

std::string GResourceManager::solveResourcePath(const std::string & resourceName) const
{
	return this->resourcePath + resourceName;
}


} //namespace gincu
