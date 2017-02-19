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

void GComponentContainerRender::doDraw(GRenderContext * renderContext)
{
	for(const ComponentRenderPointer & render : this->renderList) {
		render->draw(renderContext);
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
	return createComponent<GComponentImageRender>(GResourceManager::getInstance()->getImage(resourceName));
}

GComponentImageRender * createImageComponent(const GImage & image)
{
	return createComponent<GComponentImageRender>(image);
}

GComponentAtlasRender * createAtlasRenderComponent(const GAtlas & atlas, const std::string & name)
{
	GAtlasRender render(atlas);
	if(! name.empty()) {
		render.setIndex(render.getAtlas().getIndex(name));
	}
	return createComponent<GComponentAtlasRender>(render);
}

GComponentTextRender * createAndLoadTextComponent(const std::string & text, const GColor textColor, const int fontSize)
{
	GTextRender render;
	render.setText(text);
	render.setColor(textColor);
	render.setFontSize(fontSize);
	return createComponent<GComponentTextRender>(render);
}

GComponentRectRender * createRectRenderComponent(const GColor color, const GSize & size)
{
	GVertexArray vertexArray;

	vertexArray.append(GPoint{ 0, 0 }, color);
	vertexArray.append(GPoint{ size.width, 0 }, color);
	vertexArray.append(GPoint{ size.width, size.height }, color);
	vertexArray.append(GPoint{ size.width, size.height }, color);
	vertexArray.append(GPoint{ 0, size.height }, color);
	vertexArray.append(GPoint{ 0, 0 }, color);

	return createComponent<GComponentRectRender>(GVertexArrayRender(GPrimitive::triangleStrip, vertexArray));
}


} //namespace gincu
