// Auto generated file, don't modify.

#ifndef CPGF_META_GINCUGAPPLICATION_H
#define CPGF_META_GINCUGAPPLICATION_H


#include "cpgf/gmetadefine.h"
#include "cpgf/metadata/gmetadataconfig.h"
#include "cpgf/metadata/private/gmetadata_header.h"
#include "cpgf/gmetapolicy.h"


using namespace gincu;


namespace meta_gincu { 


template <typename D>
void buildMetaClass_GApplication(D _d)
{
    (void)_d;
    using namespace cpgf;
    
    _d.CPGF_MD_TEMPLATE _constructor<void * ()>();
    _d.CPGF_MD_TEMPLATE _method("getInstance", &D::ClassType::getInstance);
    _d.CPGF_MD_TEMPLATE _method("run", &D::ClassType::run);
    _d.CPGF_MD_TEMPLATE _method("finish", &D::ClassType::finish);
    _d.CPGF_MD_TEMPLATE _method("executeWorkerTask", &D::ClassType::executeWorkerTask);
    _d.CPGF_MD_TEMPLATE _method("getConfigInfo", &D::ClassType::getConfigInfo);
    _d.CPGF_MD_TEMPLATE _method("getScreenSize", &D::ClassType::getScreenSize);
    _d.CPGF_MD_TEMPLATE _method("getSceneManager", &D::ClassType::getSceneManager);
    _d.CPGF_MD_TEMPLATE _method("getEventQueue", &D::ClassType::getEventQueue);
    _d.CPGF_MD_TEMPLATE _method("getFrameCount", &D::ClassType::getFrameCount);
    _d.CPGF_MD_TEMPLATE _method("getFrameRate", &D::ClassType::getFrameRate);
    _d.CPGF_MD_TEMPLATE _method("getRenderFrameRate", &D::ClassType::getRenderFrameRate);
    _d.CPGF_MD_TEMPLATE _method("getFrameMilliseconds", &D::ClassType::getFrameMilliseconds);
    _d.CPGF_MD_TEMPLATE _method("getRenderMilliseconds", &D::ClassType::getRenderMilliseconds);
}


} // namespace meta_gincu




#include "cpgf/metadata/private/gmetadata_footer.h"


#endif
