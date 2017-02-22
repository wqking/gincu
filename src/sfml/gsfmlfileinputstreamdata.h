#ifndef GSFMLFILEINPUTSTREAMDATA_H
#define GSFMLFILEINPUTSTREAMDATA_H

#include "gincu/gfileinputstream.h"

#include <SFML/System.hpp>

namespace gincu {

class GSfmlFileInputStreamData : public GFileInputStreamData
{
public:
	virtual void open(const std::string & fileName) override
	{
		this->stream.open(fileName);
	}

	virtual int64_t read(void * buffer, const int64_t size) override
	{
		return this->stream.read(buffer, size);
	}

	virtual int64_t seek(const int64_t position) override
	{
		return this->stream.seek(position);
	}

	virtual int64_t tell() override
	{
		return this->stream.tell();
	}

	virtual int64_t getSize() override
	{
		return this->stream.getSize();
	}

	sf::FileInputStream stream;
};


} //namespace gincu


#endif

