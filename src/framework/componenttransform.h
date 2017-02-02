#ifndef COMPONENTTRANSFORM_H
#define COMPONENTTRANSFORM_H

#include "framework/component.h"
#include "engine/gametransform.h"

#include <vector>

namespace gincu{

class ComponentTransform : public Component
{
private:
	typedef Component super;

public:
	inline static constexpr unsigned int getComponentType() {
		return componentTypeId_Transform;
	}

public:
	ComponentTransform();
	explicit ComponentTransform(const GamePoint & position, const float scale = 1.0f, const bool visible = true);
	~ComponentTransform();

	GamePoint getPosition() const { return this->transform.getPosition(); }
	void setPosition(const GamePoint & position) { this->transform.setPosition(position); }

	float getScale() const { return this->transform.getScale(); }
	void setScale(const float scale) { this->transform.setScale(scale); }

	bool isVisible() const { return this->visible; }
	void setVisible(const bool visible) { this->visible = visible; }
	
	const GameTransform & getTransform() const { return this->transform; }
	void setTransform(const GameTransform & transform) { this->transform = transform; }

private:
	GameTransform transform;
	bool visible;
};

class ComponentLocalTransform : public ComponentTransform
{
private:
	typedef ComponentTransform super;

public:
	inline static constexpr int getComponentType() {
		return componentTypeId_LocalTransform;
	}
	
public:
	ComponentLocalTransform();
	explicit ComponentLocalTransform(const GamePoint & position, const float scale = 1.0f, const bool visible = true);
 	~ComponentLocalTransform();
	
	ComponentLocalTransform * setParent(ComponentLocalTransform * parent);
	ComponentLocalTransform * getParent() const;
	
	void applyGlobal();

private:
	void addChild(ComponentLocalTransform * child);
	void removeChild(ComponentLocalTransform * child);

private:
	ComponentLocalTransform * parent;
	std::vector<ComponentLocalTransform *> children;
};


} //namespace gincu

#endif
