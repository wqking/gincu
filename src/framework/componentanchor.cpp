#include "framework/componentanchor.h"
#include "framework/componentrender.h"
#include "framework/componenttransform.h"
#include "framework/entity.h"
#include "framework/util.h"
#include "engine/renderanchor.h"

namespace gincu {

ComponentAnchor::ComponentAnchor()
	:
		super(this),
		anchor(RenderAnchor::leftTop),
		flipX(false),
		flipY(false)
{
}

ComponentAnchor::ComponentAnchor(const RenderAnchor anchor)
	:
		super(this),
		anchor(anchor),
		flipX(false),
		flipY(false)
{
}

ComponentAnchor * ComponentAnchor::setAnchor(const RenderAnchor renderAnchor)
{
	this->anchor = renderAnchor;
	return this;
}

ComponentAnchor * ComponentAnchor::setFlipX(const bool flipX)
{
	this->flipX = flipX;
	return this;
}

ComponentAnchor * ComponentAnchor::setFlipY(const bool flipY)
{
	this->flipY = flipY;
	return this;
}

void ComponentAnchor::apply(GameTransform & transform, const GameSize & size)
{
	if(this->flipX || this->flipY) {
		const GameScale scale = transform.getDecompositedScale();
		if(! isEqual(scale.x, 0.0f) && ! isEqual(scale.y, 0.0f)) {
			transform.scale({ 1.0f / scale.x, 1.0f / scale.y });
		}
		if(this->flipX && ! this->flipY) {
			transform.scale({ -scale.x, scale.y });
			if((this->anchor & RenderAnchor::hLeft) != RenderAnchor::none) {
				transform.translate({ -size.width, 0 });
			}
		}
		else if(! this->flipX && this->flipY) {
			transform.scale({ scale.x, -scale.y });
			if((this->anchor & RenderAnchor::vTop) != RenderAnchor::none) {
				transform.translate({ 0, -size.height });
			}
		}
		else if(this->flipX && this->flipY) {
			transform.scale({ -scale.x, -scale.y });
			GamePoint translate{ 0, 0 };
			if((this->anchor & RenderAnchor::hLeft) != RenderAnchor::none) {
				translate.x = -size.width;
			}
			if((this->anchor & RenderAnchor::vTop) != RenderAnchor::none) {
				translate.y = -size.height;
			}
			transform.translate(translate);
		}
	}

	if(this->anchor != RenderAnchor::leftTop) {
		transform.translate(-getOriginByRenderAnchor(this->anchor, size));
	}
}


} //namespace gincu
