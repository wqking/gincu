#ifndef COMPONENTRENDER_H
#define COMPONENTRENDER_H

#include "framework/component.h"
#include "framework/componenttransform.h"
#include "framework/componentanchor.h"
#include "framework/entity.h"
#include "framework/entityutil.h"
#include "engine/gameimage.h"
#include "engine/gametext.h"
#include "engine/rectrender.h"

#include <memory>

namespace gincu {

class ComponentRender : public Component
{
private:
	typedef Component super;

public:
	inline static constexpr unsigned int getComponentType() {
		return componentTypeId_Render;
	}

public:
	ComponentRender();

	void draw() {
		this->doDraw();
	}

	GameSize getSize() const {
		return this->doGetSize();
	}

private:
	virtual void doDraw() = 0;
	virtual GameSize doGetSize() const = 0;
};

class ComponentContainerRender : public ComponentRender
{
private:
	typedef std::shared_ptr<ComponentRender> ComponentRenderPointer;

public:
	ComponentContainerRender();
	~ComponentContainerRender();
	
	ComponentContainerRender * add(ComponentRender * render);

private:
	virtual void doDraw() override;
	virtual GameSize doGetSize() const override;
	virtual void doAfterSetEntity() override;
	
private:
	mutable GameSize size;
	std::vector<ComponentRenderPointer> renderList;
};

template <typename RenderType>
class ComponentRenderImplement : public ComponentRender
{
private:
	typedef ComponentRender super;

public:
	ComponentRenderImplement()
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
		ComponentTransform * transform = this->getEntity()->template getComponentByType<ComponentTransform>();
		if(transform->isVisible()) {
			this->renderer.draw(computeRenderableTransform(transform, this));
		}
	}

	virtual GameSize doGetSize() const {
		return this->renderer.getSize();
	}

private:
	RenderType renderer;
};

typedef ComponentRenderImplement<GameImage> ComponentImageRender;
typedef ComponentRenderImplement<GameText> ComponentTextRender;
typedef ComponentRenderImplement<RectRender> ComponentRectRender;

ComponentImageRender * createAndLoadImageComponent(const std::string & resourceName);
ComponentImageRender * createImageComponent(const GameImage & image);
ComponentTextRender * createAndLoadTextComponent(const std::string & text, const GameColor textColor, const int fontSize);
ComponentRectRender * createRectRenderComponent(const GameColor color, const GameSize & size);


} //namespace gincu

#endif
