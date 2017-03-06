// Auto generated file, don't modify.

#ifndef CPGF_META_GINCUGRESOURCEMANAGER_H
#define CPGF_META_GINCUGRESOURCEMANAGER_H


#include "cpgf/gmetadefine.h"
#include "cpgf/metadata/gmetadataconfig.h"
#include "cpgf/metadata/private/gmetadata_header.h"
#include "cpgf/gmetapolicy.h"


using namespace gincu;


namespace meta_gincu { 


template <typename D>
void buildMetaClass_GResourceManager(D _d)
{
    (void)_d;
    using namespace cpgf;
    
    _d.CPGF_MD_TEMPLATE _constructor<void * ()>();
    _d.CPGF_MD_TEMPLATE _method("getInstance", &D::ClassType::getInstance);
    _d.CPGF_MD_TEMPLATE _method("initialize", &D::ClassType::initialize);
    _d.CPGF_MD_TEMPLATE _method("finalize", &D::ClassType::finalize);
    _d.CPGF_MD_TEMPLATE _method("getImage", &D::ClassType::getImage);
    _d.CPGF_MD_TEMPLATE _method("asyncGetImage", &D::ClassType::asyncGetImage)
        ._default(copyVariantFromCopyable(LoaderCallback()))
    ;
    _d.CPGF_MD_TEMPLATE _method("getAtlas", &D::ClassType::getAtlas);
    _d.CPGF_MD_TEMPLATE _method("getFont", (GFont (D::ClassType::*) (const std::string &) const)&D::ClassType::getFont);
    _d.CPGF_MD_TEMPLATE _method("asyncGetFont", &D::ClassType::asyncGetFont)
        ._default(copyVariantFromCopyable(LoaderCallback()))
    ;
    _d.CPGF_MD_TEMPLATE _method("getFont", (GFont (D::ClassType::*) () const)&D::ClassType::getFont);
    _d.CPGF_MD_TEMPLATE _method("solveResourcePath", &D::ClassType::solveResourcePath);
    _d.CPGF_MD_TEMPLATE _method("reloadResources", &D::ClassType::reloadResources);
    _d.CPGF_MD_TEMPLATE _method("getResourcePath", &D::ClassType::getResourcePath);
    _d.CPGF_MD_TEMPLATE _method("setDefaultFontName", &D::ClassType::setDefaultFontName);
    _d.CPGF_MD_TEMPLATE _method("getDefaultFontName", &D::ClassType::getDefaultFontName);
}


} // namespace meta_gincu




#include "cpgf/metadata/private/gmetadata_footer.h"


#endif
