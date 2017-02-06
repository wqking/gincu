#include "gincu/gspritesheet.h"
#include "gincu/gerrorhandler.h"
#include "gincu/gresourcemanager.h"
#include "gincu/ginputstream.h"
#include "gincu/gapplication.h"
#include "cpgf/goutmain.h"

#include <cstring>

namespace gincu {

GImage GSpriteSheetResource::getImage(const std::string & name) const
{
	auto it = this->indexMap.find(const_cast<std::string &>(name));
	if(it != this->indexMap.end()) {
		return GImage(this->imageResource, this->rectList[it->second]);
	}
	else {
		return GImage();
	}
}

int GSpriteSheetResource::getIndex(const std::string & name) const
{
	auto it = this->indexMap.find(const_cast<std::string &>(name));
	if(it != this->indexMap.end()) {
		return it->second;
	}
	else {
		return -1;
	}
}

void GSpriteSheetResource::load(const std::string & resourceName, const GSpriteSheetFormat format)
{
	const GSpriteSheet::LoaderMap * loaderMap = GSpriteSheet::getLoaderMap();
	auto it = loaderMap->find(format);
	if(it == loaderMap->end()) {
		handleFatal("Can't find sprite sheet loader.");
		return;
	}

	it->second(resourceName,this);

	this->imageResource = GResourceManager::getInstance()->getImage(this->imageName).getResource();

	for(std::size_t i = 0; i < this->nameList.size(); ++i) {
		this->indexMap.insert(std::make_pair(std::reference_wrapper<std::string>(this->nameList[i]), i));
	}
}

void GSpriteSheetResource::appendSubImage(const std::string & name, const GRect & rect)
{
	this->nameList.push_back(name);
	this->rectList.push_back(rect);
}

void GSpriteSheetResource::setImageName(const std::string & imageName)
{
	this->imageName = imageName;
}

GSpriteSheet::LoaderMap * GSpriteSheet::getLoaderMap()
{
	static LoaderMap loaderMap;
	
	return &loaderMap;
}

void GSpriteSheet::registerLoader(const GSpriteSheetFormat format, const LoaderCallback & loader)
{
	getLoaderMap()->insert(std::make_pair(format, loader));
}

GSpriteSheet::GSpriteSheet()
{
}

GSpriteSheet::GSpriteSheet(const std::shared_ptr<GSpriteSheetResource> & resource)
	: resource(resource)
{
}


char * skipSpaces(char * p, char * end)
{
	while(p < end && isspace(*p)) {
		++p;
	}

	return p;
}

char * backSkipSpaces(char * p, char * begin)
{
	while(p > begin && isspace(*p)) {
		--p;
	}

	return p;
}

std::string getNextToken(char * & data, char * end, const char delimiter)
{
	data = skipSpaces(data, end);
	char * p = data;
	while(p < end && *p != delimiter) {
		++p;
	}

	if(p == data) {
		return std::string();
	}

	char * tokenEnd = backSkipSpaces(p - 1, data);
	std::string result(data, tokenEnd + 1 - data);
	data = p + 1;
	return result;
}

void spriteSheetLoader_spritePackText(const std::string & resourceName, GSpriteSheetResource * spriteSheet)
{
	spriteSheet->setImageName(resourceName + ".png");
	
	GFileInputStream stream = GResourceManager::getInstance()->getFileStream(resourceName + ".txt");
	
	const std::size_t size = (std::size_t)stream.getSize();
	std::unique_ptr<char[]> buffer(new char[size + 2]);
	stream.read(buffer.get(), size);
	buffer[size] = '\n';
	buffer[size + 1] = 0;

	char * bufferEnd = buffer.get() + size;

	char * data = buffer.get();
	for(;;) {
		data = skipSpaces(data, bufferEnd);
		if(data >= bufferEnd) {
			break;
		}

		char * endLine = strchr(data, '\n');
		if(endLine == nullptr) {
			break;
		}

		for(;;) {
			const std::string resourceName = getNextToken(data, endLine, '=');
			if(resourceName.empty()) break;
			const std::string x = getNextToken(data, endLine, ' ');
			if(x.empty()) break;
			const std::string y = getNextToken(data, endLine, ' ');
			if(y.empty()) break;
			const std::string width = getNextToken(data, endLine, ' ');
			if(width.empty()) break;
			const std::string height = getNextToken(data, endLine, ' ');
			if(height.empty()) break;

			spriteSheet->appendSubImage(resourceName, GRect{
				(GCoord)std::stoi(x),
				(GCoord)std::stoi(y),
				(GCoord)std::stoi(width),
				(GCoord)std::stoi(height),
			});

			break;
		}

		data = endLine + 1;
	}
}

G_AUTO_RUN_BEFORE_MAIN()
{
	GSpriteSheet::registerLoader(GSpriteSheetFormat::spritePackText, &spriteSheetLoader_spritePackText);
}


} //namespace gincu

