// Auto generated file, don't modify.

#include "gincu/gincuall.h"

#include "gincu/gvertexarray.h"

#include "meta_gincugvertexarray.h"

using namespace cpgf;

namespace meta_gincu { 


#ifdef CPGF_METAGEN_LINKAGE_SPEC
CPGF_METAGEN_LINKAGE_SPEC
#endif
GDefineMetaInfo createMetaClass_GVertexArray()
{
    GDefineMetaGlobalDangle _d = GDefineMetaGlobalDangle::dangle();
    {
        GDefineMetaClass<gincu::GVertexArray> _nd = GDefineMetaClass<gincu::GVertexArray>::lazyDeclare("GVertexArray", &buildMetaClass_GVertexArray);
        _d._class(_nd);
    }
    return _d.getMetaInfo();
}


#ifdef CPGF_METAGEN_LINKAGE_SPEC
CPGF_METAGEN_LINKAGE_SPEC
#endif
GDefineMetaInfo createMetaClass_GVertexArrayData()
{
    GDefineMetaGlobalDangle _d = GDefineMetaGlobalDangle::dangle();
    {
        GDefineMetaClass<gincu::GVertexArrayData> _nd = GDefineMetaClass<gincu::GVertexArrayData>::Policy<MakePolicy<GMetaRuleDefaultConstructorAbsent, GMetaRuleCopyConstructorAbsent> >::lazyDeclare("GVertexArrayData", &buildMetaClass_GVertexArrayData);
        _d._class(_nd);
    }
    return _d.getMetaInfo();
}


} // namespace meta_gincu


