// Auto generated file, don't modify.

#ifndef CPGF_META_GINCUGRENDERCONTEXT_H
#define CPGF_META_GINCUGRENDERCONTEXT_H


#include "cpgf/gmetadefine.h"
#include "cpgf/metadata/gmetadataconfig.h"
#include "cpgf/metadata/private/gmetadata_header.h"
#include "cpgf/gmetapolicy.h"


using namespace gincu;


namespace meta_gincu { 


template <typename D>
void buildMetaClass_GRenderContext(D _d)
{
    (void)_d;
    using namespace cpgf;
    
    _d.CPGF_MD_TEMPLATE _method("setBackgroundColor", &D::ClassType::setBackgroundColor);
    _d.CPGF_MD_TEMPLATE _method("render", &D::ClassType::render);
    _d.CPGF_MD_TEMPLATE _method("switchCamera", &D::ClassType::switchCamera);
    _d.CPGF_MD_TEMPLATE _method("draw", (void (D::ClassType::*) (const GTexture &, const GRect &, const GMatrix44 &, const GRenderInfo *))&D::ClassType::draw);
    _d.CPGF_MD_TEMPLATE _method("draw", (void (D::ClassType::*) (const GTextRender &, const GMatrix44 &, const GRenderInfo *))&D::ClassType::draw);
    _d.CPGF_MD_TEMPLATE _method("draw", (void (D::ClassType::*) (const GVertexArray &, const GPrimitive, const GTexture &, const GMatrix44 &, const GRenderInfo *))&D::ClassType::draw);
}


} // namespace meta_gincu




#include "cpgf/metadata/private/gmetadata_footer.h"


#endif
