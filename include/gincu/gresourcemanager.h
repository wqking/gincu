#ifndef GRESOURCEMANAGER_H
#define GRESOURCEMANAGER_H

#include "gincu/gimage.h"
#include "gincu/gspritesheet.h"
#include "gincu/gfont.h"
#include "gincu/ginputstream.h"

#include <map>
#include <string>
#include <memory>

namespace gincu {

class GImage;
class GImageData;
class GSpriteSheetData;
class GFontData;
enum class GSpriteSheetFormat;

class GResourceManager
{
public:
	// Not singleton. It must be created somewhere, the default is created by GApplication
	static GResourceManager * getInstance();

public:
	GResourceManager();
	~GResourceManager();

	GImage getImage(const std::string & resourceName) const;

	GSpriteSheet getSpriteSheet(const std::string & resourceName, const GSpriteSheetFormat format) const;

	GFileInputStream getFileStream(const std::string & resourceName) const;

	GFont getFont(const std::string & resourceName) const;
	GFont getFont() const;

	std::string solveResourcePath(const std::string & resourceName) const;

	const std::string & getResourcePath() const { return this->resourcePath; }

	void setDefaultFontName(const std::string & defaultFontName) { this->defaultFontName = defaultFontName; }

private:
	std::string resourcePath;
	mutable std::map<std::string, std::shared_ptr<GImageData> > imageDataMap;
	mutable std::map<std::string, std::shared_ptr<GSpriteSheetData> > spriteSheetDataMap;
	mutable std::map<std::string, std::shared_ptr<GFontData> > fontDataMap;
	std::string defaultFontName;
};


} //namespace gincu

#endif
