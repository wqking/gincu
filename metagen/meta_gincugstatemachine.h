// Auto generated file, don't modify.

#ifndef CPGF_META_GINCUGSTATEMACHINE_H
#define CPGF_META_GINCUGSTATEMACHINE_H


#include "cpgf/gmetadefine.h"
#include "cpgf/metadata/gmetadataconfig.h"
#include "cpgf/metadata/private/gmetadata_header.h"
#include "cpgf/gmetapolicy.h"


using namespace gincu;


namespace meta_gincu { 


template <typename D>
void buildMetaClass_GStateMachine(D _d)
{
    (void)_d;
    using namespace cpgf;
    
    _d.CPGF_MD_TEMPLATE _constructor<void * ()>();
    _d.CPGF_MD_TEMPLATE _method("gotoState", &D::ClassType::gotoState);
    _d.CPGF_MD_TEMPLATE _method("registerState", &D::ClassType::registerState);
    _d.CPGF_MD_TEMPLATE _method("getCurrentStateId", &D::ClassType::getCurrentStateId);
    _d.CPGF_MD_TEMPLATE _method("getCurrentState", &D::ClassType::getCurrentState);
}


} // namespace meta_gincu




#include "cpgf/metadata/private/gmetadata_footer.h"


#endif
