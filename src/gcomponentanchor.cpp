#include "gincu/gcomponentanchor.h"
#include "gincu/gcomponentrender.h"
#include "gincu/gcomponenttransform.h"
#include "gincu/gentity.h"
#include "gincu/gentityutil.h"
#include "gincu/gutil.h"
#include "gincu/grenderanchor.h"

namespace gincu {

namespace {

GScale getDecompositedScale(const GMatrix44 & matrix)
{
	const auto p1 = transformPoint(matrix, { 0, 0 });
	const auto p2 = transformPoint(matrix, { 1, 0 });
	const auto p3 = transformPoint(matrix, { 0, 1 });
	return { p2.x - p1.x, p3.y - p1.y };
}


} //unnamed namespace

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
		
		this->flags.setByBool(Flags::flagFlipX, flipX);
		
		this->doApplyGlobalFlipXy(parentGlobalFlipX, parentGlobalFlipY);
	}
	return this;
}

GComponentAnchor * GComponentAnchor::setFlipY(const bool flipY)
{
	if(flipY != this->isFlipY()) {
		const bool parentGlobalFlipX = this->isFlipX() ^ this->isGlobalFlipX();
		const bool parentGlobalFlipY = this->isFlipY() ^ this->isGlobalFlipY();
		
		this->flags.setByBool(Flags::flagFlipY, flipY);
		
		this->doApplyGlobalFlipXy(parentGlobalFlipX, parentGlobalFlipY);
	}
	return this;
}

void GComponentAnchor::apply(GMatrix44 & matrix, const GSize & size)
{
	const bool globalFlipX = this->isGlobalFlipX();
	const bool globalFlipY = this->isGlobalFlipY();
	
	if(globalFlipX || globalFlipY) {
		const GScale scale = getDecompositedScale(matrix);
		if(! isEqual(scale.x, 0.0f) && ! isEqual(scale.y, 0.0f)) {
			matrix = scaleMatrix(matrix, { 1.0f / scale.x, 1.0f / scale.y });
		}
		if(globalFlipX && ! globalFlipY) {
			matrix = scaleMatrix(matrix, { -scale.x, scale.y });
			if((this->anchor & GRenderAnchor::hLeft) != GRenderAnchor::none) {
				matrix = translateMatrix(matrix, { -size.width, 0 });
			}
		}
		else if(! globalFlipX && globalFlipY) {
			matrix = scaleMatrix(matrix, { scale.x, -scale.y });
			if((this->anchor & GRenderAnchor::vTop) != GRenderAnchor::none) {
				matrix = translateMatrix(matrix, { 0, -size.height });
			}
		}
		else if(globalFlipX && globalFlipY) {
			matrix = scaleMatrix(matrix, { -scale.x, -scale.y });
			GPoint translate{ 0, 0 };
			if((this->anchor & GRenderAnchor::hLeft) != GRenderAnchor::none) {
				translate.x = -size.width;
			}
			if((this->anchor & GRenderAnchor::vTop) != GRenderAnchor::none) {
				translate.y = -size.height;
			}
			matrix = translateMatrix(matrix, translate);
		}
	}

	if(this->anchor != GRenderAnchor::leftTop) {
		matrix = translateMatrix(matrix, -getOriginByRenderAnchor(this->anchor, size));
	}
}

void GComponentAnchor::doApplyGlobalFlipXy(const bool parentGlobalFlipX, const bool parentGlobalFlipY)
{
	this->flags.setByBool(Flags::flagGlobalFlipX, parentGlobalFlipX ^ this->isFlipX());
	this->flags.setByBool(Flags::flagGlobalFlipY, parentGlobalFlipY ^ this->isFlipY());
	
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
			this->flags.setByBool(Flags::flagGlobalFlipX, parentAnchor->isGlobalFlipX() ^ this->isFlipX());
			this->flags.setByBool(Flags::flagGlobalFlipY, parentAnchor->isGlobalFlipY() ^ this->isFlipY());
		}
	}
}


} //namespace gincu
