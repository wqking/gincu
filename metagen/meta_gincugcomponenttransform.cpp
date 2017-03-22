// Auto generated file, don't modify.

#include "gincu/gincuall.h"

#include "gincu/ecs/gcomponenttransform.h"

#include "meta_gincugcomponenttransform.h"

using namespace cpgf;

namespace meta_gincu { 


#ifdef CPGF_METAGEN_LINKAGE_SPEC
CPGF_METAGEN_LINKAGE_SPEC
#endif
GDefineMetaInfo createMetaClass_GComponentTransform()
{
    GDefineMetaGlobalDangle _d = GDefineMetaGlobalDangle::dangle();
    {
        GDefineMetaClass<gincu::GComponentTransform, gincu::GComponentTransformBase< GComponentTransform >> _nd = GDefineMetaClass<gincu::GComponentTransform, gincu::GComponentTransformBase< GComponentTransform >>::lazyDeclare("GComponentTransform", &buildMetaClass_GComponentTransform);
        _d._class(_nd);
    }
    return _d.getMetaInfo();
}


} // namespace meta_gincu


