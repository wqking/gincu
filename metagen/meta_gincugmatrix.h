// Auto generated file, don't modify.

#ifndef CPGF_META_GINCUGMATRIX_H
#define CPGF_META_GINCUGMATRIX_H


#include "cpgf/gmetadefine.h"
#include "cpgf/metadata/gmetadataconfig.h"
#include "cpgf/metadata/private/gmetadata_header.h"
#include "cpgf/gmetapolicy.h"


using namespace gincu;


namespace meta_gincu { 


template <typename D>
void buildMetaClass_Global_gmatrix(D _d)
{
    (void)_d;
    using namespace cpgf;
    
    _d.CPGF_MD_TEMPLATE _field("identityMatrix", &identityMatrix);
    _d.CPGF_MD_TEMPLATE _method("translateMatrix", (GMatrix44 (*) (const GMatrix44 &, const GPoint &))&translateMatrix);
    _d.CPGF_MD_TEMPLATE _method("scaleMatrix", (GMatrix44 (*) (const GMatrix44 &, const GScale &))&scaleMatrix);
    _d.CPGF_MD_TEMPLATE _method("inverseMatrix", (GMatrix44 (*) (const GMatrix44 &))&inverseMatrix);
    _d.CPGF_MD_TEMPLATE _method("transformPoint", (GPoint (*) (const GMatrix44 &, const GPoint &))&transformPoint);
}


} // namespace meta_gincu




#include "cpgf/metadata/private/gmetadata_footer.h"


#endif
