#include "scriptmain.h"
#include "scripthelper.h"
#include "scenemenu.h"

#include "gincu/gresourcemanager.h"

#include "cpgf/gmetaapi.h"
#include "cpgf/scriptbind/gscriptbindutil.h"
#include "cpgf/gscopedinterface.h"
#include "cpgf/goutmain.h"

#include <memory>

using namespace gincu;
using namespace cpgf;

namespace {

std::unique_ptr<ScriptMain> scriptMain;

} //unnamed namespace

void ScriptMain::runScript()
{
	scriptMain.reset(new ScriptMain());
	scriptMain->run();
}

ScriptMain::ScriptMain()
{
}

ScriptMain::~ScriptMain()
{
}

void ScriptMain::run()
{
	std::string scriptFileName = GResourceManager::getInstance()->solveResourcePath("lua/scriptmain.lua");
	char * argv[] = {
		(char *)"",
		(char *)scriptFileName.c_str()
	};

	this->scriptHelper.reset(new ScriptHelper(sizeof(argv) / sizeof(argv[0]), argv));
	
	GScopedInterface<IMetaClass> metaClass(this->scriptHelper->borrowService()->findClassByName("gincu"));
	//this->scriptHelper->borrowScriptObject()->bindCoreService("cpgf", NULL);
	scriptSetValue(this->scriptHelper->borrowScriptObject(), "gincu", GScriptValue::fromClass(metaClass.get()));

	this->scriptHelper->execute();
}

G_AUTO_RUN_BEFORE_MAIN(ScriptMain)
{
	MenuRegister::getInstance()->registerItem("Script", 3, [](){
			ScriptMain::runScript();
		},
		0xffaaaaff);
}
