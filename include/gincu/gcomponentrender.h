#ifndef GCOMPONENTRENDER_H
#define GCOMPONENTRENDER_H

#include "gincu/gcomponent.h"
#include "gincu/gcomponenttransform.h"
#include "gincu/gcomponentanchor.h"
#include "gincu/gentity.h"
#include "gincu/gentityutil.h"
#include "gincu/gimage.h"
#include "gincu/gtext.h"
#include "gincu/grectrender.h"
#include "gincu/grenderinfo.h"

#include <memory>

namespace gincu {

class GImageResource;

class GComponentRender : public GComponent
{
private:
	typedef GComponent super;

public:
	inline static constexpr unsigned int getComponentType() {
		return componentTypeId_Render;
	}

public:
	GComponentRender();

	void draw() {
		this->doDraw();
	}

	GSize getSize() const {
		return this->doGetSize();
	}

	const GRenderInfo * getBatchGroup() const {
		this->renderInfo.texture = this->doGetTexture();
		return &this->renderInfo;
	}

	GComponentRender * setBlendMode(const GBlendMode & blendMode) {
		this->renderInfo.blendMode = blendMode;
		return this;
	}

protected:
	GRenderInfo * getRenderInfo() { return &this->renderInfo; }

private:
	virtual void doDraw() = 0;
	virtual GSize doGetSize() const = 0;
	virtual const GImageResource * doGetTexture() const = 0;

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
	virtual void doDraw() override;
	virtual GSize doGetSize() const override;
	virtual void doAfterSetEntity() override;
	virtual const GImageResource * doGetTexture() const override { return nullptr; }

private:
	mutable GSize size;
	std::vector<ComponentRenderPointer> renderList;
};

template <typename RenderType>
class GComponentRenderImplement : public GComponentRender
{
private:
	typedef GComponentRender super;

public:
	GComponentRenderImplement()
	{
	}

	void setRender(const RenderType & renderer) {
		this->renderer = renderer;
	}

	RenderType & getRender() {
		return renderer;
	}

	const RenderType & getRender() const {
		return renderer;
	}

private:
	virtual void doDraw() override {
		GComponentTransform * transform = this->getEntity()->template getComponentByType<GComponentTransform>();
		if(transform->isVisible()) {
			this->renderer.draw(computeRenderableTransform(transform, this), this->getRenderInfo());
		}
	}

	virtual GSize doGetSize() const override {
		return this->renderer.getSize();
	}

	virtual const GImageResource * doGetTexture() const override {
		return this->renderer.getTexture();
	}

private:
	RenderType renderer;
};

typedef GComponentRenderImplement<GImage> GComponentImageRender;
typedef GComponentRenderImplement<GText> GComponentTextRender;
typedef GComponentRenderImplement<GRectRender> GComponentRectRender;

GComponentImageRender * createAndLoadImageComponent(const std::string & resourceName);
GComponentImageRender * createImageComponent(const GImage & image);
GComponentTextRender * createAndLoadTextComponent(const std::string & text, const GColor textColor, const int fontSize);
GComponentRectRender * createRectRenderComponent(const GColor color, const GSize & size);


} //namespace gincu

#endif
