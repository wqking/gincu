#include "gincu/gresourcemanager.h"
#include "gincu/gspritesheet.h"
#include "gimagedata.h"
#include "gfontdata.h"

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
	auto it = this->imageDataMap.find(resourceName);
	if(it != this->imageDataMap.end()) {
		data = it->second;
	}
	else {
		data = std::make_shared<GImageData>();
		this->imageDataMap.insert(std::make_pair(resourceName, data));
		const std::string fileName = this->solveResourcePath(resourceName);
		data->load(fileName);
	}

	return GImage(data);
}

GSpriteSheet GResourceManager::getSpriteSheet(const std::string & resourceName, const GSpriteSheetFormat format) const
{
	std::shared_ptr<GSpriteSheetData> data;

	auto it = this->spriteSheetDataMap.find(resourceName);
	if(it != this->spriteSheetDataMap.end()) {
		data = it->second;
	}
	else {
		data = std::make_shared<GSpriteSheetData>();
		data->load(resourceName, format);
		this->spriteSheetDataMap.insert(std::make_pair(resourceName, data));
	}

	return GSpriteSheet(data);
}

GFileInputStream GResourceManager::getFileStream(const std::string & resourceName) const
{
	GFileInputStream stream;
	stream.open(this->solveResourcePath(resourceName));
	return stream;
}

GFont GResourceManager::getFont(const std::string & resourceName) const
{
	std::shared_ptr<GFontData> data;

	auto it = this->fontDataMap.find(resourceName);
	if(it != this->fontDataMap.end()) {
		data = it->second;
	}
	else {
		data = std::make_shared<GFontData>();
		this->fontDataMap.insert(std::make_pair(resourceName, data));
		data->font.loadFromFile(this->solveResourcePath(resourceName));
	}

	return GFont(data);
}

GFont GResourceManager::getFont() const
{
	return this->getFont(this->defaultFontName);
}

std::string GResourceManager::solveResourcePath(const std::string & resourceName) const
{
	return this->resourcePath + resourceName;
}


} //namespace gincu
