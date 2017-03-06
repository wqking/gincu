// Auto generated file, don't modify.

#ifndef CPGF_META_GINCUGFONT_H
#define CPGF_META_GINCUGFONT_H


#include "cpgf/gmetadefine.h"
#include "cpgf/metadata/gmetadataconfig.h"
#include "cpgf/metadata/private/gmetadata_header.h"
#include "cpgf/gmetapolicy.h"


using namespace gincu;


namespace meta_gincu { 


template <typename D>
void buildMetaClass_GFont(D _d)
{
    (void)_d;
    using namespace cpgf;
    
    _d.CPGF_MD_TEMPLATE _constructor<void * ()>();
    _d.CPGF_MD_TEMPLATE _constructor<void * (const std::shared_ptr< GFontData > &)>();
    _d.CPGF_MD_TEMPLATE _method("setResource", &D::ClassType::setResource);
    _d.CPGF_MD_TEMPLATE _method("getData", &D::ClassType::getData);
}


template <typename D>
void buildMetaClass_GFontData(D _d)
{
    (void)_d;
    using namespace cpgf;
    
    _d.CPGF_MD_TEMPLATE _method("load", &D::ClassType::load);
}


} // namespace meta_gincu




#include "cpgf/metadata/private/gmetadata_footer.h"


#endif
