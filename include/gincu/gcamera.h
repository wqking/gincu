#ifndef GCAMERA_H
#define GCAMERA_H

#include "gincu/ggeometry.h"

#include <cstdint>
#include <memory>

namespace gincu {

class GTransform;

class GCameraData;

class GCamera
{
public:
	GCamera();
	
	void apply(const GTransform & transform);

	void setViewport(const GRect & viewport) { this->viewport = viewport; }
	const GRect & getViewport() const { return this->viewport; }
	
	void setSize(const GSize & size) { this->size = size; }
	const GSize & getSize() const { return this->size; }

	uint32_t getMask() const { return this->mask; }
	void setMask(const uint32_t mask) { this->mask = mask; }

	const std::shared_ptr<GCameraData> & getData() const { return this->data; }

private:
	uint32_t mask;
	GRect viewport; // in pixels
	GSize size;
	std::shared_ptr<GCameraData> data;
};


} //namespace gincu


#endif
