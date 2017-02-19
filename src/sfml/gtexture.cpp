#include "gincu/gtexture.h"
#include "gtexturedata.h"

namespace gincu {


GTexture::GTexture()
{
}

GTexture::GTexture(const std::shared_ptr<GTextureData> & textureData)
	: textureData(textureData)
{
}

GSize GTexture::getSize() const
{
	if(this->textureData) {
		auto size = this->textureData->texture.getSize();
		return { (GCoord)size.x, (GCoord)size.y };
	}
	else {
		return GSize();
	}
}

bool GTexture::isValid() const
{
	return (bool)this->textureData;
}


} //namespace gincu


