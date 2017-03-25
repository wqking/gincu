// Auto generated file, don't modify.

#include "gincu/gincuall.h"
#include "cpgf/metatraits/gmetasharedptrtraits_cpp11_shared_ptr.h"
#include "gincu/transition/gtransitionmovein.h"

#include "meta_gincugtransitionmovein.h"

using namespace cpgf;

namespace meta_gincu { 


#ifdef CPGF_METAGEN_LINKAGE_SPEC
CPGF_METAGEN_LINKAGE_SPEC
#endif
GDefineMetaInfo createMetaClass_GTransitionMoveIn()
{
    GDefineMetaGlobalDangle _d = GDefineMetaGlobalDangle::dangle();
    {
        GDefineMetaClass<gincu::GTransitionMoveIn, gincu::GTransition> _nd = GDefineMetaClass<gincu::GTransitionMoveIn, gincu::GTransition>::Policy<MakePolicy<GMetaRuleDefaultConstructorAbsent> >::lazyDeclare("GTransitionMoveIn", &buildMetaClass_GTransitionMoveIn);
        _d._class(_nd);
    }
    return _d.getMetaInfo();
}


} // namespace meta_gincu


