// Auto generated file, don't modify.

#ifndef CPGF_META_GINCUGCOLOR_H
#define CPGF_META_GINCUGCOLOR_H


#include "cpgf/gmetadefine.h"
#include "cpgf/metadata/gmetadataconfig.h"
#include "cpgf/metadata/private/gmetadata_header.h"
#include "cpgf/gmetapolicy.h"


using namespace gincu;


namespace meta_gincu { 


template <typename D>
void buildMetaClass_Global_gcolor(D _d)
{
    (void)_d;
    using namespace cpgf;
    
    _d.CPGF_MD_TEMPLATE _field("colorBlue", &colorBlue);
    _d.CPGF_MD_TEMPLATE _field("colorGreen", &colorGreen);
    _d.CPGF_MD_TEMPLATE _field("colorRed", &colorRed);
    _d.CPGF_MD_TEMPLATE _field("colorYellow", &colorYellow);
    _d.CPGF_MD_TEMPLATE _field("colorPurple", &colorPurple);
    _d.CPGF_MD_TEMPLATE _field("colorBlack", &colorBlack);
    _d.CPGF_MD_TEMPLATE _field("colorWhite", &colorWhite);
    _d.CPGF_MD_TEMPLATE _method("colorSetAlpha", (GColor (*) (const GColor, const unsigned int))&colorSetAlpha);
    _d.CPGF_MD_TEMPLATE _method("colorSetRed", (GColor (*) (const GColor, const unsigned int))&colorSetRed);
    _d.CPGF_MD_TEMPLATE _method("colorSetGreen", (GColor (*) (const GColor, const unsigned int))&colorSetGreen);
    _d.CPGF_MD_TEMPLATE _method("colorSetBlue", (GColor (*) (const GColor, const unsigned int))&colorSetBlue);
    _d.CPGF_MD_TEMPLATE _method("colorGetAlpha", (unsigned int (*) (const GColor))&colorGetAlpha);
    _d.CPGF_MD_TEMPLATE _method("colorGetRed", (unsigned int (*) (const GColor))&colorGetRed);
    _d.CPGF_MD_TEMPLATE _method("colorGetGreen", (unsigned int (*) (const GColor))&colorGetGreen);
    _d.CPGF_MD_TEMPLATE _method("colorGetBlue", (unsigned int (*) (const GColor))&colorGetBlue);
    _d.CPGF_MD_TEMPLATE _method("colorMakeARGB", (GColor (*) (const int, const int, const int, const int))&colorMakeARGB);
}


} // namespace meta_gincu




#include "cpgf/metadata/private/gmetadata_footer.h"


#endif
