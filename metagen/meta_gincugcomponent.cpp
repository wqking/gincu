// Auto generated file, don't modify.

#include "gincu/gincuall.h"
#include "cpgf/metatraits/gmetasharedptrtraits_cpp11_shared_ptr.h"

#include "gincu/ecs/gcomponent.h"

#include "meta_gincugcomponent.h"

using namespace cpgf;

namespace meta_gincu { 


#ifdef CPGF_METAGEN_LINKAGE_SPEC
CPGF_METAGEN_LINKAGE_SPEC
#endif
GDefineMetaInfo createMetaClass_Global_gcomponent()
{
    GDefineMetaGlobalDangle _d = GDefineMetaGlobalDangle::dangle();
    buildMetaClass_Global_gcomponent(_d);
    return _d.getMetaInfo();
}


#ifdef CPGF_METAGEN_LINKAGE_SPEC
CPGF_METAGEN_LINKAGE_SPEC
#endif
GDefineMetaInfo createMetaClass_GComponent()
{
    GDefineMetaGlobalDangle _d = GDefineMetaGlobalDangle::dangle();
    {
        GDefineMetaClass<gincu::GComponent> _nd = GDefineMetaClass<gincu::GComponent>::Policy<MakePolicy<GMetaRuleDefaultConstructorAbsent> >::lazyDeclare("GComponent", &buildMetaClass_GComponent);
        _d._class(_nd);
    }
    {
        GDefineMetaClass<GComponentWrapper, gincu::GComponent> _nd = GDefineMetaClass<GComponentWrapper, gincu::GComponent>::Policy<MakePolicy<GMetaRuleDefaultConstructorAbsent> >::lazyDeclare("GComponentWrapper", &buildMetaClass_GComponentWrapper);
        _d._class(_nd);
    }
    return _d.getMetaInfo();
}


#ifdef CPGF_METAGEN_LINKAGE_SPEC
CPGF_METAGEN_LINKAGE_SPEC
#endif
GDefineMetaInfo createMetaClass_GComponentIdRegister()
{
    GDefineMetaGlobalDangle _d = GDefineMetaGlobalDangle::dangle();
    {
        GDefineMetaClass<gincu::GComponentIdRegister> _nd = GDefineMetaClass<gincu::GComponentIdRegister>::Policy<MakePolicy<GMetaRuleDefaultConstructorAbsent> >::lazyDeclare("GComponentIdRegister", &buildMetaClass_GComponentIdRegister);
        _d._class(_nd);
    }
    return _d.getMetaInfo();
}


} // namespace meta_gincu


