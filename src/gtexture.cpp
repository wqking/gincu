#include "gincu/gtexture.h"

namespace gincu {


GTexture::GTexture()
{
}

GTexture::GTexture(const std::shared_ptr<GTextureData> & data)
	: data(data)
{
}

GSize GTexture::getSize() const
{
	return this->data->getSize();
}

bool GTexture::isValid() const
{
	return (this->data && this->data->isValid());
}


} //namespace gincu


