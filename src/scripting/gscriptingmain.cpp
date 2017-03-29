#include "gincu/scripting/gscriptingmain.h"
#include "gincu/scripting/gscriptingutil.h"
#include "gincu/gfileinputstream.h"
#include "gincu/gresourcemanager.h"
#include "gincu/gevent.h"
#include "gincu/geventqueue.h"
#include "gincu/gapplication.h"

#include "cpgf/gscopedinterface.h"
#include "cpgf/scriptbind/gscriptbind.h"

#include <memory>

namespace gincu {

namespace {

std::unique_ptr<GScriptingMain> instance;

} //unnamed namespace

GScriptingMain * GScriptingMain::getInstance()
{
	if(! instance) {
		instance.reset(new GScriptingMain());
		GApplication::getInstance()->getEventQueue()->addListener(GEventType::windowClosed,
			[](const GEvent &) {
				instance.reset();
			}
		);
	}

	return instance.get();
}

GScriptingMain::GScriptingMain()
{
}

GScriptingMain::~GScriptingMain()
{
	finalizeScriptEngine(this->scriptLanguage);
}

void GScriptingMain::initialize(const GScriptLanguage lang)
{
	this->scriptLanguage = lang;

	intializeScriptEngine(lang);
	
	this->runner.reset(createScriptRunner(lang));

	cpgf::GScopedInterface<cpgf::IScriptObject> scriptObject(this->runner->getScripeObject());
	scriptObject->bindCoreService("cpgf", NULL);
}

cpgf::IScriptObject * GScriptingMain::getScriptObject()
{
	return this->runner->getScripeObject();
}

cpgf::IMetaService * GScriptingMain::getService()
{
	return this->runner->getService();
}

void GScriptingMain::executeString(const std::string & code)
{
	this->runner->executeString(code.c_str());
}

void GScriptingMain::executeFile(const std::string & fileName)
{
	GFileInputStream stream(GResourceManager::getInstance()->solveResourcePath(fileName));
	auto size = stream.getSize();
	if(size == 0) {
		return;
	}

	std::string code(size, 0);
	stream.read(&code[0], size);
	this->executeString(code);
}


} //namespace gincu

