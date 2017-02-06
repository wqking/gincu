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
	void setPosition(const GPoint & position) { this->transform.setPosition(position); }

	GScale getScale() const { return this->transform.getScale(); }
	void setScale(const GScale & scale) { this->transform.setScale(scale); }

	float getRotation() const { return this->transform.getRotation(); }
	void setRotation(const float rotation) { this->transform.setRotation(rotation); }

	bool isVisible() const { return this->visible; }
	void setVisible(const bool visible) { this->visible = visible; }
	
	const GTransform & getTransform() const { return this->transform; }
	void setTransform(const GTransform & transform) { this->transform = transform; }

private:
	GTransform transform;
	bool visible;
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
	GComponentLocalTransform * getParent() const;
	
	void applyGlobal();

private:
	void addChild(GComponentLocalTransform * child);
	void removeChild(GComponentLocalTransform * child);

private:
	GComponentLocalTransform * parent;
	std::vector<GComponentLocalTransform *> children;
};


} //namespace gincu

#endif
