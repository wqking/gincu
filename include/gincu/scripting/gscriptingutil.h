#ifndef GSCRIPTINGUTIL_H
#define GSCRIPTINGUTIL_H

#include "cpgf/scriptbind/gscriptrunner.h"
#include "cpgf/gmetaapi.h"

namespace gincu {

enum class GScriptLanguage {
	slV8Javascript,
	slSpiderMonkeyJavaScript,
	slLua,
	slPython
};

void intializeScriptEngine(const GScriptLanguage lang);
void finalizeScriptEngine(const GScriptLanguage lang);

cpgf::GScriptRunner * createScriptRunner(const GScriptLanguage lang);


} //namespace gincu



#endif

