// Auto generated file, don't modify.


#include "gincu/ecs/gcomponentanimation.h"

#include "meta_gincugcomponentanimation.h"

using namespace cpgf;

namespace meta_gincu { 


#ifdef CPGF_METAGEN_LINKAGE_SPEC
CPGF_METAGEN_LINKAGE_SPEC
#endif
GDefineMetaInfo createMetaClass_GComponentAnimation()
{
    GDefineMetaGlobalDangle _d = GDefineMetaGlobalDangle::dangle();
    {
        GDefineMetaClass<gincu::GComponentAnimation, gincu::GComponent> _nd = GDefineMetaClass<gincu::GComponentAnimation, gincu::GComponent>::Policy<MakePolicy<GMetaRuleDefaultConstructorAbsent, GMetaRuleCopyConstructorAbsent> >::lazyDeclare("GComponentAnimation", &buildMetaClass_GComponentAnimation);
        _d._class(_nd);
    }
    return _d.getMetaInfo();
}


} // namespace meta_gincu


