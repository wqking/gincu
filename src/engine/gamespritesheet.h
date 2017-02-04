#ifndef GAMESPRITESHEET_H
#define GAMESPRITESHEET_H

#include "engine/geometry.h"
#include "cpgf/gcallback.h"

#include <string>
#include <map>
#include <memory>

namespace gincu {

enum class SpriteSheetFormat
{
	// http://spritesheetpacker.codeplex.com/
	// a = 0 0 60 60
	// b = 61 0 60 60
	// c = 0 61 60 60
	spritePackText,
};

class GameImageResource;
class GameImage;

class GameSpriteSheet
{
private:
	typedef cpgf::GCallback<void (const std::string &, std::map<std::string, GameRect> *, std::string *)> LoaderCallback;
	typedef std::map<SpriteSheetFormat, LoaderCallback> LoaderMap;

public:
	static void registerLoader(const SpriteSheetFormat format, const LoaderCallback & loader);

public:
	void load(const std::string & resourceName, const SpriteSheetFormat format);
	GameImage getImage(const std::string & name) const;

private:
	static LoaderMap * getLoaderMap();

private:
	std::map<std::string, GameRect> imageMap;
	std::shared_ptr<GameImageResource> imageResource;
};

} //namespace gincu


#endif

