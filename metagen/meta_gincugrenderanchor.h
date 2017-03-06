// Auto generated file, don't modify.

#ifndef CPGF_META_GINCUGRENDERANCHOR_H
#define CPGF_META_GINCUGRENDERANCHOR_H


#include "cpgf/gmetadefine.h"
#include "cpgf/metadata/gmetadataconfig.h"
#include "cpgf/metadata/private/gmetadata_header.h"
#include "cpgf/gmetapolicy.h"


using namespace gincu;


namespace meta_gincu { 


template <typename D>
void buildMetaClass_Global_grenderanchor(D _d)
{
    (void)_d;
    using namespace cpgf;
    
    _d.CPGF_MD_TEMPLATE _method("getOriginByRenderAnchor", (GPoint (*) (const GRenderAnchor, const GSize &))&getOriginByRenderAnchor);
    _d.CPGF_MD_TEMPLATE _enum<GRenderAnchor>("GRenderAnchor")
        ._element("none", gincu::none)
        ._element("hLeft", gincu::hLeft)
        ._element("hCenter", gincu::hCenter)
        ._element("hRight", gincu::hRight)
        ._element("hMask", gincu::hMask)
        ._element("vTop", gincu::vTop)
        ._element("vCenter", gincu::vCenter)
        ._element("vBottom", gincu::vBottom)
        ._element("vMask", gincu::vMask)
        ._element("leftTop", gincu::leftTop)
        ._element("center", gincu::center)
        ._element("rightTop", gincu::rightTop)
    ;
    _d.CPGF_MD_TEMPLATE _operator<GRenderAnchor (*)(const GRenderAnchor, const GRenderAnchor)>(mopHolder & mopHolder);
    _d.CPGF_MD_TEMPLATE _operator<GRenderAnchor (*)(const GRenderAnchor, const GRenderAnchor)>(mopHolder | mopHolder);
}


} // namespace meta_gincu




#include "cpgf/metadata/private/gmetadata_footer.h"


#endif
