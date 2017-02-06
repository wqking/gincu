#include "gincu/ginputstream.h"

#include <SFML/System.hpp>

namespace gincu {

class FileInputStreamResource
{
public:
	sf::FileInputStream stream;
};

FileInputStream::FileInputStream()
{
}

FileInputStream::FileInputStream(const std::string & fileName)
{
	this->open(fileName);
}

FileInputStream::~FileInputStream()
{
	this->close();
}

void FileInputStream::open(const std::string & fileName)
{
	this->resource.reset(new FileInputStreamResource());
	this->resource->stream.open(fileName);
}

void FileInputStream::close()
{
	this->resource.reset();
}

int64_t FileInputStream::read(void * data, const int64_t size)
{
	return this->resource->stream.read(data, size);
}

int64_t FileInputStream::seek(const int64_t position)
{
	return this->resource->stream.seek(position);
}

int64_t FileInputStream::tell()
{
	return this->resource->stream.tell();
}

int64_t FileInputStream::getSize()
{
	return this->resource->stream.getSize();
}


} //namespace gincu

