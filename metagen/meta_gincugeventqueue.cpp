// Auto generated file, don't modify.

#include "gincu/gincuall.h"
#include "cpgf/metatraits/gmetasharedptrtraits_cpp11_shared_ptr.h"

#include "gincu/geventqueue.h"

#include "meta_gincugeventqueue.h"

using namespace cpgf;

namespace meta_gincu { 


#ifdef CPGF_METAGEN_LINKAGE_SPEC
CPGF_METAGEN_LINKAGE_SPEC
#endif
GDefineMetaInfo createMetaClass_GEventQueue()
{
    GDefineMetaGlobalDangle _d = GDefineMetaGlobalDangle::dangle();
    {
        GDefineMetaClass<gincu::GEventQueue, eventpp::EventQueue< GEventType, void(const GEvent &), GEventQueuePolicies >> _nd = GDefineMetaClass<gincu::GEventQueue, eventpp::EventQueue< GEventType, void(const GEvent &), GEventQueuePolicies >>::lazyDeclare("GEventQueue", &buildMetaClass_GEventQueue);
        _d._class(_nd);
    }
    return _d.getMetaInfo();
}


#ifdef CPGF_METAGEN_LINKAGE_SPEC
CPGF_METAGEN_LINKAGE_SPEC
#endif
GDefineMetaInfo createMetaClass_GEventQueuePolicies()
{
    GDefineMetaGlobalDangle _d = GDefineMetaGlobalDangle::dangle();
    {
        GDefineMetaClass<gincu::GEventQueuePolicies> _nd = GDefineMetaClass<gincu::GEventQueuePolicies>::lazyDeclare("GEventQueuePolicies", &buildMetaClass_GEventQueuePolicies);
        _d._class(_nd);
    }
    return _d.getMetaInfo();
}


} // namespace meta_gincu


