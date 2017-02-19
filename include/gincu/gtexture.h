#ifndef GTEXTURE_H
#define GTEXTURE_H

#include "gincu/ggeometry.h"

#include <memory>

namespace gincu {

class GTextureData;

class GTexture
{
public:
	GTexture();
	explicit GTexture(const std::shared_ptr<GTextureData> & textureData);

	GSize getSize() const;
	bool isValid() const;

	const std::shared_ptr<GTextureData> & getData() const { return this->textureData; }

private:
	std::shared_ptr<GTextureData> textureData;
};

} //namespace gincu


#endif
