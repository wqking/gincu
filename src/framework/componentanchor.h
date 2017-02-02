#ifndef COMPONENTANCHOR_H
#define COMPONENTANCHOR_H

#include "framework/component.h"
#include "framework/entity.h"
#include "engine/geometry.h"

namespace gincu {

class GameTransform;

// Note an anchor is applied after matrix transform
// so any rotation won't apply.
class ComponentAnchor : public Component
{
private:
	typedef Component super;

public:
	inline static constexpr unsigned int getComponentType() {
		return componentTypeId_Anchor;
	}

public:
	ComponentAnchor();
	explicit ComponentAnchor(const int anchor);

	int getAnchor() const { return this->anchor; }
	void setAnchor(const int renderAnchor) { this->anchor = renderAnchor; }
	
	void apply(GameTransform & transform, const GameSize & size);

private:
	int anchor;
};


} //namespace gincu

#endif
