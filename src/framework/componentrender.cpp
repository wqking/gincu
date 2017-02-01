#include "framework/componentrender.h"
#include "framework/entity.h"
#include "framework/gameapplication.h"
#include "engine/resourcemanager.h"

namespace gincu {

ComponentRender::ComponentRender()
	: super(this)
{
}


ComponentContainerRender::ComponentContainerRender()
	: size{ 0, 0 }, renderList{}
{
}

ComponentContainerRender::~ComponentContainerRender()
{
}

ComponentContainerRender * ComponentContainerRender::add(ComponentRender * render)
{
	this->size.width = -1;

	this->renderList.push_back((ComponentRenderPointer)render);
	render->setEntity(this->getEntity());

	return this;
}

void ComponentContainerRender::doDraw()
{
	for(const ComponentRenderPointer & render : this->renderList) {
		render->draw();
	}
}

GameSize ComponentContainerRender::doGetSize() const
{
	if(this->size.width < 0) {
		this->size.width = 0;
		this->size.height = 0;
		
		for(const ComponentRenderPointer & render : this->renderList) {
			const GameSize renderSize = render->getSize();
			if(this->size.width < renderSize.width) {
				this->size.width = renderSize.width;
			}
			if(this->size.height < renderSize.height) {
				this->size.height = renderSize.height;
			}
		}
	}

	return this->size;
}

void ComponentContainerRender::doAfterSetEntity()
{
	Entity * entity = this->getEntity();
	for(const ComponentRenderPointer & render : this->renderList) {
		render->setEntity(entity);
	}
}


ComponentImageRender * createAndLoadImageComponent(const std::string & resourceName)
{
	ComponentImageRender * component = createComponent<ComponentImageRender >();
	component->setRender(GameApplication::getInstance()->getResourceManager()->getImage(resourceName));
	return component;
}

ComponentTextRender * createAndLoadTextComponent(const std::string & text, const GameColor textColor, const int fontSize)
{
	ComponentTextRender * component = createComponent<ComponentTextRender >();
	component->setRender(GameText(fontSize));
	component->getRender().setTextAndColor(text, textColor);
	return component;
}

ComponentRectRender * createRectRenderComponent(const GameColor color, const GameSize & size)
{
	ComponentRectRender * component = createComponent<ComponentRectRender >();
	component->setRender(RectRender());
	component->getRender().setColor(color);
	component->getRender().setSize(size);
	return component;
}


} //namespace gincu
