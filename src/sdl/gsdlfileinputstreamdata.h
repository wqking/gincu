#ifndef GSDLFILEINPUTSTREAMDATA_H
#define GSDLFILEINPUTSTREAMDATA_H

#include "gincu/gfileinputstream.h"

#include "SDL.h"

namespace gincu {

class GSdlFileInputStreamData : public GFileInputStreamData
{
public:
	GSdlFileInputStreamData() : file(nullptr)
	{
		this->close();
	}
	
	void close()
	{
		if(this->file != nullptr) {
			this->file = nullptr;
		}
	}

	virtual void open(const std::string & fileName) override
	{
		this->close();
		
		this->file = SDL_RWFromFile(fileName.c_str(), "rb");
	}

	virtual int64_t read(void * buffer, const int64_t size) override
	{
		return SDL_RWread(this->file, buffer, size, 1);
	}

	virtual int64_t seek(const int64_t position) override
	{
		return SDL_RWseek(this->file, position, RW_SEEK_SET);
	}

	virtual int64_t tell() override
	{
		return SDL_RWtell(this->file);
	}

	virtual int64_t getSize() override
	{
		return SDL_RWsize(this->file);
	}

	SDL_RWops * file;
};


} //namespace gincu


#endif

