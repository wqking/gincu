// Auto generated file, don't modify.

#ifndef CPGF_META_GINCUGCOMPONENTMANAGER_H
#define CPGF_META_GINCUGCOMPONENTMANAGER_H


#include "cpgf/gmetadefine.h"
#include "cpgf/metadata/gmetadataconfig.h"
#include "cpgf/metadata/private/gmetadata_header.h"
#include "cpgf/gmetapolicy.h"


using namespace gincu;


namespace meta_gincu { 


template <typename D>
void buildMetaClass_GComponentManager(D _d)
{
    (void)_d;
    using namespace cpgf;
    
    _d.CPGF_MD_TEMPLATE _constructor<void * ()>();
    _d.CPGF_MD_TEMPLATE _method("add", &D::ClassType::add);
    _d.CPGF_MD_TEMPLATE _method("remove", &D::ClassType::remove);
    _d.CPGF_MD_TEMPLATE _method("clear", &D::ClassType::clear);
    _d.CPGF_MD_TEMPLATE _method("parentChanged", &D::ClassType::parentChanged);
    _d.CPGF_MD_TEMPLATE _method("zOrderChanged", &D::ClassType::zOrderChanged);
    _d.CPGF_MD_TEMPLATE _method("cameraIdChanged", &D::ClassType::cameraIdChanged);
    _d.CPGF_MD_TEMPLATE _method("cameraMaskChanged", &D::ClassType::cameraMaskChanged);
    _d.CPGF_MD_TEMPLATE _method("updateLocalTransforms", &D::ClassType::updateLocalTransforms);
    _d.CPGF_MD_TEMPLATE _method("render", &D::ClassType::render);
    _d.CPGF_MD_TEMPLATE _method("findTouchHandlers", &D::ClassType::findTouchHandlers);
    _d.CPGF_MD_TEMPLATE _method("updateDuringRender", &D::ClassType::updateDuringRender);
}


} // namespace meta_gincu




#include "cpgf/metadata/private/gmetadata_footer.h"


#endif
