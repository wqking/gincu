#include "gincu/gcomponentanchor.h"
#include "gincu/gcomponentrender.h"
#include "gincu/gcomponenttransform.h"
#include "gincu/gentity.h"
#include "gincu/gutil.h"
#include "gincu/grenderanchor.h"

namespace gincu {

GComponentAnchor::GComponentAnchor()
	:
		super(this),
		anchor(GRenderAnchor::leftTop),
		flipX(false),
		flipY(false)
{
}

GComponentAnchor::GComponentAnchor(const GRenderAnchor anchor)
	:
		super(this),
		anchor(anchor),
		flipX(false),
		flipY(false)
{
}

GComponentAnchor * GComponentAnchor::setAnchor(const GRenderAnchor renderAnchor)
{
	this->anchor = renderAnchor;
	return this;
}

GComponentAnchor * GComponentAnchor::setFlipX(const bool flipX)
{
	this->flipX = flipX;
	return this;
}

GComponentAnchor * GComponentAnchor::setFlipY(const bool flipY)
{
	this->flipY = flipY;
	return this;
}

void GComponentAnchor::apply(GTransform & transform, const GSize & size)
{
	if(this->flipX || this->flipY) {
		const GScale scale = transform.getDecompositedScale();
		if(! isEqual(scale.x, 0.0f) && ! isEqual(scale.y, 0.0f)) {
			transform.scale({ 1.0f / scale.x, 1.0f / scale.y });
		}
		if(this->flipX && ! this->flipY) {
			transform.scale({ -scale.x, scale.y });
			if((this->anchor & GRenderAnchor::hLeft) != GRenderAnchor::none) {
				transform.translate({ -size.width, 0 });
			}
		}
		else if(! this->flipX && this->flipY) {
			transform.scale({ scale.x, -scale.y });
			if((this->anchor & GRenderAnchor::vTop) != GRenderAnchor::none) {
				transform.translate({ 0, -size.height });
			}
		}
		else if(this->flipX && this->flipY) {
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


} //namespace gincu
