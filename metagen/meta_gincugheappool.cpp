// Auto generated file, don't modify.


#include "gincu/gheappool.h"

#include "meta_gincugheappool.h"

using namespace cpgf;

namespace meta_gincu { 


#ifdef CPGF_METAGEN_LINKAGE_SPEC
CPGF_METAGEN_LINKAGE_SPEC
#endif
GDefineMetaInfo createMetaClass_Global_gheappool()
{
    GDefineMetaGlobalDangle _d = GDefineMetaGlobalDangle::dangle();
    buildMetaClass_Global_gheappool(_d);
    return _d.getMetaInfo();
}


#ifdef CPGF_METAGEN_LINKAGE_SPEC
CPGF_METAGEN_LINKAGE_SPEC
#endif
GDefineMetaInfo createMetaClass_GHeapPool()
{
    GDefineMetaGlobalDangle _d = GDefineMetaGlobalDangle::dangle();
    {
        GDefineMetaClass<gincu::GHeapPool> _nd = GDefineMetaClass<gincu::GHeapPool>::Policy<MakePolicy<GMetaRuleDefaultConstructorAbsent> >::lazyDeclare("GHeapPool", &buildMetaClass_GHeapPool);
        _d._class(_nd);
    }
    return _d.getMetaInfo();
}


#ifdef CPGF_METAGEN_LINKAGE_SPEC
CPGF_METAGEN_LINKAGE_SPEC
#endif
GDefineMetaInfo createMetaClass_GHeapSizedPool()
{
    GDefineMetaGlobalDangle _d = GDefineMetaGlobalDangle::dangle();
    {
        GDefineMetaClass<gincu::GHeapSizedPool> _nd = GDefineMetaClass<gincu::GHeapSizedPool>::Policy<MakePolicy<GMetaRuleDefaultConstructorAbsent> >::lazyDeclare("GHeapSizedPool", &buildMetaClass_GHeapSizedPool);
        _d._class(_nd);
    }
    return _d.getMetaInfo();
}


} // namespace meta_gincu


