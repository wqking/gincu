#ifndef GSCRIPTINGMETADATA_H
#define GSCRIPTINGMETADATA_H

#include "gincu/gevent.h"

#include "cpgf/gcallback.h"
#include "cpgf/scriptbind/gscriptbindapi.h"

// The code in this file is intended to be used in script, not in C++.

namespace gincu {

// Doxygen treats it as variable if we expand OnTouchCallback to result type directly
typedef cpgf::GCallback<void (const GEvent &)> OnTouchCallback;
OnTouchCallback createOnTouchedCallback(cpgf::IScriptFunction * func);

} //namespace gincu


#endif
