#ifndef GCAMERA_H
#define GCAMERA_H

#include "gincu/ggeometry.h"
#include "gincu/gmatrix.h"

#include <cstdint>
#include <memory>

namespace gincu {

class GTransform;

class GCameraData
{
public:
	virtual ~GCameraData() {}

	virtual void apply(const GMatrix44 & matrix, const GRect & viewport, const GRect & viewportPixels) = 0;
	virtual GPoint mapScreenToWorld(const GPoint & point, const GRect & viewportPixels) const = 0;
};

enum class GCameraFitStrategy
{
	none,
	scaleFitFullScreen, // keep the ascpect ratio as targetViewSize
	fixed, // use targetViewSize
};

class GCamera
{
public:
	GCamera();
	
	void apply(const GMatrix44 & matrix);

	// the size is between [0, 1]
	void setViewport(const GRect & viewport);
	const GRect & getViewport() const;
	GRect getViewportPixels() const;
	
	void setFitStrategy(const GCameraFitStrategy strategy);
	GCameraFitStrategy getFitStrategy() const { return this->fitStrategy; }
	
	void setTargetViewSize(const GSize & size);
	const GSize & getTargetViewSize() const { return this->targetViewSize; }
	
	void setWorldSize(const GSize & worldSize) { this->worldSize = worldSize; }
	const GSize & getWorldSize() const { return this->worldSize; }

	void setMask(const uint32_t mask) { this->mask = mask; }
	uint32_t getMask() const { return this->mask; }
	
	bool belongs(const unsigned int cameraId) const { return (this->mask & (1u << cameraId)) != 0; }

	const std::shared_ptr<GCameraData> & getData() const { return this->data; }

	GPoint mapScreenToWorld(const GPoint & point) const;
	
private:
	void doRequireRefresh();
	void doRefresh() const;

private:
	uint32_t mask;
	mutable GRect viewport; // in percentage
	GSize worldSize;
	GCameraFitStrategy fitStrategy;
	GSize targetViewSize; // in pixel
	mutable GSize cachedScreenSize;
	std::shared_ptr<GCameraData> data;
};


} //namespace gincu


#endif
