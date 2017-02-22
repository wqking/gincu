#ifndef GRESOURCEMANAGER_H
#define GRESOURCEMANAGER_H

#include "gincu/gimage.h"
#include "gincu/gatlas.h"
#include "gincu/gfont.h"

#include "cpgf/gcallback.h"

#include <map>
#include <string>
#include <memory>
#include <mutex>

namespace gincu {

class GImage;
class GTextureData;
class GAtlasData;
class GFontData;
enum class GAtlasFormat;

class GResourceManager
{
public:
	// Not singleton. It must be created somewhere, the default is created by GApplication
	static GResourceManager * getInstance();

	typedef cpgf::GCallback<void ()> LoaderCallback;

private:
	typedef std::recursive_mutex MutexType;
	typedef std::lock_guard<MutexType> LockType;

public:
	GResourceManager();
	~GResourceManager();

	void initialize();
	void finalize();

	GImage getImage(const std::string & resourceName) const;
	GImage asyncGetImage(const std::string & resourceName, const LoaderCallback & callback = LoaderCallback()) const;

	GAtlas getAtlas(const std::string & resourceName, const GAtlasFormat format) const;

	GFont getFont(const std::string & resourceName) const;
	GFont asyncGetFont(const std::string & resourceName, const LoaderCallback & callback = LoaderCallback()) const;
	GFont getFont() const;

	std::string solveResourcePath(const std::string & resourceName) const;
	
	void reloadResources();

	const std::string & getResourcePath() const { return this->resourcePath; }

	void setDefaultFontName(const std::string & defaultFontName) { this->defaultFontName = defaultFontName; }
	const std::string & getDefaultFontName() const { return this->defaultFontName; }

private:
	std::string resourcePath;

	mutable MutexType imageMutex;
	mutable std::map<std::string, std::shared_ptr<GTextureData> > imageDataMap;
	mutable std::map<std::string, std::shared_ptr<GAtlasData> > atlasDataMap;
	mutable MutexType fontMutex;
	mutable std::map<std::string, std::shared_ptr<GFontData> > fontDataMap;
	std::string defaultFontName;
};


} //namespace gincu

#endif
