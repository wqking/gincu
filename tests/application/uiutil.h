#ifndef UIUTIL_H
#define UIUTIL_H

#include "gincu/ggeometry.h"
#include "gincu/gentity.h"
#include "gincu/gevent.h"
#include "cpgf/gcallback.h"

cpgf::GCallback<void (const gincu::GEvent &)> createOnPressCallback(const cpgf::GCallback<void ()> & onPress);

gincu::GEntity * createBackButton(const cpgf::GCallback<void ()> & onClick);


#endif
