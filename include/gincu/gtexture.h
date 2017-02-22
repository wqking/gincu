#ifndef GTEXTURE_H
#define GTEXTURE_H

#include "gincu/ggeometry.h"

#include <memory>

namespace gincu {

class GTextureData
{
public:
	virtual ~GTextureData() {}

	virtual void load(const std::string & fileName) = 0;
	virtual void reload() = 0;
	virtual GSize getSize() const = 0;
	virtual bool isValid() const = 0;
};

class GTexture
{
public:
	GTexture();
	explicit GTexture(const std::shared_ptr<GTextureData> & data);

	GSize getSize() const;
	bool isValid() const;

	const std::shared_ptr<GTextureData> & getData() const { return this->data; }

private:
	std::shared_ptr<GTextureData> data;
};

} //namespace gincu


#endif
