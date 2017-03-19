// Auto generated file, don't modify.

#ifndef CPGF_META_GINCUGCOMPONENTLOCALTRANSFORM_H
#define CPGF_META_GINCUGCOMPONENTLOCALTRANSFORM_H


#include "cpgf/gmetadefine.h"
#include "cpgf/metadata/gmetadataconfig.h"
#include "cpgf/metadata/private/gmetadata_header.h"
#include "cpgf/gmetapolicy.h"


using namespace gincu;


namespace meta_gincu { 


template <typename D>
void buildMetaClass_GComponentLocalTransform(D _d)
{
    (void)_d;
    using namespace cpgf;
    
    _d.CPGF_MD_TEMPLATE _constructor<void * ()>();
    _d.CPGF_MD_TEMPLATE _constructor<void * (const GPoint &, const GScale &, const bool)>()
        ._default(copyVariantFromCopyable<const bool>(true))
        ._default(copyVariantFromCopyable<const GScale &>({1.0f, 1.0f}))
    ;
    _d.CPGF_MD_TEMPLATE _method("getComponentType", &D::ClassType::getComponentType);
    _d.CPGF_MD_TEMPLATE _method("setParent", &D::ClassType::setParent);
    _d.CPGF_MD_TEMPLATE _method("getParent", &D::ClassType::getParent);
    _d.CPGF_MD_TEMPLATE _method("applyGlobal", &D::ClassType::applyGlobal);
    _d.CPGF_MD_TEMPLATE _method("getChildCount", &D::ClassType::getChildCount);
    _d.CPGF_MD_TEMPLATE _method("getChildAt", &D::ClassType::getChildAt);
    _d.CPGF_MD_TEMPLATE _method("getSortedChildren", &D::ClassType::getSortedChildren);
}


} // namespace meta_gincu




#include "cpgf/metadata/private/gmetadata_footer.h"


#endif
