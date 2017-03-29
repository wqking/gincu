// Auto generated file, don't modify.

#include "gincu/gincuall.h"
#include "cpgf/metatraits/gmetasharedptrtraits_cpp11_shared_ptr.h"

#include "gincu/ecs/gcomponentmanager.h"

#include "meta_gincugcomponentmanager.h"

using namespace cpgf;

namespace meta_gincu { 


#ifdef CPGF_METAGEN_LINKAGE_SPEC
CPGF_METAGEN_LINKAGE_SPEC
#endif
GDefineMetaInfo createMetaClass_GComponentManager()
{
    GDefineMetaGlobalDangle _d = GDefineMetaGlobalDangle::dangle();
    {
        GDefineMetaClass<gincu::GComponentManager> _nd = GDefineMetaClass<gincu::GComponentManager>::lazyDeclare("GComponentManager", &buildMetaClass_GComponentManager);
        _d._class(_nd);
    }
    return _d.getMetaInfo();
}


} // namespace meta_gincu


