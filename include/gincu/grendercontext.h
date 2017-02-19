#ifndef GRENDERCONTEXT_H
#define GRENDERCONTEXT_H

namespace gincu {

class GCamera;
class GImage;
class GTexture;
class GAtlasRender;
class GTextRender;
class GRectRender;
class GVertexArray;
enum class GPrimitive;
struct GRenderInfo;

class GRenderContext
{
public:
	virtual void switchCamera(const GCamera & camera) = 0;
	virtual void draw(const GImage & image, const GMatrix44 & matrix, const GRenderInfo * renderInfo) = 0;
	virtual void draw(const GAtlasRender & atlasRender, const GMatrix44 & matrix, const GRenderInfo * renderInfo) = 0;
	virtual void draw(const GTextRender & text, const GMatrix44 & matrix, const GRenderInfo * renderInfo) = 0;
	virtual void draw(const GRectRender & rect, const GMatrix44 & matrix, const GRenderInfo * renderInfo) = 0;
	virtual void draw(const GVertexArray & vertexArray, const GPrimitive type, const GTexture & texture, const GMatrix44 & matrix, const GRenderInfo * renderInfo) = 0;
};


} //namespace gincu


#endif
