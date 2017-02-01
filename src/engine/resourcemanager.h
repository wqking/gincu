#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include "engine/gameimage.h"
#include "engine/gamefont.h"

#include <map>
#include <string>
#include <memory>

namespace gincu {

class GameImage;
class GameImageResource;

class ResourceManager
{
public:
	// Not singleton. It must be created somewhere, the default is created by GameApplication
	static ResourceManager * getInstance();

public:
	ResourceManager();
	~ResourceManager();

	GameImage getImage(const std::string & resourceName) const;

	const GameFont & getFont() const;

private:
	mutable std::map<std::string, std::shared_ptr<GameImageResource> > imageResourceMap;
	mutable std::unique_ptr<GameFont> font;
};


} //namespace gincu

#endif
