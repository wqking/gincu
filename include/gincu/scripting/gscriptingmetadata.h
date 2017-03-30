#ifndef GSCRIPTINGMETADATA_H
#define GSCRIPTINGMETADATA_H

#include "gincu/gevent.h"
#include "gincu/ggeometry.h"

#include "cpgf/gcallback.h"
#include "cpgf/scriptbind/gscriptbindapi.h"
#include "cpgf/accessor/gaccessor.h"

#include <string>
#include <memory>

// The code in this file is intended to be used in script, not in C++.

namespace gincu {

// Doxygen treats it as variable if we expand OnTouchCallback to result type directly
typedef cpgf::GCallback<void (const GEvent &)> OnTouchCallback;
OnTouchCallback createOnTouchedCallback(cpgf::IScriptFunction * func);

typedef cpgf::GAccessor<cpgf::GGetter<cpgf::GCallback<float ()> >, cpgf::GSetter<cpgf::GCallback<void (float)> > > FloatAccessor;
FloatAccessor createFloatAccessor(
		const cpgf::GVariant & instance,
		const std::string & getterName,
		const std::string & setterName
	);

typedef cpgf::GAccessor<cpgf::GGetter<cpgf::GCallback<GPoint ()> >, cpgf::GSetter<cpgf::GCallback<void (GPoint)> > > PointAccessor;
PointAccessor createPointAccessor(
		const cpgf::GVariant & instance,
		const std::string & getterName,
		const std::string & setterName
	);

typedef cpgf::GAccessor<cpgf::GGetter<cpgf::GCallback<GScale ()> >, cpgf::GSetter<cpgf::GCallback<void (GScale)> > > ScaleAccessor;
ScaleAccessor createScaleAccessor(
		const cpgf::GVariant & instance,
		const std::string & getterName,
		const std::string & setterName
	);

std::shared_ptr<void> createSharedPointer(const cpgf::GVariant & instance);


} //namespace gincu


#endif
