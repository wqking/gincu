// Auto generated file, don't modify.

#ifndef CPGF_META_GINCUGCONFIGINFO_H
#define CPGF_META_GINCUGCONFIGINFO_H


#include "cpgf/gmetadefine.h"
#include "cpgf/metadata/gmetadataconfig.h"
#include "cpgf/metadata/private/gmetadata_header.h"
#include "cpgf/gmetapolicy.h"


using namespace gincu;


namespace meta_gincu { 


template <typename D>
void buildMetaClass_Global_gconfiginfo(D _d)
{
    (void)_d;
    using namespace cpgf;
    
    _d.CPGF_MD_TEMPLATE _method("createDefaultConfigInfo", (GConfigInfo (*) ())&createDefaultConfigInfo);
}


template <typename D>
void buildMetaClass_GConfigInfo(D _d)
{
    (void)_d;
    using namespace cpgf;
    
    _d.CPGF_MD_TEMPLATE _field("engine", &D::ClassType::engine);
    _d.CPGF_MD_TEMPLATE _field("caption", &D::ClassType::caption);
    _d.CPGF_MD_TEMPLATE _field("framesPerSecond", &D::ClassType::framesPerSecond);
    _d.CPGF_MD_TEMPLATE _field("renderFramesPerSecond", &D::ClassType::renderFramesPerSecond);
    _d.CPGF_MD_TEMPLATE _field("windowSize", &D::ClassType::windowSize);
    _d.CPGF_MD_TEMPLATE _field("targetViewSize", &D::ClassType::targetViewSize);
    _d.CPGF_MD_TEMPLATE _field("fullScreenMode", &D::ClassType::fullScreenMode);
    _d.CPGF_MD_TEMPLATE _field("resizable", &D::ClassType::resizable);
    _d.CPGF_MD_TEMPLATE _field("backgroundColor", &D::ClassType::backgroundColor);
}


} // namespace meta_gincu




#include "cpgf/metadata/private/gmetadata_footer.h"


#endif
