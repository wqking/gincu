// Auto generated file, don't modify.

#include "gincu/gincuall.h"
#include "cpgf/metatraits/gmetasharedptrtraits_cpp11_shared_ptr.h"
#include "cpgf/tween/gtimeline.h"

#include "gincu/ecs/gcomponentcamera.h"

#include "meta_gincugcomponentcamera.h"

using namespace cpgf;

namespace meta_gincu { 


#ifdef CPGF_METAGEN_LINKAGE_SPEC
CPGF_METAGEN_LINKAGE_SPEC
#endif
GDefineMetaInfo createMetaClass_GComponentCamera()
{
    GDefineMetaGlobalDangle _d = GDefineMetaGlobalDangle::dangle();
    {
        GDefineMetaClass<gincu::GComponentCamera, gincu::GComponent> _nd = GDefineMetaClass<gincu::GComponentCamera, gincu::GComponent>::lazyDeclare("GComponentCamera", &buildMetaClass_GComponentCamera);
        _d._class(_nd);
    }
    return _d.getMetaInfo();
}


} // namespace meta_gincu


