#ifndef GALLEGROFONTDATA_H
#define GALLEGROFONTDATA_H

#include "gincu/gfont.h"

#include "allegro5/allegro_font.h"

namespace gincu {

class GAllegroFontData : public GFontData
{
public:
	GAllegroFontData()
		: font(nullptr)
	{
	}

	~GAllegroFontData()
	{
		this->unload();
	}

	virtual void load(const std::string & fileName) override
	{
		this->unload();

		this->font = al_load_font(fileName.c_str(), 10, 0);
	}

	void unload()
	{
		if(this->font != nullptr) {
			al_destroy_font(this->font);
			this->font = nullptr;
		}
	}

	ALLEGRO_FONT * font;
};


} //namespace gincu



#endif
