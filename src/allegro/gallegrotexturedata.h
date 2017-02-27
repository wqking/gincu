#ifndef GALLEGROTEXTUREDATA_H
#define GALLEGROTEXTUREDATA_H

#include "gincu/gtexture.h"
#include "gincu/glog.h"

#include "allegro5/allegro.h"

#include <string>

namespace gincu {

class GAllegroTextureData : public GTextureData
{
public:
	GAllegroTextureData()
		: image(nullptr)
	{
	}

	~GAllegroTextureData()
	{
		this->close();
	}
	
	virtual void load(const std::string & fileName) override
	{
		this->fileName = fileName;
		this->reload();
	}

	virtual void reload() override
	{
		this->close();

		this->image = al_load_bitmap(this->fileName.c_str());
		
		if(this->image == nullptr) {
			G_LOG_ERROR("Can't load image %s", this->fileName.c_str());
		}
	}

	virtual GSize getSize() const override
	{
		if(this->image != nullptr) {
			return { (GCoord)al_get_bitmap_width(this->image), (GCoord)al_get_bitmap_height(this->image) };
		}
		else {
			return GSize();
		}
	}
	
	virtual bool isValid() const override
	{
		return this->image != nullptr;
	}
	
	void close()
	{
		if(this->image != nullptr) {
			al_destroy_bitmap(this->image);
		}
	}
	
	std::string fileName;
	ALLEGRO_BITMAP * image;
};

} //namespace gincu



#endif
