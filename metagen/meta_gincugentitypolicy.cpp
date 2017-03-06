// Auto generated file, don't modify.


#include "gincu/ecs/gentitypolicy.h"

#include "meta_gincugentitypolicy.h"

using namespace cpgf;

namespace meta_gincu { 


#ifdef CPGF_METAGEN_LINKAGE_SPEC
CPGF_METAGEN_LINKAGE_SPEC
#endif
GDefineMetaInfo createMetaClass_Global_gentitypolicy()
{
    GDefineMetaGlobalDangle _d = GDefineMetaGlobalDangle::dangle();
    buildMetaClass_Global_gentitypolicy(_d);
    return _d.getMetaInfo();
}


#ifdef CPGF_METAGEN_LINKAGE_SPEC
CPGF_METAGEN_LINKAGE_SPEC
#endif
GDefineMetaInfo createMetaClass_GEntityDynamicArrayBase()
{
    GDefineMetaGlobalDangle _d = GDefineMetaGlobalDangle::dangle();
    {
        GDefineMetaClass<gincu::GEntityDynamicArrayBase> _nd = GDefineMetaClass<gincu::GEntityDynamicArrayBase>::Policy<MakePolicy<GMetaRuleDefaultConstructorAbsent> >::lazyDeclare("GEntityDynamicArrayBase", &buildMetaClass_GEntityDynamicArrayBase);
        _d._class(_nd);
    }
    return _d.getMetaInfo();
}


#ifdef CPGF_METAGEN_LINKAGE_SPEC
CPGF_METAGEN_LINKAGE_SPEC
#endif
GDefineMetaInfo createMetaClass_GEntityDynamicMap()
{
    GDefineMetaGlobalDangle _d = GDefineMetaGlobalDangle::dangle();
    {
        GDefineMetaClass<gincu::GEntityDynamicMap> _nd = GDefineMetaClass<gincu::GEntityDynamicMap>::lazyDeclare("GEntityDynamicMap", &buildMetaClass_GEntityDynamicMap);
        _d._class(_nd);
    }
    return _d.getMetaInfo();
}


} // namespace meta_gincu


