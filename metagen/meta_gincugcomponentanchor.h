// Auto generated file, don't modify.

#ifndef CPGF_META_GINCUGCOMPONENTANCHOR_H
#define CPGF_META_GINCUGCOMPONENTANCHOR_H


#include "cpgf/gmetadefine.h"
#include "cpgf/metadata/gmetadataconfig.h"
#include "cpgf/metadata/private/gmetadata_header.h"
#include "cpgf/gmetapolicy.h"


using namespace gincu;


namespace meta_gincu { 


template <typename D>
void buildMetaClass_GComponentAnchor(D _d)
{
    (void)_d;
    using namespace cpgf;
    
    _d.CPGF_MD_TEMPLATE _constructor<void * ()>();
    _d.CPGF_MD_TEMPLATE _constructor<void * (const GRenderAnchor)>();
    _d.CPGF_MD_TEMPLATE _method("getComponentType", &D::ClassType::getComponentType);
    _d.CPGF_MD_TEMPLATE _method("getAnchor", &D::ClassType::getAnchor);
    _d.CPGF_MD_TEMPLATE _method("setAnchor", &D::ClassType::setAnchor);
    _d.CPGF_MD_TEMPLATE _method("isFlipX", &D::ClassType::isFlipX);
    _d.CPGF_MD_TEMPLATE _method("setFlipX", &D::ClassType::setFlipX);
    _d.CPGF_MD_TEMPLATE _method("isFlipY", &D::ClassType::isFlipY);
    _d.CPGF_MD_TEMPLATE _method("setFlipY", &D::ClassType::setFlipY);
    _d.CPGF_MD_TEMPLATE _method("apply", &D::ClassType::apply);
}


} // namespace meta_gincu




#include "cpgf/metadata/private/gmetadata_footer.h"


#endif
