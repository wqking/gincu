#ifndef GFONT_H
#define GFONT_H

#include <memory>

namespace gincu {

class GFontResource;

class GFont
{
public:
	GFont();
	~GFont();

	void setResource(const std::shared_ptr<GFontResource> & resource) { this->resource = resource; }
	const std::shared_ptr<GFontResource> & getResource() const { return this->resource; }

private:
	std::shared_ptr<GFontResource> resource;
};


} //namespace gincu

#endif
