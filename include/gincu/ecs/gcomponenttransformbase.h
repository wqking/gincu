#ifndef GCOMPONENTTRANSFORMBASE_H
#define GCOMPONENTTRANSFORMBASE_H

#include "gincu/ecs/gcomponent.h"
#include "gincu/gtransform.h"

namespace gincu {

template <typename T>
class GComponentTransformBase : public GComponent
{
private:
	typedef GComponent super;

public:
	GComponentTransformBase()
		:
			super(static_cast<T *>(this)),
			transform(),
			zOrder(0),
			visible(true)
	{
	}

	explicit GComponentTransformBase(const GPoint & position, const GScale & scale, const bool visible)
		:
			super(static_cast<T *>(this)),
			transform(position, scale),
			zOrder(0),
			visible(visible)
	{
	}

	~GComponentTransformBase() {
	}

	GPoint getPosition() const { return this->transform.getPosition(); }
	T * setPosition(const GPoint & position) { this->transform.setPosition(position); return static_cast<T *>(this); }

	GPoint getOrigin() const { return this->transform.getOrigin(); }
	T * setOrigin(const GPoint & origin) { this->transform.setOrigin(origin); return static_cast<T *>(this); }

	GScale getScale() const { return this->transform.getScale(); }
	T * setScale(const GScale & scale) { this->transform.setScale(scale); return static_cast<T *>(this); }

	float getRotation() const { return this->transform.getRotation(); }
	T * setRotation(const float rotation) { this->transform.setRotation(rotation); return static_cast<T *>(this); }

	bool isVisible() const { return this->visible; }
	T * setVisible(const bool visible) { this->visible = visible; return static_cast<T *>(this); }
	
	int getZOrder() const { return this->zOrder; }
	T * setZOrder(const int zOrder) {
		if(this->zOrder != zOrder) {
			this->zOrder = zOrder;
			
			this->doAfterZOrderChanged();
		}

		return static_cast<T *>(this);
	}

	const GTransform & getTransform() const { return this->transform; }
	GTransform & getTransform() { return this->transform; }
	T * setTransform(const GTransform & transform) { this->transform = transform; return static_cast<T *>(this); }

private:
	virtual void doAfterZOrderChanged() {}

private:
	GTransform transform;
	int zOrder;
	bool visible;
};


} //namespace gincu


#endif

