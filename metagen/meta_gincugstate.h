// Auto generated file, don't modify.

#ifndef CPGF_META_GINCUGSTATE_H
#define CPGF_META_GINCUGSTATE_H


#include "cpgf/gmetadefine.h"
#include "cpgf/metadata/gmetadataconfig.h"
#include "cpgf/metadata/private/gmetadata_header.h"
#include "cpgf/gmetapolicy.h"


using namespace gincu;


namespace meta_gincu { 


template <typename D>
void buildMetaClass_Global_gstate(D _d)
{
    (void)_d;
    using namespace cpgf;
    
    _d.CPGF_MD_TEMPLATE _field("invalidStateId", &invalidStateId);
}


template <typename D>
void buildMetaClass_GState(D _d)
{
    (void)_d;
    using namespace cpgf;
    
    _d.CPGF_MD_TEMPLATE _constructor<void * (const int, const int)>()
        ._default(copyVariantFromCopyable(invalidStateId))
    ;
    _d.CPGF_MD_TEMPLATE _method("onEnter", &D::ClassType::onEnter);
    _d.CPGF_MD_TEMPLATE _method("onExit", &D::ClassType::onExit);
    _d.CPGF_MD_TEMPLATE _method("finish", &D::ClassType::finish);
    _d.CPGF_MD_TEMPLATE _method("gotoNext", &D::ClassType::gotoNext);
    _d.CPGF_MD_TEMPLATE _method("getId", &D::ClassType::getId);
    _d.CPGF_MD_TEMPLATE _method("getNextId", &D::ClassType::getNextId);
    _d.CPGF_MD_TEMPLATE _method("getStateMachine", &D::ClassType::getStateMachine);
}


} // namespace meta_gincu




#include "cpgf/metadata/private/gmetadata_footer.h"


#endif
