// Auto generated file, don't modify.


#include "gincu/gobjectfactory.h"

#include "meta_gincugobjectfactory.h"

using namespace cpgf;

namespace meta_gincu { 


#ifdef CPGF_METAGEN_LINKAGE_SPEC
CPGF_METAGEN_LINKAGE_SPEC
#endif
GDefineMetaInfo createMetaClass_Global_gobjectfactory()
{
    GDefineMetaGlobalDangle _d = GDefineMetaGlobalDangle::dangle();
    buildMetaClass_Global_gobjectfactory(_d);
    return _d.getMetaInfo();
}


#ifdef CPGF_METAGEN_LINKAGE_SPEC
CPGF_METAGEN_LINKAGE_SPEC
#endif
GDefineMetaInfo createMetaClass_GObjectFactoryBase()
{
    GDefineMetaGlobalDangle _d = GDefineMetaGlobalDangle::dangle();
    {
        GDefineMetaClass<gincu::GObjectFactoryBase> _nd = GDefineMetaClass<gincu::GObjectFactoryBase>::lazyDeclare("GObjectFactoryBase", &buildMetaClass_GObjectFactoryBase);
        _d._class(_nd);
    }
    return _d.getMetaInfo();
}


} // namespace meta_gincu


