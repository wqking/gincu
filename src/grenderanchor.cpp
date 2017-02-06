#include "gincu/grenderanchor.h"

namespace gincu {

GPoint getOriginByRenderAnchor(const GRenderAnchor renderAnchor, const GSize & size)
{
	GPoint result{ 0, 0 };

	switch(renderAnchor & GRenderAnchor::hMask) {
	case GRenderAnchor::hLeft:
		break;

	case GRenderAnchor::hCenter:
		result.x = size.width / 2;
		break;

	case GRenderAnchor::hRight:
		result.x = size.width;
		break;
	}

	switch(renderAnchor & GRenderAnchor::vMask) {
	case GRenderAnchor::vTop:
		break;

	case GRenderAnchor::vCenter:
		result.y = size.height / 2;
		break;

	case GRenderAnchor::vBottom:
		result.y = size.height;
		break;
	}

	return result;
}


} //namespace gincu
