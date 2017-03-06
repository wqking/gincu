// Auto generated file, don't modify.

#ifndef CPGF_META_GINCUGPRIMITIVE_H
#define CPGF_META_GINCUGPRIMITIVE_H


#include "cpgf/gmetadefine.h"
#include "cpgf/metadata/gmetadataconfig.h"
#include "cpgf/metadata/private/gmetadata_header.h"
#include "cpgf/gmetapolicy.h"


using namespace gincu;


namespace meta_gincu { 


template <typename D>
void buildMetaClass_Global_gprimitive(D _d)
{
    (void)_d;
    using namespace cpgf;
    
    _d.CPGF_MD_TEMPLATE _enum<GPrimitive>("GPrimitive")
        ._element("points", gincu::points)
        ._element("lines", gincu::lines)
        ._element("lineStrip", gincu::lineStrip)
        ._element("triangles", gincu::triangles)
        ._element("triangleStrip", gincu::triangleStrip)
        ._element("triangleFan", gincu::triangleFan)
    ;
}


} // namespace meta_gincu




#include "cpgf/metadata/private/gmetadata_footer.h"


#endif
