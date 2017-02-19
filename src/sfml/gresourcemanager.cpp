#include "gincu/gresourcemanager.h"
#include "gincu/gapplication.h"
#include "gincu/geventqueue.h"
#include "gincu/gatlas.h"
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

void GResourceManager::initialize()
{
}

void GResourceManager::finalize()
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
		{
			LockType lock(this->imageMutex);
			data->load(fileName);
		}
	}

	return GImage(data);
}

GImage GResourceManager::asyncGetImage(const std::string & resourceName, const LoaderCallback & callback) const
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
		GApplication::getInstance()->executeWorkerTask(
			[=]() {
				{
					LockType lock(this->imageMutex);
					data->load(fileName);
				}
				if(! callback.empty()) {
					GApplication::getInstance()->getEventQueue()->post(GEvent(GEventType::execute, callback));
				}
			}
		);
	}

	return GImage(data);
}

GAtlas GResourceManager::getAtlas(const std::string & resourceName, const GAtlasFormat format) const
{
	std::shared_ptr<GAtlasData> data;

	auto it = this->atlasDataMap.find(resourceName);
	if(it != this->atlasDataMap.end()) {
		data = it->second;
	}
	else {
		data = std::make_shared<GAtlasData>();
		data->load(resourceName, format);
		this->atlasDataMap.insert(std::make_pair(resourceName, data));
	}

	return GAtlas(data);
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
		const std::string fileName = this->solveResourcePath(resourceName);
		{
			LockType lock(this->fontMutex);
			data->load(fileName);
		}
	}

	return GFont(data);
}

GFont GResourceManager::asyncGetFont(const std::string & resourceName, const LoaderCallback & callback) const
{
	std::shared_ptr<GFontData> data;

	auto it = this->fontDataMap.find(resourceName);
	if(it != this->fontDataMap.end()) {
		data = it->second;
	}
	else {
		data = std::make_shared<GFontData>();
		this->fontDataMap.insert(std::make_pair(resourceName, data));
		const std::string fileName = this->solveResourcePath(resourceName);
		GApplication::getInstance()->executeWorkerTask(
			[=]() {
				{
					LockType lock(this->fontMutex);
					data->load(fileName);
				}
				if(! callback.empty()) {
					GApplication::getInstance()->getEventQueue()->post(GEvent(GEventType::execute, callback));
				}
		}
		);
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

void GResourceManager::reloadResources()
{
	for(auto it = this->imageDataMap.begin(); it != this->imageDataMap.end(); ++it) {
		it->second->reload();
	}
}


} //namespace gincu
