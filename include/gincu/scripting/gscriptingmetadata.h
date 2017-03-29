#ifndef GSCRIPTINGMETADATA_H
#define GSCRIPTINGMETADATA_H

#include "gincu/gevent.h"

#include "cpgf/gcallback.h"
#include "cpgf/scriptbind/gscriptbindapi.h"
#include "cpgf/accessor/gaccessor.h"

#include <string>

// The code in this file is intended to be used in script, not in C++.

namespace gincu {

// Doxygen treats it as variable if we expand OnTouchCallback to result type directly
typedef cpgf::GCallback<void (const GEvent &)> OnTouchCallback;
OnTouchCallback createOnTouchedCallback(cpgf::IScriptFunction * func);

typedef cpgf::GAccessor<cpgf::GGetter<cpgf::GCallback<float ()> >, cpgf::GSetter<cpgf::GCallback<void (float)> > > FloatAccessor;
FloatAccessor createFloatAccessor(
		void * instance,
		cpgf::IMetaClass * metaClass,
		const std::string & getterName,
		const std::string & setterName
	);


} //namespace gincu


#endif
