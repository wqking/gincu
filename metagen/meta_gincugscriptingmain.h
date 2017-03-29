// Auto generated file, don't modify.

#ifndef CPGF_META_GINCUGSCRIPTINGMAIN_H
#define CPGF_META_GINCUGSCRIPTINGMAIN_H


#include "cpgf/gmetadefine.h"
#include "cpgf/metadata/gmetadataconfig.h"
#include "cpgf/metadata/private/gmetadata_header.h"
#include "cpgf/gmetapolicy.h"


using namespace gincu;


namespace meta_gincu { 


template <typename D>
void buildMetaClass_GScriptingMain(D _d)
{
    (void)_d;
    using namespace cpgf;
    
    _d.CPGF_MD_TEMPLATE _method("getInstance", &D::ClassType::getInstance);
    _d.CPGF_MD_TEMPLATE _method("initialize", &D::ClassType::initialize);
    _d.CPGF_MD_TEMPLATE _method("getScripeObject", &D::ClassType::getScripeObject);
    _d.CPGF_MD_TEMPLATE _method("getService", &D::ClassType::getService);
    _d.CPGF_MD_TEMPLATE _method("executeString", &D::ClassType::executeString);
    _d.CPGF_MD_TEMPLATE _method("executeFile", &D::ClassType::executeFile);
}


} // namespace meta_gincu




#include "cpgf/metadata/private/gmetadata_footer.h"


#endif
