// Auto generated file, don't modify.


#include "gincu/ecs/gentity.h"

#include "meta_gincugentity.h"

using namespace cpgf;

namespace meta_gincu { 


#ifdef CPGF_METAGEN_LINKAGE_SPEC
CPGF_METAGEN_LINKAGE_SPEC
#endif
GDefineMetaInfo createMetaClass_Global_gentity()
{
    GDefineMetaGlobalDangle _d = GDefineMetaGlobalDangle::dangle();
    buildMetaClass_Global_gentity(_d);
    return _d.getMetaInfo();
}


#ifdef CPGF_METAGEN_LINKAGE_SPEC
CPGF_METAGEN_LINKAGE_SPEC
#endif
GDefineMetaInfo createMetaClass_GEntity()
{
    GDefineMetaGlobalDangle _d = GDefineMetaGlobalDangle::dangle();
    {
        GDefineMetaClass<gincu::GEntity> _nd = GDefineMetaClass<gincu::GEntity>::lazyDeclare("GEntity", &buildMetaClass_GEntity);
        _d._class(_nd);
    }
    return _d.getMetaInfo();
}


} // namespace meta_gincu


