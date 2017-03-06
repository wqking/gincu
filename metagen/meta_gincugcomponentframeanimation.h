// Auto generated file, don't modify.

#ifndef CPGF_META_GINCUGCOMPONENTFRAMEANIMATION_H
#define CPGF_META_GINCUGCOMPONENTFRAMEANIMATION_H


#include "cpgf/gmetadefine.h"
#include "cpgf/metadata/gmetadataconfig.h"
#include "cpgf/metadata/private/gmetadata_header.h"
#include "cpgf/gmetapolicy.h"


using namespace gincu;


namespace meta_gincu { 


template <typename D>
void buildMetaClass_GComponentFrameAnimation(D _d)
{
    (void)_d;
    using namespace cpgf;
    
    _d.CPGF_MD_TEMPLATE _constructor<void * ()>();
    _d.CPGF_MD_TEMPLATE _constructor<void * (const std::shared_ptr< GFrameAnimationSetData > &)>();
    _d.CPGF_MD_TEMPLATE _method("getTween", &D::ClassType::getTween);
}


} // namespace meta_gincu




#include "cpgf/metadata/private/gmetadata_footer.h"


#endif
