// Auto generated file, don't modify.

#include "gincu/gincuall.h"
#include "cpgf/metatraits/gmetasharedptrtraits_cpp11_shared_ptr.h"

#include "gincu/ecs/gcomponentrender.h"

#include "meta_gincugcomponentrender.h"

using namespace cpgf;

namespace meta_gincu { 


#ifdef CPGF_METAGEN_LINKAGE_SPEC
CPGF_METAGEN_LINKAGE_SPEC
#endif
GDefineMetaInfo createMetaClass_Global_gcomponentrender()
{
    GDefineMetaGlobalDangle _d = GDefineMetaGlobalDangle::dangle();
    buildMetaClass_Global_gcomponentrender(_d);
    return _d.getMetaInfo();
}


#ifdef CPGF_METAGEN_LINKAGE_SPEC
CPGF_METAGEN_LINKAGE_SPEC
#endif
GDefineMetaInfo createMetaClass_GComponentContainerRender()
{
    GDefineMetaGlobalDangle _d = GDefineMetaGlobalDangle::dangle();
    {
        GDefineMetaClass<gincu::GComponentContainerRender, gincu::GComponentRender> _nd = GDefineMetaClass<gincu::GComponentContainerRender, gincu::GComponentRender>::lazyDeclare("GComponentContainerRender", &buildMetaClass_GComponentContainerRender);
        _d._class(_nd);
    }
    return _d.getMetaInfo();
}


#ifdef CPGF_METAGEN_LINKAGE_SPEC
CPGF_METAGEN_LINKAGE_SPEC
#endif
GDefineMetaInfo createMetaClass_GComponentRender()
{
    GDefineMetaGlobalDangle _d = GDefineMetaGlobalDangle::dangle();
    {
        GDefineMetaClass<gincu::GComponentRender, gincu::GComponent> _nd = GDefineMetaClass<gincu::GComponentRender, gincu::GComponent>::Policy<MakePolicy<GMetaRuleDefaultConstructorAbsent, GMetaRuleCopyConstructorAbsent> >::lazyDeclare("GComponentRender", &buildMetaClass_GComponentRender);
        _d._class(_nd);
    }
    return _d.getMetaInfo();
}


#ifdef CPGF_METAGEN_LINKAGE_SPEC
CPGF_METAGEN_LINKAGE_SPEC
#endif
GDefineMetaInfo createMetaClass_GComponentVertexArrayRender()
{
    GDefineMetaGlobalDangle _d = GDefineMetaGlobalDangle::dangle();
    {
        GDefineMetaClass<gincu::GComponentVertexArrayRender, gincu::GComponentRenderCommon< GVertexArrayRender >> _nd = GDefineMetaClass<gincu::GComponentVertexArrayRender, gincu::GComponentRenderCommon< GVertexArrayRender >>::lazyDeclare("GComponentVertexArrayRender", &buildMetaClass_GComponentVertexArrayRender);
        _d._class(_nd);
    }
    return _d.getMetaInfo();
}


} // namespace meta_gincu


