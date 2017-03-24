#include "scriptmain.h"
#include "scripthelper.h"
#include "scenemenu.h"

#include "gincu/gresourcemanager.h"
#include "gincu/ecs/gentity.h"
#include "gincu/ecs/gcomponenttransform.h"
#include "gincu/gevent.h"

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

std::unique_ptr<ScriptMain> scriptMain;

template <typename RT>
struct ScriptCallback
{
	explicit ScriptCallback(IScriptFunction * func) : func(func) {
	}
	
	template <typename... Parameters>
	RT operator() (Parameters && ... parameters) const
	{
		invokeScriptFunction(this->func.get(), std::forward<Parameters>(parameters)...);
		return RT();
	}
	
	GSharedInterface<IScriptFunction> func;
};

cpgf::GCallback<void (const GEvent &)> createOnTouchedCallback(IScriptFunction * func)
{
	return cpgf::GCallback<void (const GEvent &)>(ScriptCallback<void>(func));
}

GEntity * createEntity()
{
	GEntity * entity = new GEntity();
	entity->addComponent(createComponent<GComponentTransform>());
	return entity;
}

void doTest(const GComponentTransform * transform)
{
	cout << transform->getTransform().toDebugString() << endl;
}

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

	GDefineMetaGlobal()
		._method("createEntity", &createEntity)
		._method("doTest", &doTest)
		._method("createOnTouchedCallback", &createOnTouchedCallback)
	;

	this->doBindMethod("createEntity");
	this->doBindMethod("doTest");
	this->doBindMethod("createOnTouchedCallback");

	this->scriptHelper->execute();
}

void ScriptMain::doBindMethod(const std::string & methodName)
{
	GScopedInterface<IMetaMethod> method(static_cast<IMetaMethod *>(metaItemToInterface(getGlobalMetaClass()->getMethod(methodName.c_str()))));
	scriptSetValue(this->scriptHelper->borrowScriptObject(), methodName.c_str(), GScriptValue::fromMethod(NULL, method.get()));
}


G_AUTO_RUN_BEFORE_MAIN(ScriptMain)
{
	MenuRegister::getInstance()->registerItem("Script", 3, [](){
			ScriptMain::runScript();
		},
		0xffaaaaff);
}
