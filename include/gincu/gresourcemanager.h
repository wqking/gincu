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

	const GFont & getFont() const;

private:
	std::string resourcePath;
	mutable std::map<std::string, std::shared_ptr<GImageData> > imageResourceMap;
	mutable std::map<std::string, std::shared_ptr<GSpriteSheetData> > spriteSheetResourceMap;
	mutable std::unique_ptr<GFont> font;
};


} //namespace gincu

#endif
