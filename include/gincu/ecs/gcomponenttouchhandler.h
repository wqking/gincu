#ifndef GCOMPONENTTOUCHHANDLER_H
#define GCOMPONENTTOUCHHANDLER_H

#include "gincu/ecs/gcomponent.h"
#include "gincu/ggeometry.h"

#include "cpgf/gcallbacklist.h"

#include <memory>

namespace gincu {

class GEvent;

class GComponentTouchHandler : public GComponent
{
private:
	typedef GComponent super;

public:
	typedef cpgf::GCallback<void (const GEvent &)> OnTouched;
	typedef cpgf::GCallbackList<void (const GEvent &)> OnTouchedList;

public:
	inline static constexpr GComponentType getComponentType() {
		return GComponentType::touchHandler;
	}

public:
	GComponentTouchHandler();

	GComponentTouchHandler * addOnTouch(const OnTouched & onTouch);
	void removeOnTouch(const OnTouched & onTouch);

	bool canHandle(const GPoint & worldPosition) const;
	void handle(const GEvent & touchEvent);

private:
	virtual bool doCanHandle(const GPoint & worldPosition) const = 0;

private:
	std::shared_ptr<OnTouchedList> onTouchedList;
};

class GComponentRendererTouchHandler : public GComponentTouchHandler
{
public:
	GComponentRendererTouchHandler();

private:
	virtual bool doCanHandle(const GPoint & worldPosition) const;
};

struct GTouchHandlerFindResult
{
	GComponentTouchHandler * handler;
	GPoint worldPosition;
};


} //namespace gincu

#endif
