#include "gincu/gfileinputstream.h"
#include "gincu/gdevicecontext.h"

namespace gincu {

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
	this->data = GDeviceContext::getInstance()->createFileInputStreamData();
	this->data->open(fileName);
}

void GFileInputStream::close()
{
	this->data.reset();
}

int64_t GFileInputStream::read(void * buffer, const int64_t size)
{
	return this->data->read(buffer, size);
}

int64_t GFileInputStream::seek(const int64_t position)
{
	return this->data->seek(position);
}

int64_t GFileInputStream::tell()
{
	return this->data->tell();
}

int64_t GFileInputStream::getSize()
{
	return this->data->getSize();
}


} //namespace gincu

