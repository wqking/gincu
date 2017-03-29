// Auto generated file, don't modify.

#include "gincu/gincuall.h"
#include "cpgf/metatraits/gmetasharedptrtraits_cpp11_shared_ptr.h"
#include "cpgf/tween/gtimeline.h"

#include "gincu/ecs/gcomponenttouchhandler.h"

#include "meta_gincugcomponenttouchhandler.h"

using namespace cpgf;

namespace meta_gincu { 


#ifdef CPGF_METAGEN_LINKAGE_SPEC
CPGF_METAGEN_LINKAGE_SPEC
#endif
GDefineMetaInfo createMetaClass_GComponentRendererTouchHandler()
{
    GDefineMetaGlobalDangle _d = GDefineMetaGlobalDangle::dangle();
    {
        GDefineMetaClass<gincu::GComponentRendererTouchHandler, gincu::GComponentTouchHandler> _nd = GDefineMetaClass<gincu::GComponentRendererTouchHandler, gincu::GComponentTouchHandler>::lazyDeclare("GComponentRendererTouchHandler", &buildMetaClass_GComponentRendererTouchHandler);
        _d._class(_nd);
    }
    return _d.getMetaInfo();
}


#ifdef CPGF_METAGEN_LINKAGE_SPEC
CPGF_METAGEN_LINKAGE_SPEC
#endif
GDefineMetaInfo createMetaClass_GComponentTouchHandler()
{
    GDefineMetaGlobalDangle _d = GDefineMetaGlobalDangle::dangle();
    {
        GDefineMetaClass<gincu::GComponentTouchHandler, gincu::GComponent> _nd = GDefineMetaClass<gincu::GComponentTouchHandler, gincu::GComponent>::Policy<MakePolicy<GMetaRuleDefaultConstructorAbsent, GMetaRuleCopyConstructorAbsent> >::lazyDeclare("GComponentTouchHandler", &buildMetaClass_GComponentTouchHandler);
        _d._class(_nd);
    }
    return _d.getMetaInfo();
}


#ifdef CPGF_METAGEN_LINKAGE_SPEC
CPGF_METAGEN_LINKAGE_SPEC
#endif
GDefineMetaInfo createMetaClass_GTouchHandlerFindResult()
{
    GDefineMetaGlobalDangle _d = GDefineMetaGlobalDangle::dangle();
    {
        GDefineMetaClass<gincu::GTouchHandlerFindResult> _nd = GDefineMetaClass<gincu::GTouchHandlerFindResult>::lazyDeclare("GTouchHandlerFindResult", &buildMetaClass_GTouchHandlerFindResult);
        _d._class(_nd);
    }
    return _d.getMetaInfo();
}


} // namespace meta_gincu


