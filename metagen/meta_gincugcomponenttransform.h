// Auto generated file, don't modify.

#ifndef CPGF_META_GINCUGCOMPONENTTRANSFORM_H
#define CPGF_META_GINCUGCOMPONENTTRANSFORM_H


#include "cpgf/gmetadefine.h"
#include "cpgf/metadata/gmetadataconfig.h"
#include "cpgf/metadata/private/gmetadata_header.h"
#include "cpgf/gmetapolicy.h"


using namespace gincu;


namespace meta_gincu { 


template <typename D>
void buildMetaClass_GComponentTransform(D _d)
{
    (void)_d;
    using namespace cpgf;
    
    _d.CPGF_MD_TEMPLATE _constructor<void * ()>();
    _d.CPGF_MD_TEMPLATE _constructor<void * (const GPoint &)>();
    _d.CPGF_MD_TEMPLATE _method("getComponentType", &D::ClassType::getComponentType);
    _d.CPGF_MD_TEMPLATE _method("getCameraId", &D::ClassType::getCameraId);
    _d.CPGF_MD_TEMPLATE _method("setCameraId", &D::ClassType::setCameraId);
}


} // namespace meta_gincu




#include "cpgf/metadata/private/gmetadata_footer.h"


#endif
