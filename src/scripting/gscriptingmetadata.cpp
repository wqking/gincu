#include "gincu/scripting/gscriptingmetadata.h"
#include "gincu/scripting/gscriptingmain.h"
#include "gincu/gerrorhandler.h"

#include "cpgf/gsharedinterface.h"
#include "cpgf/gscopedinterface.h"
#include "cpgf/scriptbind/gscriptbindutil.h"

namespace gincu {

namespace {

template <typename RT>
struct ScriptCallback
{
	explicit ScriptCallback(cpgf::IScriptFunction * func) : func(func) {
	}
	
	template <typename... Parameters>
	RT operator() (Parameters && ... parameters) const
	{
		cpgf::invokeScriptFunction(this->func.get(), std::forward<Parameters>(parameters)...);
		return RT();
	}
	
	cpgf::GSharedInterface<cpgf::IScriptFunction> func;
};

} //unnamed namespace

OnTouchCallback createOnTouchedCallback(cpgf::IScriptFunction * func)
{
	return cpgf::GCallback<void (const GEvent &)>(ScriptCallback<void>(func));
}


typedef cpgf::GAccessor<cpgf::GGetter<cpgf::GCallback<float ()> >, cpgf::GSetter<cpgf::GCallback<void (float)> > > FloatAccessor;

template <typename T>
struct MetaGetterSetter
{
	MetaGetterSetter(void * instance, cpgf::IMetaMethod * method)
		:
			instance(instance),
			method(method)
	{
	}
	
	T operator() () const {
		return cpgf::fromVariant<T>(cpgf::metaInvokeMethod(this->method.get(), this->instance));
	}
	
	void operator() (const T & value) const {
		cpgf::metaInvokeMethod(this->method.get(), this->instance, value);
	}
	
	void * instance;
	cpgf::GSharedInterface<cpgf::IMetaMethod> method;
};

template <typename T>
cpgf::GAccessor<cpgf::GGetter<cpgf::GCallback<T ()> >, cpgf::GSetter<cpgf::GCallback<void (T)> > >
createMetaAccessor(
		const cpgf::GVariant & instance,
		const std::string & getterName,
		const std::string & setterName
	)
{
	cpgf::GScopedInterface<cpgf::IMetaClass> metaClass(GScriptingMain::getInstance()->getInstanceMetaClass(instance));
	if(! metaClass) {
		handleFatal("createMetaAccessor: can't find meta class.");
	}

	void * instanceAddress = cpgf::fromVariant<void *>(instance);
	void * getterInstance = instanceAddress;
	void * setterInstance = instanceAddress;

	cpgf::GScopedInterface<cpgf::IMetaMethod> getter(metaClass->getMethodInHierarchy(getterName.c_str(), &getterInstance));
	if(! getter) {
		handleFatal("createMetaAccessor: can't find getter method " + getterName);
	}

	cpgf::GScopedInterface<cpgf::IMetaMethod> setter(metaClass->getMethodInHierarchy(setterName.c_str(), &setterInstance));
	if(! setter) {
		handleFatal("createMetaAccessor: can't find setter method " + setterName);
	}

	return cpgf::createAccessor(
		cpgf::createGetter(getterInstance, cpgf::GCallback<T ()>(MetaGetterSetter<T>(getterInstance, getter.get()))),
		cpgf::createSetter(setterInstance, cpgf::GCallback<void (T)>(MetaGetterSetter<T>(setterInstance, setter.get())))
	);
}

FloatAccessor createFloatAccessor(
		const cpgf::GVariant & instance,
		const std::string & getterName,
		const std::string & setterName
	)
{
	return createMetaAccessor<float>(instance, getterName, setterName);
}

struct MetaInstanceDeleter
{
	explicit MetaInstanceDeleter(cpgf::IMetaClass * metaClass)
		: metaClass(metaClass)
	{
	}
	
	void operator() (void * p)
	{
		this->metaClass->destroyInstance(p);
	}
	
	cpgf::GSharedInterface<cpgf::IMetaClass> metaClass;
};

std::shared_ptr<void> createSharedPointer(const cpgf::GVariant & instance)
{
	cpgf::GScopedInterface<cpgf::IMetaClass> metaClass(GScriptingMain::getInstance()->getInstanceMetaClass(instance));
	if(! metaClass) {
		handleFatal("createMetaAccessor: can't find meta class.");
	}

	cpgf::GScopedInterface<cpgf::IScriptObject> scriptObject(GScriptingMain::getInstance()->getScriptObject());
	cpgf::GScopedInterface<cpgf::IScriptContext> context(scriptObject->getContext());
	context->setAllowGC(&instance.refData(), false);
	
	return std::shared_ptr<void>(cpgf::fromVariant<void *>(instance), MetaInstanceDeleter(metaClass.get()));
}


} //namespace gincu
