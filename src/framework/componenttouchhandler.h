#ifndef COMPONENTTOUCHHANDLER_H
#define COMPONENTTOUCHHANDLER_H

#include "framework/component.h"
#include "engine/touchevent.h"
#include "cpgf/gcallbacklist.h"

namespace gincu {

class ComponentTouchHandler : public Component
{
private:
	typedef Component super;

public:
	typedef cpgf::GCallback<void (const TouchEvent &)> OnTouched;
	typedef cpgf::GCallbackList<void (const TouchEvent &)> OnTouchedList;

public:
	inline static constexpr unsigned int getComponentType() {
		return componentTypeId_TouchHandler;
	}

public:
	ComponentTouchHandler();

	ComponentTouchHandler * addOnTouch(const OnTouched & onTouch);
	void removeOnTouch(const OnTouched & onTouch);

	bool canHandle(const GamePoint & point) const;
	void handle(const TouchEvent & touchEvent);

private:
	virtual bool doCanHandle(const GamePoint & point) const = 0;

private:
	OnTouchedList onTouchedList;
};

class ComponentRendererTouchHandler : public ComponentTouchHandler
{
public:
	ComponentRendererTouchHandler();

private:
	virtual bool doCanHandle(const GamePoint & point) const;
};


} //namespace gincu

#endif
