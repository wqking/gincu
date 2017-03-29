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
        ._element("none", gincu::GRenderAnchor::none)
        ._element("hLeft", gincu::GRenderAnchor::hLeft)
        ._element("hCenter", gincu::GRenderAnchor::hCenter)
        ._element("hRight", gincu::GRenderAnchor::hRight)
        ._element("hMask", gincu::GRenderAnchor::hMask)
        ._element("vTop", gincu::GRenderAnchor::vTop)
        ._element("vCenter", gincu::GRenderAnchor::vCenter)
        ._element("vBottom", gincu::GRenderAnchor::vBottom)
        ._element("vMask", gincu::GRenderAnchor::vMask)
        ._element("leftTop", gincu::GRenderAnchor::leftTop)
        ._element("center", gincu::GRenderAnchor::center)
        ._element("rightTop", gincu::GRenderAnchor::rightTop)
    ;
}


} // namespace meta_gincu




#include "cpgf/metadata/private/gmetadata_footer.h"


#endif
