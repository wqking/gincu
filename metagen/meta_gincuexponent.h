// Auto generated file, don't modify.

#ifndef CPGF_META_GINCUEXPONENT_H
#define CPGF_META_GINCUEXPONENT_H


#include "cpgf/gmetadefine.h"
#include "cpgf/metadata/gmetadataconfig.h"
#include "cpgf/metadata/private/gmetadata_header.h"
#include "cpgf/gmetapolicy.h"
#include "cpgf/tween/gtimeline.h"
#include "cpgf/accessor/gaccessor.h"
#include "cpgf/gselectfunctionbyarity.h"


using namespace cpgf;


namespace meta_gincu { 


template <typename D>
void buildMetaClass_ExponentEase(D _d)
{
    (void)_d;
    using namespace cpgf;
    
    _d.CPGF_MD_TEMPLATE _method("easeIn", &D::ClassType::easeIn);
    _d.CPGF_MD_TEMPLATE _method("easeOut", &D::ClassType::easeOut);
    _d.CPGF_MD_TEMPLATE _method("easeInOut", &D::ClassType::easeInOut);
}


} // namespace meta_gincu




#include "cpgf/metadata/private/gmetadata_footer.h"


#endif
