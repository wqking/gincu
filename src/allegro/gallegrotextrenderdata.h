#ifndef GALLEGROTEXTRENDERDATA_H
#define GALLEGROTEXTRENDERDATA_H

#include "gincu/gtextrender.h"
#include "gincu/gresourcemanager.h"

#include "gallegroutil.h"
#include "gallegrofontdata.h"

namespace gincu {

class GAllegroTextRenderData : public GTextRenderData
{
public:
	virtual void setText(const std::string & text) override {
	}

	virtual void setColor(const GColor textColor) override {
	}
	
	virtual void setFontSize(const int fontSize) override {
	}

	virtual GSize getBoundingSize() const override {
		return GSize();
	}

public:
};


} //namespace gincu



#endif
