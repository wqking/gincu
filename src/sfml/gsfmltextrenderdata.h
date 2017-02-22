#ifndef GSFMLTEXTRENDERDATA_H
#define GSFMLTEXTRENDERDATA_H

#include "gincu/gtextrender.h"
#include "gincu/gresourcemanager.h"

#include "gsfmlutil.h"
#include "gfontdata.h"

#include <SFML/Graphics.hpp>

namespace gincu {

class GSfmlTextRenderData : public GTextRenderData
{
public:
	virtual void setText(const std::string & text) override {
		this->text.setFont(GResourceManager::getInstance()->getFont().getData()->font);
		this->text.setString(text);
	}

	virtual void setColor(const GColor textColor) override {
		this->text.setOutlineColor(gameColorToSfml(textColor));
		this->text.setFillColor(gameColorToSfml(textColor));
	}
	
	virtual void setFontSize(const int fontSize) override {
		this->text.setCharacterSize(fontSize);
	}

	virtual GSize getBoundingSize() const override {
		auto rect = this->text.getLocalBounds();
		return { rect.width, rect.height };
	}

public:
	sf::Text text;
};


} //namespace gincu



#endif
