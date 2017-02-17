#ifndef GCOMPONENTTRANSFORM_H
#define GCOMPONENTTRANSFORM_H

#include "gincu/gcomponent.h"
#include "gincu/gtransform.h"

#include <vector>

namespace gincu{

template <typename T>
class GComponentTransformBase : public GComponent
{
private:
	typedef GComponent super;

public:
	GComponentTransformBase() :	GComponentTransformBase(GPoint()) {
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

class GComponentTransform : public GComponentTransformBase<GComponentTransform>
{
private:
	typedef GComponentTransformBase<GComponentTransform> super;

public:
	inline static constexpr unsigned int getComponentType() {
		return componentTypeId_Transform;
	}

public:
	GComponentTransform();
	explicit GComponentTransform(const GPoint & position, const GScale & scale = {1.0f, 1.0f}, const bool visible = true);
	~GComponentTransform();

	unsigned int getCameraId() const { return this->cameraId; }
	GComponentTransform * setCameraId(const unsigned int cameraId);
	
private:
	virtual void doAfterZOrderChanged();

private:
	unsigned int cameraId; // must between [0, 31]

private:
	friend class GComponentLocalTransform;
};

class GComponentLocalTransform : public GComponentTransformBase<GComponentLocalTransform>
{
private:
	typedef GComponentTransformBase<GComponentLocalTransform> super;

public:
	inline static constexpr int getComponentType() {
		return componentTypeId_LocalTransform;
	}
	
public:
	GComponentLocalTransform();
	explicit GComponentLocalTransform(const GPoint & position, const GScale & scale = {1.0f, 1.0f}, const bool visible = true);
 	~GComponentLocalTransform();
	
	GComponentLocalTransform * setParent(GComponentLocalTransform * parent);
	GComponentLocalTransform * getParent() const { return this->parent; }
	
	void applyGlobal();
	
	int getChildCount() const { return (int)this->children.size(); }
	GComponentLocalTransform * getChildAt(const int index) const { return this->children[index]; }
	const std::vector<GComponentLocalTransform *> & getSortedChildren() const;

private:
	void addChild(GComponentLocalTransform * child);
	void removeChild(GComponentLocalTransform * child);

private:
	virtual void doAfterZOrderChanged() override;

private:
	GComponentLocalTransform * parent;
	mutable std::vector<GComponentLocalTransform *> children;
	mutable bool needSortChildren;
};


} //namespace gincu

#endif
