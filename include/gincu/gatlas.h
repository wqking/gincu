#ifndef GATLAS_H
#define GATLAS_H

#include "gincu/ggeometry.h"
#include "gincu/gimage.h"
#include "gincu/gtexture.h"
#include "gincu/gutil.h"

#include "cpgf/gcallback.h"

#include <string>
#include <map>
#include <vector>
#include <memory>
#include <functional>

namespace gincu {

enum class GAtlasFormat
{
	// http://spritesheetpacker.codeplex.com/
	// a = 0 0 60 60
	// b = 61 0 60 60
	// c = 0 61 60 60
	spritePackText,
};

class GAtlasData
{
public:
	void load(const std::string & resourceName, const GAtlasFormat format);

	GImage getImage(const std::string & name) const;
	int getIndex(const std::string & name) const;

	const std::vector<std::string> & getNameList() const { return this->nameList; }
	const std::vector<GRect> & getRectList() const { return this->rectList; }

	const GTexture & getTexture() const { return this->texture; }

public: // used by loaders, don't use them directly
	void appendSubImage(const std::string & name, const GRect & rect);
	void setImageName(const std::string & imageName);

private:
	std::string imageName;
	std::vector<std::string> nameList;
	std::vector<GRect> rectList;
	std::map<std::reference_wrapper<const std::string>, std::size_t, ReferenceWrapperLessCompare<std::reference_wrapper<const std::string> > > indexMap;
	GTexture texture;
};

class GAtlas
{
public:
	typedef cpgf::GCallback<void (const std::string &, GAtlasData *)> LoaderCallback;
	typedef std::map<GAtlasFormat, LoaderCallback> LoaderMap;

public:
	static void registerLoader(const GAtlasFormat format, const LoaderCallback & loader);

public:
	GAtlas();
	explicit GAtlas(const std::shared_ptr<GAtlasData> & data);

	GImage getImage(const std::string & name) const { return this->data->getImage(name); }

	const std::vector<std::string> & getNameList() const { return this->data->getNameList(); }
	const std::vector<GRect> & getRectList() const { return this->data->getRectList(); }

	const GTexture & getTexture() const { return this->data->getTexture(); }

	int getImageCount() const { return (int)this->data->getNameList().size(); }
	int getIndex(const std::string & name) const { return this->data->getIndex(name); }

	// internal use
	static LoaderMap * getLoaderMap();

private:
	std::shared_ptr<GAtlasData> data;
};

} //namespace gincu


#endif

