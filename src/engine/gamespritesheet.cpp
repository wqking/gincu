#include "engine/gamespritesheet.h"
#include "engine/errorhandler.h"
#include "engine/resourcemanager.h"
#include "engine/gameinputstream.h"
#include "framework/gameapplication.h"
#include "cpgf/goutmain.h"

#include <cstring>

namespace gincu {

void GameSpriteSheetResource::load(const std::string & resourceName, const SpriteSheetFormat format)
{
	const GameSpriteSheet::LoaderMap * loaderMap = GameSpriteSheet::getLoaderMap();
	auto it = loaderMap->find(format);
	if(it == loaderMap->end()) {
		handleFatal("Can't find sprite sheet loader.");
		return;
	}

	std::string imageFileName;
	it->second(resourceName, &this->imageMap, &imageFileName);
	this->imageResource = ResourceManager::getInstance()->getImage(imageFileName).getResource();
}

GameSpriteSheet::LoaderMap * GameSpriteSheet::getLoaderMap()
{
	static LoaderMap loaderMap;
	
	return &loaderMap;
}

void GameSpriteSheet::registerLoader(const SpriteSheetFormat format, const LoaderCallback & loader)
{
	getLoaderMap()->insert(std::make_pair(format, loader));
}

GameSpriteSheet::GameSpriteSheet()
{
}

GameSpriteSheet::GameSpriteSheet(const std::shared_ptr<GameSpriteSheetResource> & resource)
	: resource(resource)
{
}

GameImage GameSpriteSheet::getImage(const std::string & name) const
{
	auto it = this->resource->imageMap.find(name);
	if(it != this->resource->imageMap.end()) {
		return GameImage(this->resource->imageResource, it->second);
	}
	else {
		return GameImage();
	}
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

void spriteSheetLoader_spritePackText(const std::string & resourceName, std::map<std::string, GameRect> * imageMap, std::string * imageFileName)
{
	*imageFileName = resourceName + ".png";
	
	FileInputStream stream = ResourceManager::getInstance()->getFileStream(resourceName + ".txt");
	
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

			imageMap->insert(std::make_pair(resourceName, GameRect{
				(CoordType)std::stoi(x),
				(CoordType)std::stoi(y),
				(CoordType)std::stoi(width),
				(CoordType)std::stoi(height),
			}));

			break;
		}

		data = endLine + 1;
	}
}

G_AUTO_RUN_BEFORE_MAIN()
{
	GameSpriteSheet::registerLoader(SpriteSheetFormat::spritePackText, &spriteSheetLoader_spritePackText);
}


} //namespace gincu

