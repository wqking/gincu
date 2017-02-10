#ifndef GCOMPONENTRENDER_H
#define GCOMPONENTRENDER_H

#include "gincu/gcomponent.h"
#include "gincu/gcomponenttransform.h"
#include "gincu/gcomponentanchor.h"
#include "gincu/gentity.h"
#include "gincu/gentityutil.h"
#include "gincu/gimage.h"
#include "gincu/gspritesheetrender.h"
#include "gincu/gtextrender.h"
#include "gincu/grectrender.h"
#include "gincu/grenderinfo.h"

#include <memory>

namespace gincu {

class GImageData;

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

	GComponentRender * setBlendMode(const GBlendMode & blendMode) {
		this->renderInfo.blendMode = blendMode;
		return this;
	}

protected:
	GRenderInfo * getRenderInfo() { return &this->renderInfo; }

private:
	virtual void doDraw() = 0;
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
	virtual void doDraw() override;
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
	virtual void doDraw() override {
		GComponentTransform * transform = this->getEntity()->template getComponentByType<GComponentTransform>();
		if(transform->isVisible()) {
			this->render.draw(computeRenderableTransform(transform, this), this->getRenderInfo());
		}
	}

	virtual GSize doGetSize() const override {
		return this->render.getSize();
	}

private:
	RenderType render;
};

typedef GComponentRenderCommon<GImage> GComponentImageRender;
typedef GComponentRenderCommon<GSpriteSheetRender> GComponentSpriteSheetRender;
typedef GComponentRenderCommon<GTextRender> GComponentTextRender;
typedef GComponentRenderCommon<GRectRender> GComponentRectRender;

GComponentImageRender * createAndLoadImageComponent(const std::string & resourceName);
GComponentImageRender * createImageComponent(const GImage & image);
GComponentSpriteSheetRender * createSpriteSheetComponent(const GSpriteSheet & spriteSheet, const std::string & name);
GComponentTextRender * createAndLoadTextComponent(const std::string & text, const GColor textColor, const int fontSize);
GComponentRectRender * createRectRenderComponent(const GColor color, const GSize & size);


} //namespace gincu

#endif
