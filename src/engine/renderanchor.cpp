#include "engine/renderanchor.h"

namespace gincu {

GamePoint getOriginByRenderAnchor(const RenderAnchor renderAnchor, const GameSize & size)
{
	GamePoint result{ 0, 0 };

	switch(renderAnchor & RenderAnchor::hMask) {
	case RenderAnchor::hLeft:
		break;

	case RenderAnchor::hCenter:
		result.x = size.width / 2;
		break;

	case RenderAnchor::hRight:
		result.x = size.width;
		break;
	}

	switch(renderAnchor & RenderAnchor::vMask) {
	case RenderAnchor::vTop:
		break;

	case RenderAnchor::vCenter:
		result.y = size.height / 2;
		break;

	case RenderAnchor::vBottom:
		result.y = size.height;
		break;
	}

	return result;
}


} //namespace gincu
