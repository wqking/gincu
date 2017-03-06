// Auto generated file, don't modify.

#ifndef CPGF_META_GINCUGTRANSITION_H
#define CPGF_META_GINCUGTRANSITION_H


#include "cpgf/gmetadefine.h"
#include "cpgf/metadata/gmetadataconfig.h"
#include "cpgf/metadata/private/gmetadata_header.h"
#include "cpgf/gmetapolicy.h"


using namespace gincu;


namespace meta_gincu { 


template <typename D>
void buildMetaClass_GTransition(D _d)
{
    (void)_d;
    using namespace cpgf;
    
    _d.CPGF_MD_TEMPLATE _constructor<void * ()>();
    _d.CPGF_MD_TEMPLATE _method("transite", &D::ClassType::transite);
    _d.CPGF_MD_TEMPLATE _method("cancel", &D::ClassType::cancel);
    _d.CPGF_MD_TEMPLATE _method("addOnComplete", &D::ClassType::addOnComplete);
    _d.CPGF_MD_TEMPLATE _method("getTween", &D::ClassType::getTween);
}


} // namespace meta_gincu




#include "cpgf/metadata/private/gmetadata_footer.h"


#endif
