#ifndef GCOMPONENTANCHOR_H
#define GCOMPONENTANCHOR_H

#include "gincu/gcomponent.h"
#include "gincu/ggeometry.h"

namespace gincu {

class GTransform;
enum class GRenderAnchor;

class GComponentAnchor : public GComponent
{
private:
	typedef GComponent super;

public:
	inline static constexpr unsigned int getComponentType() {
		return componentTypeId_Anchor;
	}

public:
	GComponentAnchor();
	explicit GComponentAnchor(const GRenderAnchor anchor);

	GRenderAnchor getAnchor() const { return this->anchor; }
	GComponentAnchor * setAnchor(const GRenderAnchor renderAnchor);

	bool isFlipX() const { return this->flipX; }
	GComponentAnchor * setFlipX(const bool flipX);
	
	bool isFlipY() const { return this->flipY; }
	GComponentAnchor * setFlipY(const bool flipY);

	void apply(GTransform & transform, const GSize & size);

private:
	void doCalculateGlobalFlip(bool * outputFlipX, bool * outputFlipY) const;

private:
	GRenderAnchor anchor;
	bool flipX;
	bool flipY;
};


} //namespace gincu

#endif
