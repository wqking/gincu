#ifndef GCOMPONENTTRANSFORM_H
#define GCOMPONENTTRANSFORM_H

#include "gincu/gcomponent.h"
#include "gincu/gtransform.h"

#include <vector>

namespace gincu{

class GComponentTransform : public GComponent
{
private:
	typedef GComponent super;

public:
	inline static constexpr unsigned int getComponentType() {
		return componentTypeId_Transform;
	}

public:
	GComponentTransform();
	explicit GComponentTransform(const GPoint & position, const GScale & scale = {1.0f, 1.0f}, const bool visible = true);
	~GComponentTransform();

	GPoint getPosition() const { return this->transform.getPosition(); }
	GComponentTransform * setPosition(const GPoint & position) { this->transform.setPosition(position); return this; }

	GScale getScale() const { return this->transform.getScale(); }
	GComponentTransform * setScale(const GScale & scale) { this->transform.setScale(scale); return this; }

	float getRotation() const { return this->transform.getRotation(); }
	GComponentTransform * setRotation(const float rotation) { this->transform.setRotation(rotation); return this; }

	bool isVisible() const { return this->visible; }
	GComponentTransform * setVisible(const bool visible) { this->visible = visible; return this; }
	
	const GTransform & getTransform() const { return this->transform; }
	GComponentTransform * setTransform(const GTransform & transform) { this->transform = transform; return this; }

	int getZOrder() const { return this->zOrder; }
	GComponentTransform * setZOrder(const int zOrder);

private:
	virtual void doAfterZOrderChanged(const int oldZOrder);

private:
	GTransform transform;
	bool visible;
	int zOrder;
};

class GComponentLocalTransform : public GComponentTransform
{
private:
	typedef GComponentTransform super;

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
	virtual void doAfterZOrderChanged(const int oldZOrder) override;

private:
	GComponentLocalTransform * parent;
	mutable std::vector<GComponentLocalTransform *> children;
	mutable bool needSortChildren;
};


} //namespace gincu

#endif
