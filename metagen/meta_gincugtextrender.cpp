// Auto generated file, don't modify.

#include "gincu/gincuall.h"
#include "cpgf/metatraits/gmetasharedptrtraits_cpp11_shared_ptr.h"
#include "gincu/gtextrender.h"

#include "meta_gincugtextrender.h"

using namespace cpgf;

namespace meta_gincu { 


#ifdef CPGF_METAGEN_LINKAGE_SPEC
CPGF_METAGEN_LINKAGE_SPEC
#endif
GDefineMetaInfo createMetaClass_Global_gtextrender()
{
    GDefineMetaGlobalDangle _d = GDefineMetaGlobalDangle::dangle();
    buildMetaClass_Global_gtextrender(_d);
    return _d.getMetaInfo();
}


#ifdef CPGF_METAGEN_LINKAGE_SPEC
CPGF_METAGEN_LINKAGE_SPEC
#endif
GDefineMetaInfo createMetaClass_GTextRender()
{
    GDefineMetaGlobalDangle _d = GDefineMetaGlobalDangle::dangle();
    {
        GDefineMetaClass<gincu::GTextRender> _nd = GDefineMetaClass<gincu::GTextRender>::lazyDeclare("GTextRender", &buildMetaClass_GTextRender);
        _d._class(_nd);
    }
    return _d.getMetaInfo();
}


#ifdef CPGF_METAGEN_LINKAGE_SPEC
CPGF_METAGEN_LINKAGE_SPEC
#endif
GDefineMetaInfo createMetaClass_GTextRenderData()
{
    GDefineMetaGlobalDangle _d = GDefineMetaGlobalDangle::dangle();
    {
        GDefineMetaClass<gincu::GTextRenderData> _nd = GDefineMetaClass<gincu::GTextRenderData>::Policy<MakePolicy<GMetaRuleDefaultConstructorAbsent, GMetaRuleCopyConstructorAbsent> >::lazyDeclare("GTextRenderData", &buildMetaClass_GTextRenderData);
        _d._class(_nd);
    }
    return _d.getMetaInfo();
}


} // namespace meta_gincu


