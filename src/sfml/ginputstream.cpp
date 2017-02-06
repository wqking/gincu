#include "gincu/ginputstream.h"

#include <SFML/System.hpp>

namespace gincu {

class FileInputStreamResource
{
public:
	sf::FileInputStream stream;
};

GFileInputStream::GFileInputStream()
{
}

GFileInputStream::GFileInputStream(const std::string & fileName)
{
	this->open(fileName);
}

GFileInputStream::~GFileInputStream()
{
	this->close();
}

void GFileInputStream::open(const std::string & fileName)
{
	this->resource.reset(new FileInputStreamResource());
	this->resource->stream.open(fileName);
}

void GFileInputStream::close()
{
	this->resource.reset();
}

int64_t GFileInputStream::read(void * data, const int64_t size)
{
	return this->resource->stream.read(data, size);
}

int64_t GFileInputStream::seek(const int64_t position)
{
	return this->resource->stream.seek(position);
}

int64_t GFileInputStream::tell()
{
	return this->resource->stream.tell();
}

int64_t GFileInputStream::getSize()
{
	return this->resource->stream.getSize();
}


} //namespace gincu

