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

enum class GSpriteSheetFormat
{
	// http://spritesheetpacker.codeplex.com/
	// a = 0 0 60 60
	// b = 61 0 60 60
	// c = 0 61 60 60
	spritePackText,
};

class GImageResource;

class GSpriteSheetResource
{
private:
	template <typename T>
	struct LessCompare {
		bool operator() (const T & a, const T & b) const { return a.get() < b.get(); }
	};

public:
	void load(const std::string & resourceName, const GSpriteSheetFormat format);

	GImage getImage(const std::string & name) const;
	int getIndex(const std::string & name) const;

	const std::vector<std::string> & getNameList() const { return this->nameList; }
	const std::vector<GRect> & getRectList() const { return this->rectList; }
	const std::shared_ptr<GImageResource> & getImageResource() const { return this->imageResource; }

public: // used by loaders, don't use them directly
	void appendSubImage(const std::string & name, const GRect & rect);
	void setImageName(const std::string & imageName);

private:
	std::string imageName;
	std::vector<std::string> nameList;
	std::vector<GRect> rectList;
	std::map<std::reference_wrapper<std::string>, std::size_t, LessCompare<std::reference_wrapper<std::string> > > indexMap;
	std::shared_ptr<GImageResource> imageResource;
};

class GSpriteSheet
{
private:
	typedef cpgf::GCallback<void (const std::string &, GSpriteSheetResource *)> LoaderCallback;
	typedef std::map<GSpriteSheetFormat, LoaderCallback> LoaderMap;

public:
	static void registerLoader(const GSpriteSheetFormat format, const LoaderCallback & loader);

public:
	GSpriteSheet();
	explicit GSpriteSheet(const std::shared_ptr<GSpriteSheetResource> & resource);

	GImage getImage(const std::string & name) const { return this->resource->getImage(name); }

	const std::vector<std::string> & getNameList() const { return this->resource->getNameList(); }
	const std::vector<GRect> & getRectList() const { return this->resource->getRectList(); }
	const std::shared_ptr<GImageResource> & getImageResource() const { return this->resource->getImageResource(); }

	int getImageCount() const { return (int)this->resource->getNameList().size(); }
	int getIndex(const std::string & name) const { return this->resource->getIndex(name); }

private:
	static LoaderMap * getLoaderMap();

private:
	std::shared_ptr<GSpriteSheetResource> resource;

private:
	friend class GSpriteSheetResource;
};

} //namespace gincu


#endif

