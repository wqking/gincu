#ifndef GFONT_H
#define GFONT_H

#include <string>
#include <memory>

namespace gincu {

class GFontData
{
public:
	virtual ~GFontData() {}
	virtual void load(const std::string & fileName) = 0;
};

class GFont
{
public:
	GFont();
	explicit GFont(const std::shared_ptr<GFontData> & data);
	~GFont();

	void setResource(const std::shared_ptr<GFontData> & data) { this->data = data; }
	const std::shared_ptr<GFontData> & getData() const { return this->data; }

private:
	std::shared_ptr<GFontData> data;
};


} //namespace gincu

#endif
