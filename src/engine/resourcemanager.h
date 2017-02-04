#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include "engine/gameimage.h"
#include "engine/gamespritesheet.h"
#include "engine/gamefont.h"
#include "engine/gameinputstream.h"

#include <map>
#include <string>
#include <memory>

namespace gincu {

class GameImage;
class GameImageResource;
class GameSpriteSheetResource;
enum class SpriteSheetFormat;

class ResourceManager
{
public:
	// Not singleton. It must be created somewhere, the default is created by GameApplication
	static ResourceManager * getInstance();

public:
	ResourceManager();
	~ResourceManager();

	GameImage getImage(const std::string & resourceName) const;

	GameSpriteSheet getSpriteSheet(const std::string & resourceName, const SpriteSheetFormat format) const;

	FileInputStream getFileStream(const std::string & resourceName) const;

	const GameFont & getFont() const;

private:
	std::string resourcePath;
	mutable std::map<std::string, std::shared_ptr<GameImageResource> > imageResourceMap;
	mutable std::map<std::string, std::shared_ptr<GameSpriteSheetResource> > spriteSheetResourceMap;
	mutable std::unique_ptr<GameFont> font;
};


} //namespace gincu

#endif
