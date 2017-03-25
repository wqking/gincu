// Auto generated file, don't modify.

#include "gincu/gincuall.h"
#include "cpgf/metatraits/gmetasharedptrtraits_cpp11_shared_ptr.h"
#include "gincu/gatlasrender.h"

#include "meta_gincugatlasrender.h"

using namespace cpgf;

namespace meta_gincu { 


#ifdef CPGF_METAGEN_LINKAGE_SPEC
CPGF_METAGEN_LINKAGE_SPEC
#endif
GDefineMetaInfo createMetaClass_Global_gatlasrender()
{
    GDefineMetaGlobalDangle _d = GDefineMetaGlobalDangle::dangle();
    buildMetaClass_Global_gatlasrender(_d);
    return _d.getMetaInfo();
}


#ifdef CPGF_METAGEN_LINKAGE_SPEC
CPGF_METAGEN_LINKAGE_SPEC
#endif
GDefineMetaInfo createMetaClass_GAtlasRender()
{
    GDefineMetaGlobalDangle _d = GDefineMetaGlobalDangle::dangle();
    {
        GDefineMetaClass<gincu::GAtlasRender> _nd = GDefineMetaClass<gincu::GAtlasRender>::lazyDeclare("GAtlasRender", &buildMetaClass_GAtlasRender);
        _d._class(_nd);
    }
    return _d.getMetaInfo();
}


} // namespace meta_gincu


