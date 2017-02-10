#include "gincu/gcomponentanchor.h"
#include "gincu/gcomponentrender.h"
#include "gincu/gcomponenttransform.h"
#include "gincu/gentity.h"
#include "gincu/gentityutil.h"
#include "gincu/gutil.h"
#include "gincu/grenderanchor.h"

namespace gincu {

GComponentAnchor::GComponentAnchor()
	:
		super(this),
		anchor(GRenderAnchor::leftTop)
{
}

GComponentAnchor::GComponentAnchor(const GRenderAnchor anchor)
	:
		super(this),
		anchor(anchor)
{
}

GComponentAnchor * GComponentAnchor::setAnchor(const GRenderAnchor renderAnchor)
{
	this->anchor = renderAnchor;
	return this;
}

GComponentAnchor * GComponentAnchor::setFlipX(const bool flipX)
{
	if(flipX != this->isFlipX()) {
		const bool parentGlobalFlipX = this->isFlipX() ^ this->isGlobalFlipX();
		const bool parentGlobalFlipY = this->isFlipY() ^ this->isGlobalFlipY();
		
		this->flags.setByBool(flagFlipX, flipX);
		
		this->doApplyGlobalFlipXy(parentGlobalFlipX, parentGlobalFlipY);
	}
	return this;
}

GComponentAnchor * GComponentAnchor::setFlipY(const bool flipY)
{
	if(flipY != this->isFlipY()) {
		const bool parentGlobalFlipX = this->isFlipX() ^ this->isGlobalFlipX();
		const bool parentGlobalFlipY = this->isFlipY() ^ this->isGlobalFlipY();
		
		this->flags.setByBool(flagFlipY, flipY);
		
		this->doApplyGlobalFlipXy(parentGlobalFlipX, parentGlobalFlipY);
	}
	return this;
}

void GComponentAnchor::apply(GTransform & transform, const GSize & size)
{
	const bool globalFlipX = this->isGlobalFlipX();
	const bool globalFlipY = this->isGlobalFlipY();
	
	if(globalFlipX || globalFlipY) {
		const GScale scale = transform.getDecompositedScale();
		if(! isEqual(scale.x, 0.0f) && ! isEqual(scale.y, 0.0f)) {
			transform.scale({ 1.0f / scale.x, 1.0f / scale.y });
		}
		if(globalFlipX && ! globalFlipY) {
			transform.scale({ -scale.x, scale.y });
			if((this->anchor & GRenderAnchor::hLeft) != GRenderAnchor::none) {
				transform.translate({ -size.width, 0 });
			}
		}
		else if(! globalFlipX && globalFlipY) {
			transform.scale({ scale.x, -scale.y });
			if((this->anchor & GRenderAnchor::vTop) != GRenderAnchor::none) {
				transform.translate({ 0, -size.height });
			}
		}
		else if(globalFlipX && globalFlipY) {
			transform.scale({ -scale.x, -scale.y });
			GPoint translate{ 0, 0 };
			if((this->anchor & GRenderAnchor::hLeft) != GRenderAnchor::none) {
				translate.x = -size.width;
			}
			if((this->anchor & GRenderAnchor::vTop) != GRenderAnchor::none) {
				translate.y = -size.height;
			}
			transform.translate(translate);
		}
	}

	if(this->anchor != GRenderAnchor::leftTop) {
		transform.translate(-getOriginByRenderAnchor(this->anchor, size));
	}
}

void GComponentAnchor::doApplyGlobalFlipXy(const bool parentGlobalFlipX, const bool parentGlobalFlipY)
{
	this->flags.setByBool(flagGlobalFlipX, parentGlobalFlipX ^ this->isFlipX());
	this->flags.setByBool(flagGlobalFlipY, parentGlobalFlipY ^ this->isFlipY());
	
	if(this->getEntity() == nullptr) {
		return;
	}
	enumerateEntityChildren(this->getEntity()->getComponentByType<GComponentLocalTransform>(),
		[=](GComponentLocalTransform * localTransform) {
			GComponentAnchor * anchor = localTransform->getEntity()->getComponentByType<GComponentAnchor>();
			if(anchor != nullptr) {
				anchor->doApplyGlobalFlipXy(this->isGlobalFlipX(), this->isGlobalFlipY());
			}
		}
	);
}

void GComponentAnchor::doAfterSetEntity()
{
	GComponentLocalTransform * localTransform = this->getEntity()->getComponentByType<GComponentLocalTransform>();
	if(localTransform != nullptr && localTransform->getParent() != nullptr) {
		GComponentAnchor * parentAnchor = localTransform->getParent()->getEntity()->getComponentByType<GComponentAnchor>();
		if(parentAnchor != nullptr) {
			this->flags.setByBool(flagGlobalFlipX, parentAnchor->isGlobalFlipX() ^ this->isFlipX());
			this->flags.setByBool(flagGlobalFlipY, parentAnchor->isGlobalFlipY() ^ this->isFlipY());
		}
	}
}


} //namespace gincu
