#include "scenemenu.h"

#include "gincu/scripting/gscriptingmain.h"
#include "gincu/scripting/gscriptingutil.h"
#include "gincu/gresourcemanager.h"
#include "gincu/ecs/gentity.h"
#include "gincu/ecs/gcomponenttransform.h"
#include "gincu/gevent.h"
#include "gincu/geventqueue.h"
#include "gincu/gapplication.h"

#include "cpgf/gmetaclass.h"
#include "cpgf/gmetadefine.h"
#include "cpgf/gmetaapi.h"
#include "cpgf/scriptbind/gscriptbindutil.h"
#include "cpgf/gscopedinterface.h"
#include "cpgf/goutmain.h"

#include <memory>
#include <iostream>

using namespace gincu;
using namespace cpgf;
using namespace std;

namespace {

void exitScriptDemo()
{
	SceneMenu::returnToMainMenu();
}

void bindMethod(IScriptObject * scriptObject, const std::string & methodName)
{
	GScopedInterface<IMetaMethod> method(static_cast<IMetaMethod *>(metaItemToInterface(getGlobalMetaClass()->getMethod(methodName.c_str()))));
	scriptSetValue(scriptObject, methodName.c_str(), GScriptValue::fromMethod(NULL, method.get()));
}

void runScriptMain()
{
	GScriptingMain * scriptMain = GScriptingMain::getInstance();
	scriptMain->initialize(GScriptLanguage::slLua);
	
	GScopedInterface<IScriptObject> scriptObject(scriptMain->getScriptObject());
	GScopedInterface<IMetaService> metaService(scriptMain->getService());
	GScopedInterface<IMetaClass> metaClass(metaService->findClassByName("gincu"));
	scriptSetValue(scriptObject.get(), "gincu", GScriptValue::fromClass(metaClass.get()));

	GDefineMetaGlobal()
		._method("exitScriptDemo", &exitScriptDemo)
	;

	bindMethod(scriptObject.get(), "exitScriptDemo");
	
	scriptMain->executeFile("lua/scriptmain.lua");
}

} //unnamed namespace

G_AUTO_RUN_BEFORE_MAIN(ScriptMain)
{
	MenuRegister::getInstance()->registerItem("Script", 3, &runScriptMain, 0xffaaaaff);
}
