// Auto generated file, don't modify.

#include "gincu/gincuall.h"

#include "gincu/gapplication.h"

#include "meta_gincugapplication.h"

using namespace cpgf;

namespace meta_gincu { 


#ifdef CPGF_METAGEN_LINKAGE_SPEC
CPGF_METAGEN_LINKAGE_SPEC
#endif
GDefineMetaInfo createMetaClass_GApplication()
{
    GDefineMetaGlobalDangle _d = GDefineMetaGlobalDangle::dangle();
    {
        GDefineMetaClass<gincu::GApplication> _nd = GDefineMetaClass<gincu::GApplication>::lazyDeclare("GApplication", &buildMetaClass_GApplication);
        _d._class(_nd);
    }
    {
        GDefineMetaClass<GApplicationWrapper, gincu::GApplication> _nd = GDefineMetaClass<GApplicationWrapper, gincu::GApplication>::lazyDeclare("GApplicationWrapper", &buildMetaClass_GApplicationWrapper);
        _d._class(_nd);
    }
    return _d.getMetaInfo();
}


} // namespace meta_gincu


