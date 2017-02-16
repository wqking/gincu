#ifndef UIUTIL_H
#define UIUTIL_H

#include "gincu/ggeometry.h"
#include "gincu/gentity.h"
#include "gincu/gevent.h"

#include "cpgf/gcallback.h"

#include <string>

cpgf::GCallback<void (const gincu::GEvent &)> createOnPressCallback(const cpgf::GCallback<void ()> & onPress);

gincu::GEntity * createBackButton(const cpgf::GCallback<void ()> & onClick);

constexpr gincu::GSize defaultButtonSize { 100, 30 };

gincu::GEntity * createButton(
		const std::string & text,
		const gincu::GPoint & position,
		const cpgf::GCallback<void ()> & onClick,
		const gincu::GSize size = defaultButtonSize
	);


#endif
