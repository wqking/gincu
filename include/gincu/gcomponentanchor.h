#ifndef GCOMPONENTANCHOR_H
#define GCOMPONENTANCHOR_H

#include "gincu/gcomponent.h"
#include "gincu/gentity.h"
#include "gincu/ggeometry.h"

namespace gincu {

class GameTransform;
enum class RenderAnchor;

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
	explicit ComponentAnchor(const RenderAnchor anchor);

	RenderAnchor getAnchor() const { return this->anchor; }
	ComponentAnchor * setAnchor(const RenderAnchor renderAnchor);

	bool isFlipX() const { return this->flipX; }
	ComponentAnchor * setFlipX(const bool flipX);
	
	bool isFlipY() const { return this->flipY; }
	ComponentAnchor * setFlipY(const bool flipY);

	void apply(GameTransform & transform, const GameSize & size);

private:
	RenderAnchor anchor;
	bool flipX;
	bool flipY;
};


} //namespace gincu

#endif
