// Auto generated file, don't modify.

#ifndef CPGF_META_GINCUGRENDERINFO_H
#define CPGF_META_GINCUGRENDERINFO_H


#include "cpgf/gmetadefine.h"
#include "cpgf/metadata/gmetadataconfig.h"
#include "cpgf/metadata/private/gmetadata_header.h"
#include "cpgf/gmetapolicy.h"


using namespace gincu;


namespace meta_gincu { 


template <typename D>
void buildMetaClass_Global_grenderinfo(D _d)
{
    (void)_d;
    using namespace cpgf;
    
}


template <typename D>
void buildMetaClass_GRenderInfo(D _d)
{
    (void)_d;
    using namespace cpgf;
    
    _d.CPGF_MD_TEMPLATE _constructor<void * ()>();
    _d.CPGF_MD_TEMPLATE _field("blendMode", &D::ClassType::blendMode);
    _d.CPGF_MD_TEMPLATE _field("color", &D::ClassType::color);
}


} // namespace meta_gincu




#include "cpgf/metadata/private/gmetadata_footer.h"


#endif
