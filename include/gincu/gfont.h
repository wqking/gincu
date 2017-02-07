#ifndef GFONT_H
#define GFONT_H

#include <memory>

namespace gincu {

class GFontData;

class GFont
{
public:
	GFont();
	~GFont();

	void setResource(const std::shared_ptr<GFontData> & data) { this->data = data; }
	const std::shared_ptr<GFontData> & getData() const { return this->data; }

private:
	std::shared_ptr<GFontData> data;
};


} //namespace gincu

#endif
