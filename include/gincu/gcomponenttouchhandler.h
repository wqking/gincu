#ifndef GCOMPONENTTOUCHHANDLER_H
#define GCOMPONENTTOUCHHANDLER_H

#include "gincu/gcomponent.h"
#include "gincu/gtouchevent.h"
#include "cpgf/gcallbacklist.h"

namespace gincu {

class GComponentTouchHandler : public GComponent
{
private:
	typedef GComponent super;

public:
	typedef cpgf::GCallback<void (const GTouchEvent &)> OnTouched;
	typedef cpgf::GCallbackList<void (const GTouchEvent &)> OnTouchedList;

public:
	inline static constexpr unsigned int getComponentType() {
		return componentTypeId_TouchHandler;
	}

public:
	GComponentTouchHandler();

	GComponentTouchHandler * addOnTouch(const OnTouched & onTouch);
	void removeOnTouch(const OnTouched & onTouch);

	bool canHandle(const GPoint & point) const;
	void handle(const GTouchEvent & touchEvent);

private:
	virtual bool doCanHandle(const GPoint & point) const = 0;

private:
	OnTouchedList onTouchedList;
};

class GComponentRendererTouchHandler : public GComponentTouchHandler
{
public:
	GComponentRendererTouchHandler();

private:
	virtual bool doCanHandle(const GPoint & point) const;
};


} //namespace gincu

#endif
