// Auto generated file, don't modify.

#include "gincu/gincuall.h"

#include "gincu/ecs/gcomponenttransformbase.h"

#include "meta_gincugcomponenttransformbase.h"

using namespace cpgf;

namespace meta_gincu { 


#ifdef CPGF_METAGEN_LINKAGE_SPEC
CPGF_METAGEN_LINKAGE_SPEC
#endif
GDefineMetaInfo createMetaClass_GComponentTransformBase_TemplateInstance_GComponentTransformBase_GComponentLocalTransform()
{
    GDefineMetaGlobalDangle _d = GDefineMetaGlobalDangle::dangle();
    {
        GDefineMetaClass<GComponentTransformBase<GComponentLocalTransform>, gincu::GComponent > _nd = GDefineMetaClass<GComponentTransformBase<GComponentLocalTransform>, gincu::GComponent >::lazyDeclare("GComponentTransformBase_GComponentLocalTransform", &buildMetaClass_GComponentTransformBase<GDefineMetaClass<GComponentTransformBase<GComponentLocalTransform>, gincu::GComponent >, GComponentLocalTransform >);
        _d._class(_nd);
    }
    return _d.getMetaInfo();
}
} // namespace meta_gincu


