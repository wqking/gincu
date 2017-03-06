// Auto generated file, don't modify.

#ifndef CPGF_META_GINCUGDEVICECONTEXT_H
#define CPGF_META_GINCUGDEVICECONTEXT_H


#include "cpgf/gmetadefine.h"
#include "cpgf/metadata/gmetadataconfig.h"
#include "cpgf/metadata/private/gmetadata_header.h"
#include "cpgf/gmetapolicy.h"


using namespace gincu;


namespace meta_gincu { 


template <typename D>
void buildMetaClass_GDeviceContext(D _d)
{
    (void)_d;
    using namespace cpgf;
    
    _d.CPGF_MD_TEMPLATE _method("getInstance", &D::ClassType::getInstance);
    _d.CPGF_MD_TEMPLATE _method("initialize", &D::ClassType::initialize);
    _d.CPGF_MD_TEMPLATE _method("finalize", &D::ClassType::finalize);
    _d.CPGF_MD_TEMPLATE _method("getRenderContext", &D::ClassType::getRenderContext);
    _d.CPGF_MD_TEMPLATE _method("getEvent", &D::ClassType::getEvent);
    _d.CPGF_MD_TEMPLATE _method("isFinished", &D::ClassType::isFinished);
    _d.CPGF_MD_TEMPLATE _method("createTextRenderData", &D::ClassType::createTextRenderData);
    _d.CPGF_MD_TEMPLATE _method("createVertexArrayData", &D::ClassType::createVertexArrayData);
    _d.CPGF_MD_TEMPLATE _method("createFontData", &D::ClassType::createFontData);
    _d.CPGF_MD_TEMPLATE _method("createTextureData", &D::ClassType::createTextureData);
    _d.CPGF_MD_TEMPLATE _method("createCameraData", &D::ClassType::createCameraData);
    _d.CPGF_MD_TEMPLATE _method("createFileInputStreamData", &D::ClassType::createFileInputStreamData);
}


template <typename D>
void buildMetaClass_GDeviceContextRegister(D _d)
{
    (void)_d;
    using namespace cpgf;
    
    _d.CPGF_MD_TEMPLATE _method("getInstance", &D::ClassType::getInstance);
}


} // namespace meta_gincu




#include "cpgf/metadata/private/gmetadata_footer.h"


#endif
