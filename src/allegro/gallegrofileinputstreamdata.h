#ifndef GALLEGROFILEINPUTSTREAMDATA_H
#define GALLEGROFILEINPUTSTREAMDATA_H

#include "gincu/gfileinputstream.h"

#include "allegro5/allegro.h"

namespace gincu {

class GAllegroFileInputStreamData : public GFileInputStreamData
{
public:
	GAllegroFileInputStreamData()
		: file(nullptr)
	{
	}
	
	~GAllegroFileInputStreamData()
	{
		this->close();
	}

	void close()
	{
		if(this->file != nullptr) {
			al_fclose(this->file);
			this->file = nullptr;
		}
	}

	virtual void open(const std::string & fileName) override
	{
		this->close();
		
		this->file = al_fopen(fileName.c_str(), "rb");
	}

	virtual int64_t read(void * buffer, const int64_t size) override
	{
		return al_fread(this->file, buffer, size);
	}

	virtual int64_t seek(const int64_t position) override
	{
		return al_fseek(this->file, position, ALLEGRO_SEEK_SET);
	}

	virtual int64_t tell() override
	{
		return al_ftell(this->file);
	}

	virtual int64_t getSize() override
	{
		return al_fsize(this->file);
	}

	ALLEGRO_FILE * file;
};


} //namespace gincu


#endif

