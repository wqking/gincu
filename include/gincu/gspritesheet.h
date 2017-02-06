#ifndef GSPRITESHEET_H
#define GSPRITESHEET_H

#include "gincu/ggeometry.h"
#include "gincu/gimage.h"
#include "cpgf/gcallback.h"

#include <string>
#include <map>
#include <vector>
#include <memory>
#include <functional>

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

class GameSpriteSheetResource
{
private:
	template <typename T>
	struct LessCompare {
		bool operator() (const T & a, const T & b) const { return a.get() < b.get(); }
	};

public:
	void load(const std::string & resourceName, const SpriteSheetFormat format);
	GameImage getImage(std::string name) const;

	const std::vector<std::string> & getNameList() const { return this->nameList; }
	const std::vector<GameRect> & getRectList() const { return this->rectList; }

public: // used by loaders, don't use them directly
	void appendSubImage(const std::string & name, const GameRect & rect);
	void setImageName(const std::string & imageName);

private:
	std::string imageName;
	std::vector<std::string> nameList;
	std::vector<GameRect> rectList;
	std::map<std::reference_wrapper<std::string>, std::size_t, LessCompare<std::reference_wrapper<std::string> > > indexMap;
	std::shared_ptr<GameImageResource> imageResource;
};

class GameSpriteSheet
{
private:
	typedef cpgf::GCallback<void (const std::string &, GameSpriteSheetResource *)> LoaderCallback;
	typedef std::map<SpriteSheetFormat, LoaderCallback> LoaderMap;

public:
	static void registerLoader(const SpriteSheetFormat format, const LoaderCallback & loader);

public:
	GameSpriteSheet();
	explicit GameSpriteSheet(const std::shared_ptr<GameSpriteSheetResource> & resource);

	GameImage getImage(const std::string & name) const { return this->resource->getImage(name); }

	const std::vector<std::string> & getNameList() const { return this->resource->getNameList(); }
	const std::vector<GameRect> & getRectList() const { return this->resource->getRectList(); }

private:
	static LoaderMap * getLoaderMap();

private:
	std::shared_ptr<GameSpriteSheetResource> resource;

private:
	friend class GameSpriteSheetResource;
};

} //namespace gincu


#endif

