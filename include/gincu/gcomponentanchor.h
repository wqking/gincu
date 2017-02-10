#ifndef GCOMPONENTANCHOR_H
#define GCOMPONENTANCHOR_H

#include "gincu/gcomponent.h"
#include "gincu/ggeometry.h"

#include "cpgf/gflags.h"

namespace gincu {

class GTransform;
enum class GRenderAnchor;

class GComponentAnchor : public GComponent
{
private:
	typedef GComponent super;
	
	enum Flags {
		flagFlipX = (1u << 0),
		flagFlipY = (1u << 1),
		flagGlobalFlipX = (1u << 2),
		flagGlobalFlipY = (1u << 3)
	};

public:
	inline static constexpr unsigned int getComponentType() {
		return componentTypeId_Anchor;
	}

public:
	GComponentAnchor();
	explicit GComponentAnchor(const GRenderAnchor anchor);

	GRenderAnchor getAnchor() const { return this->anchor; }
	GComponentAnchor * setAnchor(const GRenderAnchor renderAnchor);

	bool isFlipX() const { return this->flags.has(flagFlipX); }
	GComponentAnchor * setFlipX(const bool flipX);
	
	bool isFlipY() const { return this->flags.has(flagFlipY); }
	GComponentAnchor * setFlipY(const bool flipY);

	void apply(GTransform & transform, const GSize & size);

private:
	void doApplyGlobalFlipXy(const bool parentGlobalFlipX, const bool parentGlobalFlipY);

	bool isGlobalFlipX() const { return this->flags.has(flagGlobalFlipX); }
	bool isGlobalFlipY() const { return this->flags.has(flagGlobalFlipY); }

private:
	virtual void doAfterSetEntity() override;

private:
	GRenderAnchor anchor;
	cpgf::GFlags<Flags> flags;
};


} //namespace gincu

#endif
