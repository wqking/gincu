// Auto generated file, don't modify.

#include "gincu/gincuall.h"
#include "cpgf/metatraits/gmetasharedptrtraits_cpp11_shared_ptr.h"
#include "cpgf/tween/gtimeline.h"

#include "gincu/gstate.h"

#include "meta_gincugstate.h"

using namespace cpgf;

namespace meta_gincu { 


#ifdef CPGF_METAGEN_LINKAGE_SPEC
CPGF_METAGEN_LINKAGE_SPEC
#endif
GDefineMetaInfo createMetaClass_Global_gstate()
{
    GDefineMetaGlobalDangle _d = GDefineMetaGlobalDangle::dangle();
    buildMetaClass_Global_gstate(_d);
    return _d.getMetaInfo();
}


#ifdef CPGF_METAGEN_LINKAGE_SPEC
CPGF_METAGEN_LINKAGE_SPEC
#endif
GDefineMetaInfo createMetaClass_GState()
{
    GDefineMetaGlobalDangle _d = GDefineMetaGlobalDangle::dangle();
    {
        GDefineMetaClass<gincu::GState> _nd = GDefineMetaClass<gincu::GState>::Policy<MakePolicy<GMetaRuleDefaultConstructorAbsent> >::lazyDeclare("GState", &buildMetaClass_GState);
        _d._class(_nd);
    }
    return _d.getMetaInfo();
}


} // namespace meta_gincu


