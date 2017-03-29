// Auto generated file, don't modify.

#ifndef CPGF_META_GINCUGTEXTRENDER_H
#define CPGF_META_GINCUGTEXTRENDER_H


#include "cpgf/gmetadefine.h"
#include "cpgf/metadata/gmetadataconfig.h"
#include "cpgf/metadata/private/gmetadata_header.h"
#include "cpgf/gmetapolicy.h"


using namespace gincu;


namespace meta_gincu { 


template <typename D>
void buildMetaClass_Global_gtextrender(D _d)
{
    (void)_d;
    using namespace cpgf;
    
    _d.CPGF_MD_TEMPLATE _method("drawRender", (void (*) (const GTextRender &, GRenderContext *, const GMatrix44 &, const GRenderInfo *))&drawRender);
    _d.CPGF_MD_TEMPLATE _method("getRenderSize", (GSize (*) (const GTextRender &))&getRenderSize);
}


template <typename D>
void buildMetaClass_GTextRender(D _d)
{
    (void)_d;
    using namespace cpgf;
    
    _d.CPGF_MD_TEMPLATE _constructor<void * ()>();
    _d.CPGF_MD_TEMPLATE _method("setText", &D::ClassType::setText, cpgf::MakePolicy<cpgf::GMetaRuleCopyConstReference<0> >());
    _d.CPGF_MD_TEMPLATE _method("setFontSize", &D::ClassType::setFontSize);
    _d.CPGF_MD_TEMPLATE _method("getData", &D::ClassType::getData);
}


template <typename D>
void buildMetaClass_GTextRenderData(D _d)
{
    (void)_d;
    using namespace cpgf;
    
    _d.CPGF_MD_TEMPLATE _method("setText", &D::ClassType::setText, cpgf::MakePolicy<cpgf::GMetaRuleCopyConstReference<0> >());
    _d.CPGF_MD_TEMPLATE _method("setFontSize", &D::ClassType::setFontSize);
    _d.CPGF_MD_TEMPLATE _method("getBoundingSize", &D::ClassType::getBoundingSize);
}


} // namespace meta_gincu




#include "cpgf/metadata/private/gmetadata_footer.h"


#endif
