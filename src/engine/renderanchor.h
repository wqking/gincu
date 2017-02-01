#ifndef RENDERANCHOR_H
#define RENDERANCHOR_H

#include "engine/geometry.h"

namespace gincu {

const int RenderAnchor_Hleft = 0x01;
const int RenderAnchor_Hcenter = 0x02;
const int RenderAnchor_Hright = 0x03;
const int RenderAnchor_Hmask = 0x0f;

const int RenderAnchor_Vtop = 0x10;
const int RenderAnchor_Vcenter = 0x20;
const int RenderAnchor_Vbottom = 0x30;
const int RenderAnchor_Vmask = 0xf0;

const int RenderAnchor_LeftTop = RenderAnchor_Hleft | RenderAnchor_Vtop;
const int RenderAnchor_Center = RenderAnchor_Hcenter | RenderAnchor_Vcenter;
const int RenderAnchor_None = 0;

GamePoint getOriginByRenderAnchor(const int renderAnchor, const GameSize & size);


} //namespace gincu

#endif
