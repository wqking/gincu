#include "gincu/scripting/gscriptingutil.h"

#include "cpgf/gscopedinterface.h"

#if ENABLE_LUA
	#include "cpgf/scriptbind/gluarunner.h"
#endif

#if ENABLE_V8
	#include "cpgf/scriptbind/gv8runner.h"
#endif

#if ENABLE_PYTHON
	#include "cpgf/scriptbind/gpythonrunner.h"
	#include "Python.h"
#endif

#if ENABLE_SPIDERMONKEY
	#include "cpgf/scriptbind/gspidermonkeyrunner.h"
#endif

using namespace cpgf;

namespace gincu {

namespace {

GScriptRunner * doCreateScriptRunnerFromScriptLanguage(const GScriptLanguage lang, IMetaService * service)
{
	switch(lang) {
		case GScriptLanguage::slV8Javascript:
#if ENABLE_V8
			return createV8ScriptRunner(service);
#endif
			break;
		
		case GScriptLanguage::slSpiderMonkeyJavaScript:
#if ENABLE_SPIDERMONKEY
			return createSpiderMonkeyScriptRunner(service);
#endif
			break;
		
		case GScriptLanguage::slLua:
#if ENABLE_LUA
			return createLuaScriptRunner(service);
#endif
			break;

		case GScriptLanguage::slPython:
#if ENABLE_PYTHON
			return createPythonScriptRunner(service);
#endif
			break;
	}

	return NULL;
}

const char * getLanguageText(const GScriptLanguage lang)
{
	switch(lang) {
		case GScriptLanguage::slV8Javascript:
			return "V8 Javascript";
		
		case GScriptLanguage::slSpiderMonkeyJavaScript:
			return "SpiderMonkey Javascript";
		
		case GScriptLanguage::slLua:
			return "Lua";

		case GScriptLanguage::slPython:
			return "Python";
	}

	return "Unknown";
}

} //unnamed namespace

void intializeScriptEngine(const GScriptLanguage lang)
{
	switch(lang) {
		case GScriptLanguage::slV8Javascript:
			break;
		
		case GScriptLanguage::slSpiderMonkeyJavaScript:
			break;

		case GScriptLanguage::slLua:
			break;

		case GScriptLanguage::slPython:
#if ENABLE_PYTHON
			Py_Initialize();
#endif
			break;
	}
}

void finalizeScriptEngine(const GScriptLanguage lang)
{
	switch(lang) {
		case GScriptLanguage::slV8Javascript:
			break;
		
		case GScriptLanguage::slSpiderMonkeyJavaScript:
			break;

		case GScriptLanguage::slLua:
			break;

		case GScriptLanguage::slPython:
#if ENABLE_PYTHON
			Py_Finalize();
#endif
			break;
	}
}

cpgf::GScriptRunner * createScriptRunner(const GScriptLanguage lang)
{
	GScopedInterface<IMetaService> metaSevice(createDefaultMetaService());
	return doCreateScriptRunnerFromScriptLanguage(lang, metaSevice.get());
}

} //namespace gincu
