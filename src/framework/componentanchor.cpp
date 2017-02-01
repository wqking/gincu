#include "framework/componentanchor.h"
#include "framework/componentrender.h"
#include "framework/componenttransform.h"
#include "framework/entity.h"
#include "framework/util.h"
#include "engine/renderanchor.h"

namespace gincu {

ComponentAnchor::ComponentAnchor()
	: super(this), anchor(RenderAnchor_None)
{
}

ComponentAnchor::ComponentAnchor(const int anchor)
	: super(this), anchor(anchor)
{
}

void ComponentAnchor::apply(GameTransform & transform, const GameSize & size)
{
	if(this->anchor != RenderAnchor_None) {
		transform.translate(-getOriginByRenderAnchor(this->anchor, size));
	}
}


} //namespace gincu
