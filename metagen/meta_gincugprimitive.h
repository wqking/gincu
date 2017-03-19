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
        ._element("points", gincu::GPrimitive::points)
        ._element("lines", gincu::GPrimitive::lines)
        ._element("lineStrip", gincu::GPrimitive::lineStrip)
        ._element("triangles", gincu::GPrimitive::triangles)
        ._element("triangleStrip", gincu::GPrimitive::triangleStrip)
        ._element("triangleFan", gincu::GPrimitive::triangleFan)
    ;
}


} // namespace meta_gincu




#include "cpgf/metadata/private/gmetadata_footer.h"


#endif
