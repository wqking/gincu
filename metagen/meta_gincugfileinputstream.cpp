// Auto generated file, don't modify.

#include "gincu/gincuall.h"
#include "cpgf/metatraits/gmetasharedptrtraits_cpp11_shared_ptr.h"

#include "gincu/gfileinputstream.h"

#include "meta_gincugfileinputstream.h"

using namespace cpgf;

namespace meta_gincu { 


#ifdef CPGF_METAGEN_LINKAGE_SPEC
CPGF_METAGEN_LINKAGE_SPEC
#endif
GDefineMetaInfo createMetaClass_GFileInputStream()
{
    GDefineMetaGlobalDangle _d = GDefineMetaGlobalDangle::dangle();
    {
        GDefineMetaClass<gincu::GFileInputStream> _nd = GDefineMetaClass<gincu::GFileInputStream>::lazyDeclare("GFileInputStream", &buildMetaClass_GFileInputStream);
        _d._class(_nd);
    }
    return _d.getMetaInfo();
}


#ifdef CPGF_METAGEN_LINKAGE_SPEC
CPGF_METAGEN_LINKAGE_SPEC
#endif
GDefineMetaInfo createMetaClass_GFileInputStreamData()
{
    GDefineMetaGlobalDangle _d = GDefineMetaGlobalDangle::dangle();
    {
        GDefineMetaClass<gincu::GFileInputStreamData> _nd = GDefineMetaClass<gincu::GFileInputStreamData>::Policy<MakePolicy<GMetaRuleDefaultConstructorAbsent, GMetaRuleCopyConstructorAbsent> >::lazyDeclare("GFileInputStreamData", &buildMetaClass_GFileInputStreamData);
        _d._class(_nd);
    }
    return _d.getMetaInfo();
}


} // namespace meta_gincu


