#include "gincu/ginputstream.h"

#include <SFML/System.hpp>

namespace gincu {

class FileInputStreamData
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
	this->data.reset(new FileInputStreamData());
	this->data->stream.open(fileName);
}

void GFileInputStream::close()
{
	this->data.reset();
}

int64_t GFileInputStream::read(void * buffer, const int64_t size)
{
	return this->data->stream.read(buffer, size);
}

int64_t GFileInputStream::seek(const int64_t position)
{
	return this->data->stream.seek(position);
}

int64_t GFileInputStream::tell()
{
	return this->data->stream.tell();
}

int64_t GFileInputStream::getSize()
{
	return this->data->stream.getSize();
}


} //namespace gincu

