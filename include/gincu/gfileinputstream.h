#ifndef GFILEINPUTSTREAM_H
#define GFILEINPUTSTREAM_H

#include <cstdint>
#include <string>
#include <memory>

namespace gincu {

class GFileInputStreamData
{
public:
	virtual ~GFileInputStreamData() {}

	virtual void open(const std::string & fileName) = 0;
	virtual int64_t read(void * buffer, const int64_t size) = 0;
	virtual int64_t seek(const int64_t position) = 0;
	virtual int64_t tell() = 0;
	virtual int64_t getSize() = 0;
};

class GFileInputStream
{
public:
	GFileInputStream();
	explicit GFileInputStream(const std::string & fileName);
	~GFileInputStream();

	void open(const std::string & fileName);
	void close();

	int64_t read(void * buffer, const int64_t size);
	int64_t seek(const int64_t position);
	int64_t tell();
	int64_t getSize();

private:
	std::shared_ptr<GFileInputStreamData> data;
};

} //namespace gincu



#endif
