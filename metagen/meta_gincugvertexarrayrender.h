// Auto generated file, don't modify.

#ifndef CPGF_META_GINCUGVERTEXARRAYRENDER_H
#define CPGF_META_GINCUGVERTEXARRAYRENDER_H


#include "cpgf/gmetadefine.h"
#include "cpgf/metadata/gmetadataconfig.h"
#include "cpgf/metadata/private/gmetadata_header.h"
#include "cpgf/gmetapolicy.h"


using namespace gincu;


namespace meta_gincu { 


template <typename D>
void buildMetaClass_Global_gvertexarrayrender(D _d)
{
    (void)_d;
    using namespace cpgf;
    
    _d.CPGF_MD_TEMPLATE _method("drawRender", (void (*) (const GVertexArrayRender &, GRenderContext *, const GMatrix44 &, const GRenderInfo *))&drawRender);
    _d.CPGF_MD_TEMPLATE _method("getRenderSize", (GSize (*) (const GVertexArrayRender &))&getRenderSize);
}


template <typename D>
void buildMetaClass_GVertexArrayRender(D _d)
{
    (void)_d;
    using namespace cpgf;
    
    _d.CPGF_MD_TEMPLATE _constructor<void * ()>();
    _d.CPGF_MD_TEMPLATE _constructor<void * (const GPrimitive, const GVertexArray &)>();
    _d.CPGF_MD_TEMPLATE _constructor<void * (const GPrimitive, const GVertexArray &, const GTexture &)>();
    _d.CPGF_MD_TEMPLATE _method("getPrimitive", &D::ClassType::getPrimitive);
    _d.CPGF_MD_TEMPLATE _method("setPrimitive", &D::ClassType::setPrimitive);
    _d.CPGF_MD_TEMPLATE _method("getVertexArray", (const GVertexArray & (D::ClassType::*) () const)&D::ClassType::getVertexArray);
    _d.CPGF_MD_TEMPLATE _method("getVertexArray", (GVertexArray & (D::ClassType::*) ())&D::ClassType::getVertexArray);
    _d.CPGF_MD_TEMPLATE _method("setVertexArray", &D::ClassType::setVertexArray);
    _d.CPGF_MD_TEMPLATE _method("getTexture", &D::ClassType::getTexture);
    _d.CPGF_MD_TEMPLATE _method("setTexture", &D::ClassType::setTexture);
    _d.CPGF_MD_TEMPLATE _method("getColor", &D::ClassType::getColor);
    _d.CPGF_MD_TEMPLATE _method("setColor", &D::ClassType::setColor);
}


} // namespace meta_gincu




#include "cpgf/metadata/private/gmetadata_footer.h"


#endif
