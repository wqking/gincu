#ifndef GSDLTEXTUREDATA_H
#define GSDLTEXTUREDATA_H

#include "gincu/gtexture.h"

#include "SDL_gpu.h"

#include <string>

namespace gincu {

class GSdlTextureData : public GTextureData
{
public:
	GSdlTextureData() : image(nullptr) {}
	~GSdlTextureData()
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
		this->image = GPU_LoadImage(this->fileName.c_str());
	}

	virtual GSize getSize() const override
	{
		if(this->image != nullptr) {
			return { this->image->texture_w, this->image->texture_h };
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
			GPU_FreeImage(this->image);
			this->image = nullptr;
		}
	}
	
	std::string fileName;
	GPU_Image * image;
};

} //namespace gincu



#endif
