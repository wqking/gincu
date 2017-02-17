#ifndef GCOMPONENTCAMERA_H
#define GCOMPONENTCAMERA_H

#include "gincu/gcomponent.h"
#include "gincu/ggeometry.h"
#include "gincu/gcamera.h"

#include "cpgf/gflags.h"

namespace gincu {

class GTransform;
class GComponentTransform;
enum class GEntityEventType;

class GComponentCamera : public GComponent
{
private:
	typedef GComponent super;

public:
	inline static constexpr GComponentType getComponentType() {
		return GComponentType::camera;
	}

public:
	GComponentCamera();

	GComponentCamera * setViewport(const GRect & viewport) { this->camera.setViewport(viewport); return this; }
	const GRect & getViewport() const { return this->camera.getViewport(); }
	
	GComponentCamera * setFitStrategy(const GCameraFitStrategy strategy) { this->camera.setFitStrategy(strategy); return this; }
	GCameraFitStrategy getFitStrategy() const { return this->camera.getFitStrategy(); }
	
	GComponentCamera * setTargetViewSize(const GSize & size) { this->camera.setTargetViewSize(size); return this; }
	const GSize & getTargetViewSize() const { return this->camera.getTargetViewSize(); }
	
	GComponentCamera * setWorldSize(const GSize & worldSize);
	const GSize & getWorldSize() const { return this->camera.getWorldSize(); }

	GComponentCamera * setMask(const uint32_t mask);
	uint32_t getMask() const { return this->camera.getMask(); }

	bool belongs(const unsigned int cameraId) const { return this->camera.belongs(cameraId); }
	const GCamera & getCamera() const { return this->camera; }

private:
	void onEntityEvent(GComponent * component, const GEntityEventType eventType);
	void doInitializeComponentTransform(GComponentTransform * componentTransform);

private:
	virtual void doAfterSetEntity() override;

private:
	GCamera camera;
};


} //namespace gincu


#endif
