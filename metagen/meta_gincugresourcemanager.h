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
    _d.CPGF_MD_TEMPLATE _method("getImage", &D::ClassType::getImage, cpgf::MakePolicy<cpgf::GMetaRuleCopyConstReference<0> >());
    _d.CPGF_MD_TEMPLATE _method("asyncGetImage", &D::ClassType::asyncGetImage, cpgf::MakePolicy<cpgf::GMetaRuleCopyConstReference<0> >())
        ._default(copyVariantFromCopyable<const GResourceManager::LoaderCallback&>(GResourceManager::LoaderCallback()))
    ;
    _d.CPGF_MD_TEMPLATE _method("getAtlas", &D::ClassType::getAtlas, cpgf::MakePolicy<cpgf::GMetaRuleCopyConstReference<0> >());
    _d.CPGF_MD_TEMPLATE _method("getFont", (GFont (D::ClassType::*) (const std::string &) const)&D::ClassType::getFont, cpgf::MakePolicy<cpgf::GMetaRuleCopyConstReference<0> >());
    _d.CPGF_MD_TEMPLATE _method("asyncGetFont", &D::ClassType::asyncGetFont, cpgf::MakePolicy<cpgf::GMetaRuleCopyConstReference<0> >())
        ._default(copyVariantFromCopyable<const GResourceManager::LoaderCallback&>(GResourceManager::LoaderCallback()))
    ;
    _d.CPGF_MD_TEMPLATE _method("getFont", (GFont (D::ClassType::*) () const)&D::ClassType::getFont);
    _d.CPGF_MD_TEMPLATE _method("solveResourcePath", &D::ClassType::solveResourcePath, cpgf::MakePolicy<cpgf::GMetaRuleCopyConstReference<0> >());
    _d.CPGF_MD_TEMPLATE _method("reloadResources", &D::ClassType::reloadResources);
    _d.CPGF_MD_TEMPLATE _method("getResourcePath", &D::ClassType::getResourcePath, cpgf::MakePolicy<cpgf::GMetaRuleCopyConstReference<-1> >());
    _d.CPGF_MD_TEMPLATE _method("setDefaultFontName", &D::ClassType::setDefaultFontName, cpgf::MakePolicy<cpgf::GMetaRuleCopyConstReference<0> >());
    _d.CPGF_MD_TEMPLATE _method("getDefaultFontName", &D::ClassType::getDefaultFontName, cpgf::MakePolicy<cpgf::GMetaRuleCopyConstReference<-1> >());
}


} // namespace meta_gincu




#include "cpgf/metadata/private/gmetadata_footer.h"


#endif
