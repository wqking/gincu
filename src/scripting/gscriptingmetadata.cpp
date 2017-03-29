#include "gincu/scripting/gscriptingmetadata.h"

#include "cpgf/gsharedinterface.h"
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


} //namespace gincu
