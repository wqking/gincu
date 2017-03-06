// Auto generated file, don't modify.

#ifndef CPGF_META_GINCUGATLASRENDER_H
#define CPGF_META_GINCUGATLASRENDER_H


#include "cpgf/gmetadefine.h"
#include "cpgf/metadata/gmetadataconfig.h"
#include "cpgf/metadata/private/gmetadata_header.h"
#include "cpgf/gmetapolicy.h"


using namespace gincu;


namespace meta_gincu { 


template <typename D>
void buildMetaClass_Global_gatlasrender(D _d)
{
    (void)_d;
    using namespace cpgf;
    
    _d.CPGF_MD_TEMPLATE _method("drawRender", (void (*) (const GAtlasRender &, GRenderContext *, const GMatrix44 &, const GRenderInfo *))&drawRender, cpgf::MakePolicy<cpgf::GMetaRuleCopyConstReference<0> >());
    _d.CPGF_MD_TEMPLATE _method("getRenderSize", (GSize (*) (const GAtlasRender &))&getRenderSize, cpgf::MakePolicy<cpgf::GMetaRuleCopyConstReference<0> >());
}


template <typename D>
void buildMetaClass_GAtlasRender(D _d)
{
    (void)_d;
    using namespace cpgf;
    
    _d.CPGF_MD_TEMPLATE _constructor<void * ()>();
    _d.CPGF_MD_TEMPLATE _constructor<void * (const GAtlas &)>();
    _d.CPGF_MD_TEMPLATE _method("getAtlas", &D::ClassType::getAtlas);
    _d.CPGF_MD_TEMPLATE _method("getIndex", &D::ClassType::getIndex);
    _d.CPGF_MD_TEMPLATE _method("setIndex", &D::ClassType::setIndex);
    _d.CPGF_MD_TEMPLATE _method("getImageCount", &D::ClassType::getImageCount);
    _d.CPGF_MD_TEMPLATE _method("getRect", &D::ClassType::getRect);
    _d.CPGF_MD_TEMPLATE _method("getTexture", &D::ClassType::getTexture);
}


} // namespace meta_gincu




#include "cpgf/metadata/private/gmetadata_footer.h"


#endif
