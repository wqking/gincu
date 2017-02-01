#include "engine/renderanchor.h"

namespace gincu {

GamePoint getOriginByRenderAnchor(const int renderAnchor, const GameSize & size)
{
	GamePoint result{ 0, 0 };

	switch(renderAnchor & RenderAnchor_Hmask) {
	case RenderAnchor_Hleft:
		break;

	case RenderAnchor_Hcenter:
		result.x = size.width / 2;
		break;

	case RenderAnchor_Hright:
		result.x = size.width;
		break;
	}

	switch(renderAnchor & RenderAnchor_Vmask) {
	case RenderAnchor_Vtop:
		break;

	case RenderAnchor_Vcenter:
		result.y = size.height / 2;
		break;

	case RenderAnchor_Vbottom:
		result.y = size.height;
		break;
	}

	return result;
}


} //namespace gincu
