// Auto generated file, don't modify.

#ifndef CPGF_META_GINCUGFRAMEANIMATION_H
#define CPGF_META_GINCUGFRAMEANIMATION_H


#include "cpgf/gmetadefine.h"
#include "cpgf/metadata/gmetadataconfig.h"
#include "cpgf/metadata/private/gmetadata_header.h"
#include "cpgf/gmetapolicy.h"


using namespace gincu;


namespace meta_gincu { 


template <typename D>
void buildMetaClass_Global_gframeanimation(D _d)
{
    (void)_d;
    using namespace cpgf;
    
    _d.CPGF_MD_TEMPLATE _method("buildFrameAnimationDataFromAtlas", (void (*) (GFrameAnimationSetData *, const GAtlas &, const int))&buildFrameAnimationDataFromAtlas)
        ._default(copyVariantFromCopyable(30))
    ;
}


template <typename D>
void buildMetaClass_GFrameAnimationData(D _d)
{
    (void)_d;
    using namespace cpgf;
    
    _d.CPGF_MD_TEMPLATE _constructor<void * ()>();
    _d.CPGF_MD_TEMPLATE _constructor<void * (std::vector< int > &&, const int)>();
    _d.CPGF_MD_TEMPLATE _method("getFrameIndexList", &D::ClassType::getFrameIndexList);
    _d.CPGF_MD_TEMPLATE _method("getDurationMilliseconds", &D::ClassType::getDurationMilliseconds);
}


template <typename D>
void buildMetaClass_GFrameAnimationSetData(D _d)
{
    (void)_d;
    using namespace cpgf;
    
    _d.CPGF_MD_TEMPLATE _method("append", &D::ClassType::append);
    _d.CPGF_MD_TEMPLATE _method("getAnimationData", &D::ClassType::getAnimationData);
    _d.CPGF_MD_TEMPLATE _method("getAnimationCount", &D::ClassType::getAnimationCount);
    _d.CPGF_MD_TEMPLATE _method("getAnimationNameAt", &D::ClassType::getAnimationNameAt);
    _d.CPGF_MD_TEMPLATE _method("getAnimationDataAt", &D::ClassType::getAnimationDataAt);
}


} // namespace meta_gincu




#include "cpgf/metadata/private/gmetadata_footer.h"


#endif
