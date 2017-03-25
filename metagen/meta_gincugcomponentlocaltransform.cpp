// Auto generated file, don't modify.

#include "gincu/gincuall.h"
#include "cpgf/metatraits/gmetasharedptrtraits_cpp11_shared_ptr.h"
#include "gincu/ecs/gcomponentlocaltransform.h"

#include "meta_gincugcomponentlocaltransform.h"

using namespace cpgf;

namespace meta_gincu { 


#ifdef CPGF_METAGEN_LINKAGE_SPEC
CPGF_METAGEN_LINKAGE_SPEC
#endif
GDefineMetaInfo createMetaClass_GComponentLocalTransform()
{
    GDefineMetaGlobalDangle _d = GDefineMetaGlobalDangle::dangle();
    {
        GDefineMetaClass<gincu::GComponentLocalTransform, gincu::GComponentTransformBase< GComponentLocalTransform >> _nd = GDefineMetaClass<gincu::GComponentLocalTransform, gincu::GComponentTransformBase< GComponentLocalTransform >>::lazyDeclare("GComponentLocalTransform", &buildMetaClass_GComponentLocalTransform);
        _d._class(_nd);
    }
    return _d.getMetaInfo();
}


} // namespace meta_gincu


