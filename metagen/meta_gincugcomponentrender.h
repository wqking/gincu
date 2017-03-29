// Auto generated file, don't modify.

#ifndef CPGF_META_GINCUGCOMPONENTRENDER_H
#define CPGF_META_GINCUGCOMPONENTRENDER_H


#include "cpgf/gmetadefine.h"
#include "cpgf/metadata/gmetadataconfig.h"
#include "cpgf/metadata/private/gmetadata_header.h"
#include "cpgf/gmetapolicy.h"


using namespace gincu;


namespace meta_gincu { 


template <typename D>
void buildMetaClass_Global_gcomponentrender(D _d)
{
    (void)_d;
    using namespace cpgf;
    
    _d.CPGF_MD_TEMPLATE _method("createAndLoadImageComponent", (GComponentImageRender * (*) (const std::string &))&createAndLoadImageComponent, cpgf::MakePolicy<cpgf::GMetaRuleCopyConstReference<0> >());
    _d.CPGF_MD_TEMPLATE _method("createImageComponent", (GComponentImageRender * (*) (const GImage &))&createImageComponent);
    _d.CPGF_MD_TEMPLATE _method("createAtlasRenderComponent", (GComponentAtlasRender * (*) (const GAtlas &, const std::string &))&createAtlasRenderComponent, cpgf::MakePolicy<cpgf::GMetaRuleCopyConstReference<1> >());
    _d.CPGF_MD_TEMPLATE _method("createAndLoadTextComponent", (GComponentTextRender * (*) (const std::string &, const GColor, const int))&createAndLoadTextComponent, cpgf::MakePolicy<cpgf::GMetaRuleCopyConstReference<0> >());
    _d.CPGF_MD_TEMPLATE _method("createRectRenderComponent", (GComponentRectRender * (*) (const GColor, const GSize &))&createRectRenderComponent);
}


template <typename D>
void buildMetaClass_GComponentContainerRender(D _d)
{
    (void)_d;
    using namespace cpgf;
    
    _d.CPGF_MD_TEMPLATE _constructor<void * ()>();
    _d.CPGF_MD_TEMPLATE _method("add", &D::ClassType::add);
}


template <typename D>
void buildMetaClass_GComponentRender(D _d)
{
    (void)_d;
    using namespace cpgf;
    
    _d.CPGF_MD_TEMPLATE _method("getComponentType", &D::ClassType::getComponentType);
    _d.CPGF_MD_TEMPLATE _method("draw", &D::ClassType::draw);
    _d.CPGF_MD_TEMPLATE _method("getSize", &D::ClassType::getSize);
    _d.CPGF_MD_TEMPLATE _method("setBlendMode", &D::ClassType::setBlendMode);
    _d.CPGF_MD_TEMPLATE _method("getBlendMode", &D::ClassType::getBlendMode);
    _d.CPGF_MD_TEMPLATE _method("setColor", &D::ClassType::setColor);
    _d.CPGF_MD_TEMPLATE _method("getColor", &D::ClassType::getColor);
}


template <typename D, typename RenderType>
void buildMetaClass_GComponentRenderCommon(D _d)
{
    (void)_d;
    using namespace cpgf;
    
    _d.CPGF_MD_TEMPLATE _constructor<void * ()>();
    _d.CPGF_MD_TEMPLATE _constructor<void * (const RenderType &)>();
    _d.CPGF_MD_TEMPLATE _method("setRender", &D::ClassType::setRender);
    _d.CPGF_MD_TEMPLATE _method("getRender", (RenderType & (D::ClassType::*) ())&D::ClassType::getRender);
    _d.CPGF_MD_TEMPLATE _method("getRender", (const RenderType & (D::ClassType::*) () const)&D::ClassType::getRender);
}


template <typename D>
void buildMetaClass_GComponentVertexArrayRender(D _d)
{
    (void)_d;
    using namespace cpgf;
    
}


} // namespace meta_gincu




#include "cpgf/metadata/private/gmetadata_footer.h"


#endif
