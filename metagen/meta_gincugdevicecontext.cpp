// Auto generated file, don't modify.

#include "gincu/gincuall.h"
#include "cpgf/metatraits/gmetasharedptrtraits_cpp11_shared_ptr.h"
#include "gincu/gdevicecontext.h"

#include "meta_gincugdevicecontext.h"

using namespace cpgf;

namespace meta_gincu { 


#ifdef CPGF_METAGEN_LINKAGE_SPEC
CPGF_METAGEN_LINKAGE_SPEC
#endif
GDefineMetaInfo createMetaClass_GDeviceContext()
{
    GDefineMetaGlobalDangle _d = GDefineMetaGlobalDangle::dangle();
    {
        GDefineMetaClass<gincu::GDeviceContext> _nd = GDefineMetaClass<gincu::GDeviceContext>::Policy<MakePolicy<GMetaRuleDefaultConstructorAbsent, GMetaRuleCopyConstructorAbsent> >::lazyDeclare("GDeviceContext", &buildMetaClass_GDeviceContext);
        _d._class(_nd);
    }
    return _d.getMetaInfo();
}


#ifdef CPGF_METAGEN_LINKAGE_SPEC
CPGF_METAGEN_LINKAGE_SPEC
#endif
GDefineMetaInfo createMetaClass_GDeviceContextRegister()
{
    GDefineMetaGlobalDangle _d = GDefineMetaGlobalDangle::dangle();
    {
        GDefineMetaClass<gincu::GDeviceContextRegister, gincu::GObjectFactory< GDeviceContext >> _nd = GDefineMetaClass<gincu::GDeviceContextRegister, gincu::GObjectFactory< GDeviceContext >>::lazyDeclare("GDeviceContextRegister", &buildMetaClass_GDeviceContextRegister);
        _d._class(_nd);
    }
    return _d.getMetaInfo();
}


} // namespace meta_gincu


