// Auto generated file, don't modify.

#include "gincu/gincuall.h"
#include "cpgf/metatraits/gmetasharedptrtraits_cpp11_shared_ptr.h"
#include "gincu/gscene.h"

#include "meta_gincugscene.h"

using namespace cpgf;

namespace meta_gincu { 


#ifdef CPGF_METAGEN_LINKAGE_SPEC
CPGF_METAGEN_LINKAGE_SPEC
#endif
GDefineMetaInfo createMetaClass_Global_gscene()
{
    GDefineMetaGlobalDangle _d = GDefineMetaGlobalDangle::dangle();
    buildMetaClass_Global_gscene(_d);
    return _d.getMetaInfo();
}


#ifdef CPGF_METAGEN_LINKAGE_SPEC
CPGF_METAGEN_LINKAGE_SPEC
#endif
GDefineMetaInfo createMetaClass_GScene()
{
    GDefineMetaGlobalDangle _d = GDefineMetaGlobalDangle::dangle();
    {
        GDefineMetaClass<gincu::GScene> _nd = GDefineMetaClass<gincu::GScene>::lazyDeclare("GScene", &buildMetaClass_GScene);
        _d._class(_nd);
    }
    {
        GDefineMetaClass<GSceneWrapper, gincu::GScene> _nd = GDefineMetaClass<GSceneWrapper, gincu::GScene>::lazyDeclare("GSceneWrapper", &buildMetaClass_GSceneWrapper);
        _d._class(_nd);
    }
    return _d.getMetaInfo();
}


} // namespace meta_gincu


