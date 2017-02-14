#ifndef GCOMPONENTCAMERA_H
#define GCOMPONENTCAMERA_H

#include "gincu/gcomponent.h"
#include "gincu/ggeometry.h"

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
	inline static constexpr unsigned int getComponentType() {
		return componentTypeId_Camera;
	}

public:
	GComponentCamera();

	void setSize(const GSize & size);
	const GSize & getSize() const { return this->size; }

private:
	void onEntityEvent(GComponent * component, const GEntityEventType eventType);
	void doInitializeComponentTransform(GComponentTransform * componentTransform);

private:
	virtual void doAfterSetEntity() override;

private:
	GSize size;
};


} //namespace gincu


#endif
