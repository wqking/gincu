// Auto generated file, don't modify.

#ifndef CPGF_META_GINCUGEVENTQUEUE_H
#define CPGF_META_GINCUGEVENTQUEUE_H


#include "cpgf/gmetadefine.h"
#include "cpgf/metadata/gmetadataconfig.h"
#include "cpgf/metadata/private/gmetadata_header.h"
#include "cpgf/gmetapolicy.h"


using namespace gincu;


namespace meta_gincu { 


template <typename D>
void buildMetaClass_GEventQueue(D _d)
{
    (void)_d;
    using namespace cpgf;
    
    _d.CPGF_MD_TEMPLATE _constructor<void * ()>();
    _d.CPGF_MD_TEMPLATE _method("dispatchAll", &D::ClassType::dispatchAll);
    _d.CPGF_MD_TEMPLATE _method("removeListener", &D::ClassType::removeListener);
}


template <typename D>
void buildMetaClass_GEventQueuePolicies(D _d)
{
    (void)_d;
    using namespace cpgf;
    
    _d.CPGF_MD_TEMPLATE _method("getEvent", &D::ClassType::getEvent);
}


} // namespace meta_gincu




#include "cpgf/metadata/private/gmetadata_footer.h"


#endif
