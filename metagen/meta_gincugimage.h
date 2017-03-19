// Auto generated file, don't modify.

#ifndef CPGF_META_GINCUGIMAGE_H
#define CPGF_META_GINCUGIMAGE_H


#include "cpgf/gmetadefine.h"
#include "cpgf/metadata/gmetadataconfig.h"
#include "cpgf/metadata/private/gmetadata_header.h"
#include "cpgf/gmetapolicy.h"


using namespace gincu;


namespace meta_gincu { 


template <typename D>
void buildMetaClass_Global_gimage(D _d)
{
    (void)_d;
    using namespace cpgf;
    
    _d.CPGF_MD_TEMPLATE _method("drawRender", (void (*) (const GImage &, GRenderContext *, const GMatrix44 &, const GRenderInfo *))&drawRender);
    _d.CPGF_MD_TEMPLATE _method("getRenderSize", (GSize (*) (const GImage &))&getRenderSize);
}


template <typename D>
void buildMetaClass_GImage(D _d)
{
    (void)_d;
    using namespace cpgf;
    
    _d.CPGF_MD_TEMPLATE _constructor<void * ()>();
    _d.CPGF_MD_TEMPLATE _constructor<void * (const GTexture &)>();
    _d.CPGF_MD_TEMPLATE _constructor<void * (const GTexture &, const GRect &)>();
    _d.CPGF_MD_TEMPLATE _method("getTexture", &D::ClassType::getTexture);
    _d.CPGF_MD_TEMPLATE _method("setRect", &D::ClassType::setRect);
    _d.CPGF_MD_TEMPLATE _method("getRect", &D::ClassType::getRect);
    _d.CPGF_MD_TEMPLATE _method("isValid", &D::ClassType::isValid);
}


} // namespace meta_gincu




#include "cpgf/metadata/private/gmetadata_footer.h"


#endif
