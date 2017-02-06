#include "gincu/gcomponentrender.h"
#include "gincu/gentity.h"
#include "gincu/gapplication.h"
#include "gincu/gresourcemanager.h"

namespace gincu {

GComponentRender::GComponentRender()
	: super(this)
{
}


GComponentContainerRender::GComponentContainerRender()
	: size{ 0, 0 }, renderList{}
{
}

GComponentContainerRender::~GComponentContainerRender()
{
}

GComponentContainerRender * GComponentContainerRender::add(GComponentRender * render)
{
	this->size.width = -1;

	this->renderList.push_back((ComponentRenderPointer)render);
	render->setEntity(this->getEntity());

	return this;
}

void GComponentContainerRender::doDraw()
{
	for(const ComponentRenderPointer & render : this->renderList) {
		render->draw();
	}
}

GSize GComponentContainerRender::doGetSize() const
{
	if(this->size.width < 0) {
		this->size.width = 0;
		this->size.height = 0;
		
		for(const ComponentRenderPointer & render : this->renderList) {
			const GSize renderSize = render->getSize();
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

void GComponentContainerRender::doAfterSetEntity()
{
	GEntity * entity = this->getEntity();
	for(const ComponentRenderPointer & render : this->renderList) {
		render->setEntity(entity);
	}
}


GComponentImageRender * createAndLoadImageComponent(const std::string & resourceName)
{
	GComponentImageRender * component = createComponent<GComponentImageRender >();
	component->setRender(GResourceManager::getInstance()->getImage(resourceName));
	return component;
}

GComponentImageRender * createImageComponent(const GImage & image)
{
	GComponentImageRender * component = createComponent<GComponentImageRender >();
	component->setRender(image);
	return component;
}

GComponentTextRender * createAndLoadTextComponent(const std::string & text, const GColor textColor, const int fontSize)
{
	GComponentTextRender * component = createComponent<GComponentTextRender >();
	component->setRender(GText(fontSize));
	component->getRender().setTextAndColor(text, textColor);
	return component;
}

GComponentRectRender * createRectRenderComponent(const GColor color, const GSize & size)
{
	GComponentRectRender * component = createComponent<GComponentRectRender >();
	component->setRender(GRectRender());
	component->getRender().setColor(color);
	component->getRender().setSize(size);
	return component;
}


} //namespace gincu
