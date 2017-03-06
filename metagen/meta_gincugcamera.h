// Auto generated file, don't modify.

#ifndef CPGF_META_GINCUGCAMERA_H
#define CPGF_META_GINCUGCAMERA_H


#include "cpgf/gmetadefine.h"
#include "cpgf/metadata/gmetadataconfig.h"
#include "cpgf/metadata/private/gmetadata_header.h"
#include "cpgf/gmetapolicy.h"


using namespace gincu;


namespace meta_gincu { 


template <typename D>
void buildMetaClass_Global_gcamera(D _d)
{
    (void)_d;
    using namespace cpgf;
    
    _d.CPGF_MD_TEMPLATE _enum<GCameraFitStrategy>("GCameraFitStrategy")
        ._element("none", gincu::none)
        ._element("scaleFitFullScreen", gincu::scaleFitFullScreen)
        ._element("fixed", gincu::fixed)
    ;
}


template <typename D>
void buildMetaClass_GCamera(D _d)
{
    (void)_d;
    using namespace cpgf;
    
    _d.CPGF_MD_TEMPLATE _constructor<void * ()>();
    _d.CPGF_MD_TEMPLATE _method("apply", &D::ClassType::apply);
    _d.CPGF_MD_TEMPLATE _method("setViewport", &D::ClassType::setViewport);
    _d.CPGF_MD_TEMPLATE _method("getViewport", &D::ClassType::getViewport);
    _d.CPGF_MD_TEMPLATE _method("getViewportPixels", &D::ClassType::getViewportPixels);
    _d.CPGF_MD_TEMPLATE _method("setFitStrategy", &D::ClassType::setFitStrategy);
    _d.CPGF_MD_TEMPLATE _method("getFitStrategy", &D::ClassType::getFitStrategy);
    _d.CPGF_MD_TEMPLATE _method("setTargetViewSize", &D::ClassType::setTargetViewSize);
    _d.CPGF_MD_TEMPLATE _method("getTargetViewSize", &D::ClassType::getTargetViewSize);
    _d.CPGF_MD_TEMPLATE _method("setWorldSize", &D::ClassType::setWorldSize);
    _d.CPGF_MD_TEMPLATE _method("getWorldSize", &D::ClassType::getWorldSize);
    _d.CPGF_MD_TEMPLATE _method("setMask", &D::ClassType::setMask);
    _d.CPGF_MD_TEMPLATE _method("getMask", &D::ClassType::getMask);
    _d.CPGF_MD_TEMPLATE _method("belongs", &D::ClassType::belongs);
    _d.CPGF_MD_TEMPLATE _method("getData", &D::ClassType::getData);
    _d.CPGF_MD_TEMPLATE _method("mapScreenToWorld", &D::ClassType::mapScreenToWorld);
}


template <typename D>
void buildMetaClass_GCameraData(D _d)
{
    (void)_d;
    using namespace cpgf;
    
    _d.CPGF_MD_TEMPLATE _method("apply", &D::ClassType::apply);
    _d.CPGF_MD_TEMPLATE _method("mapScreenToWorld", &D::ClassType::mapScreenToWorld);
}


} // namespace meta_gincu




#include "cpgf/metadata/private/gmetadata_footer.h"


#endif
