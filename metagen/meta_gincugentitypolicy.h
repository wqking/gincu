// Auto generated file, don't modify.

#ifndef CPGF_META_GINCUGENTITYPOLICY_H
#define CPGF_META_GINCUGENTITYPOLICY_H


#include "cpgf/gmetadefine.h"
#include "cpgf/metadata/gmetadataconfig.h"
#include "cpgf/metadata/private/gmetadata_header.h"
#include "cpgf/gmetapolicy.h"


using namespace gincu;


namespace meta_gincu { 


template <typename D>
void buildMetaClass_Global_gentitypolicy(D _d)
{
    (void)_d;
    using namespace cpgf;
    
    _d.CPGF_MD_TEMPLATE _enum<GEntityStoragePolicy>("GEntityStoragePolicy")
        ._element("dynamicArray", gincu::GEntityStoragePolicy::dynamicArray)
        ._element("dynamicMap", gincu::GEntityStoragePolicy::dynamicMap)
        ._element("staticArray", gincu::GEntityStoragePolicy::staticArray)
        ._element("mixedArray", gincu::GEntityStoragePolicy::mixedArray)
        ._element("mixedMap", gincu::GEntityStoragePolicy::mixedMap)
    ;
}


} // namespace meta_gincu




#include "cpgf/metadata/private/gmetadata_footer.h"


#endif
