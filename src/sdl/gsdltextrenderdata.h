#ifndef GSDLTEXTRENDERDATA_H
#define GSDLTEXTRENDERDATA_H

#include "gincu/gtextrender.h"
#include "gincu/gresourcemanager.h"

#include "gsdlutil.h"
#include "gsdlfontdata.h"

namespace gincu {

class GSdlTextRenderData : public GTextRenderData
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
