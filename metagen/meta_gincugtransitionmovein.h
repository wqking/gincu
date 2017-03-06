// Auto generated file, don't modify.

#ifndef CPGF_META_GINCUGTRANSITIONMOVEIN_H
#define CPGF_META_GINCUGTRANSITIONMOVEIN_H


#include "cpgf/gmetadefine.h"
#include "cpgf/metadata/gmetadataconfig.h"
#include "cpgf/metadata/private/gmetadata_header.h"
#include "cpgf/gmetapolicy.h"


using namespace gincu;


namespace meta_gincu { 


template <typename D>
void buildMetaClass_GTransitionMoveIn(D _d)
{
    (void)_d;
    using namespace cpgf;
    
    _d.CPGF_MD_TEMPLATE _constructor<void * (unsigned int)>()
        ._default(copyVariantFromCopyable(500))
    ;
}


} // namespace meta_gincu




#include "cpgf/metadata/private/gmetadata_footer.h"


#endif
