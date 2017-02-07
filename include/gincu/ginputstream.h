#ifndef GINPUTSTREAM_H
#define GINPUTSTREAM_H

#include <cstdint>
#include <string>
#include <memory>

namespace gincu {

class FileInputStreamData;
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
	std::shared_ptr<FileInputStreamData> data;
};

} //namespace gincu



#endif
