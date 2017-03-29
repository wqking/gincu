#ifndef GSCRIPTINGMAIN_H
#define GSCRIPTINGMAIN_H

#include "cpgf/scriptbind/gscriptrunner.h"
#include "cpgf/scriptbind/gscriptbindapi.h"
#include "cpgf/gmetaapi.h"

#include <memory>
#include <string>

namespace gincu {

enum class GScriptLanguage;

class GScriptingMain
{
public:
	static GScriptingMain * getInstance();

private:
	GScriptingMain();

public:
	~GScriptingMain();
	
	void initialize(const GScriptLanguage lang);

	cpgf::IScriptObject * getScripeObject();
	cpgf::IMetaService * getService();
	
	void executeString(const std::string & code);
	void executeFile(const std::string & fileName);

private:
	GScriptLanguage scriptLanguage;
	std::unique_ptr<cpgf::GScriptRunner> runner;
};


} //namespace gincu



#endif

