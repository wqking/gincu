#include "gincu/scripting/gscriptingmetadata.h"

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

cpgf::GCallback<void (const GEvent &)> createOnTouchedCallback(cpgf::IScriptFunction * func)
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
		void * instance,
		cpgf::IMetaClass * metaClass,
		const std::string & getterName,
		const std::string & setterName
	)
{
	void * getterInstance = instance;
	void * setterInstance = instance;
	cpgf::GScopedInterface<cpgf::IMetaMethod> getter(metaClass->getMethodInHierarchy(getterName.c_str(), &getterInstance));
	cpgf::GScopedInterface<cpgf::IMetaMethod> setter(metaClass->getMethodInHierarchy(setterName.c_str(), &setterInstance));

	return cpgf::createAccessor(
		cpgf::createGetter(instance, cpgf::GCallback<T ()>(MetaGetterSetter<T>(getterInstance, getter.get()))),
		cpgf::createSetter(instance, cpgf::GCallback<void (T)>(MetaGetterSetter<T>(setterInstance, setter.get())))
	);
}

FloatAccessor createFloatAccessor(
		void * instance,
		cpgf::IMetaClass * metaClass,
		const std::string & getterName,
		const std::string & setterName
	)
{
	return createMetaAccessor<float>(instance, metaClass, getterName, setterName);
}


} //namespace gincu
