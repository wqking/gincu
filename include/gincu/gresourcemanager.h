#ifndef GRESOURCEMANAGER_H
#define GRESOURCEMANAGER_H

#include "gincu/gimage.h"
#include "gincu/gatlas.h"
#include "gincu/gfont.h"
#include "gincu/ginputstream.h"

#include <map>
#include <string>
#include <memory>

namespace gincu {

class GImage;
class GImageData;
class GAtlasData;
class GFontData;
enum class GAtlasFormat;

class GResourceManager
{
public:
	// Not singleton. It must be created somewhere, the default is created by GApplication
	static GResourceManager * getInstance();

public:
	GResourceManager();
	~GResourceManager();

	GImage getImage(const std::string & resourceName) const;

	GAtlas getAtlas(const std::string & resourceName, const GAtlasFormat format) const;

	GFileInputStream getFileStream(const std::string & resourceName) const;

	GFont getFont(const std::string & resourceName) const;
	GFont getFont() const;

	std::string solveResourcePath(const std::string & resourceName) const;

	const std::string & getResourcePath() const { return this->resourcePath; }

	void setDefaultFontName(const std::string & defaultFontName) { this->defaultFontName = defaultFontName; }

private:
	std::string resourcePath;
	mutable std::map<std::string, std::shared_ptr<GImageData> > imageDataMap;
	mutable std::map<std::string, std::shared_ptr<GAtlasData> > atlasDataMap;
	mutable std::map<std::string, std::shared_ptr<GFontData> > fontDataMap;
	std::string defaultFontName;
};


} //namespace gincu

#endif
