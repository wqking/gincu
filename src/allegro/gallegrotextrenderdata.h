#ifndef GALLEGROTEXTRENDERDATA_H
#define GALLEGROTEXTRENDERDATA_H

#include "gincu/gtextrender.h"
#include "gincu/gresourcemanager.h"

#include "gallegrofontdata.h"
#include "gallegroutil.h"
#include "gallegrofontdata.h"

namespace gincu {

class GAllegroTextRenderData : public GTextRenderData
{
public:
	virtual void setText(const std::string & text) override {
		this->font = GResourceManager::getInstance()->getFont();
		this->text = text;
	}

	virtual void setColor(const GColor textColor) override {
		this->color = textColor;
	}
	
	virtual void setFontSize(const int fontSize) override {
		this->size = size;
	}

	virtual GSize getBoundingSize() const override {
		const GAllegroFontData * data = static_cast<const GAllegroFontData *>(this->font.getData().get());
		int x, y, width, height;
		al_get_text_dimensions(data->font, this->text.c_str(), &x, &y, &width, &height);
		return GSize { (GCoord)width, (GCoord)height };
	}

public:
	GFont font;
	std::string text;
	GColor color;
	int size;
};


} //namespace gincu



#endif
