// Auto generated file, don't modify.

#include "gincu/gincuall.h"

#include "gincu/grenderinfo.h"

#include "meta_gincugrenderinfo.h"

using namespace cpgf;

namespace meta_gincu { 


#ifdef CPGF_METAGEN_LINKAGE_SPEC
CPGF_METAGEN_LINKAGE_SPEC
#endif
GDefineMetaInfo createMetaClass_Global_grenderinfo()
{
    GDefineMetaGlobalDangle _d = GDefineMetaGlobalDangle::dangle();
    buildMetaClass_Global_grenderinfo(_d);
    return _d.getMetaInfo();
}


#ifdef CPGF_METAGEN_LINKAGE_SPEC
CPGF_METAGEN_LINKAGE_SPEC
#endif
GDefineMetaInfo createMetaClass_GRenderInfo()
{
    GDefineMetaGlobalDangle _d = GDefineMetaGlobalDangle::dangle();
    {
        GDefineMetaClass<gincu::GRenderInfo> _nd = GDefineMetaClass<gincu::GRenderInfo>::lazyDeclare("GRenderInfo", &buildMetaClass_GRenderInfo);
        _d._class(_nd);
    }
    return _d.getMetaInfo();
}


} // namespace meta_gincu


