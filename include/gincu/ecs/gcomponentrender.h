#ifndef GCOMPONENTRENDER_H
#define GCOMPONENTRENDER_H

#include "gincu/ecs/gcomponent.h"
#include "gincu/ecs/gcomponenttransform.h"
#include "gincu/ecs/gcomponentanchor.h"
#include "gincu/ecs/gentity.h"
#include "gincu/ecs/gentityutil.h"
#include "gincu/gimage.h"
#include "gincu/gatlasrender.h"
#include "gincu/gtextrender.h"
#include "gincu/gvertexarrayrender.h"
#include "gincu/grenderinfo.h"

#include <memory>

namespace gincu {

class GTextureData;
class GRenderContext;

class GComponentRender : public GComponent
{
private:
	typedef GComponent super;

public:
	inline static constexpr GComponentType getComponentType() {
		return GComponentType::render;
	}

public:
	GComponentRender();

	void draw(GRenderContext * renderContext) {
		this->doDraw(renderContext);
	}

	GSize getSize() const {
		return this->doGetSize();
	}

	GComponentRender * setBlendMode(const GBlendMode & blendMode) {
		this->renderInfo.blendMode = blendMode;
		return this;
	}

protected:
	GRenderInfo * getRenderInfo() { return &this->renderInfo; }

private:
	virtual void doDraw(GRenderContext * renderContext) = 0;
	virtual GSize doGetSize() const = 0;

private:
	mutable GRenderInfo renderInfo;
};

class GComponentContainerRender : public GComponentRender
{
private:
	typedef std::shared_ptr<GComponentRender> ComponentRenderPointer;

public:
	GComponentContainerRender();
	~GComponentContainerRender();
	
	GComponentContainerRender * add(GComponentRender * render);

private:
	virtual void doDraw(GRenderContext * renderContext) override;
	virtual GSize doGetSize() const override;
	virtual void doAfterSetEntity() override;

private:
	mutable GSize size;
	std::vector<ComponentRenderPointer> renderList;
};

template <typename RenderType>
class GComponentRenderCommon : public GComponentRender
{
private:
	typedef GComponentRender super;

public:
	GComponentRenderCommon() : render() {}
	explicit GComponentRenderCommon(const RenderType & render) : render(render) {}

	void setRender(const RenderType & render) {
		this->render = render;
	}

	RenderType & getRender() {
		return render;
	}

	const RenderType & getRender() const {
		return render;
	}

private:
	virtual void doDraw(GRenderContext * renderContext) override {
		GComponentTransform * transform = this->getEntity()->template getComponentByType<GComponentTransform>();
		if(transform->isVisible()) {
			drawRender(this->render, renderContext, computeRenderableMatrix(transform, this), this->getRenderInfo());
		}
	}

	virtual GSize doGetSize() const override {
		return getRenderSize(this->render);
	}

private:
	RenderType render;
};

typedef GComponentRenderCommon<GImage> GComponentImageRender;
typedef GComponentRenderCommon<GAtlasRender> GComponentAtlasRender;
typedef GComponentRenderCommon<GTextRender> GComponentTextRender;
typedef GComponentRenderCommon<GVertexArrayRender> GComponentVertexArrayRender;
typedef GComponentVertexArrayRender GComponentRectRender;

GComponentImageRender * createAndLoadImageComponent(const std::string & resourceName);
GComponentImageRender * createImageComponent(const GImage & image);
GComponentAtlasRender * createAtlasRenderComponent(const GAtlas & atlas, const std::string & name);
GComponentTextRender * createAndLoadTextComponent(const std::string & text, const GColor textColor, const int fontSize);
GComponentRectRender * createRectRenderComponent(const GColor color, const GSize & size);


} //namespace gincu

#endif