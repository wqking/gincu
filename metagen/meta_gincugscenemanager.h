// Auto generated file, don't modify.

#ifndef CPGF_META_GINCUGSCENEMANAGER_H
#define CPGF_META_GINCUGSCENEMANAGER_H


#include "cpgf/gmetadefine.h"
#include "cpgf/metadata/gmetadataconfig.h"
#include "cpgf/metadata/private/gmetadata_header.h"
#include "cpgf/gmetapolicy.h"


using namespace gincu;


namespace meta_gincu { 


template <typename D>
void buildMetaClass_GSceneManager(D _d)
{
    (void)_d;
    using namespace cpgf;
    
    _d.CPGF_MD_TEMPLATE _constructor<void * ()>();
    _d.CPGF_MD_TEMPLATE _method("initialize", &D::ClassType::initialize);
    _d.CPGF_MD_TEMPLATE _method("finalize", &D::ClassType::finalize);
    _d.CPGF_MD_TEMPLATE _method("switchScene", (void (D::ClassType::*) (GScene *, GTransition *))&D::ClassType::switchScene)
        ._default(copyVariantFromCopyable<GTransition *>((GTransition *)nullptr))
    ;
    _d.CPGF_MD_TEMPLATE _method("switchScene", (void (D::ClassType::*) (const std::string &, const GSceneManager::SceneCreator&, GTransition *))&D::ClassType::switchScene)
        ._default(copyVariantFromCopyable<GTransition *>((GTransition *)nullptr))
    ;
    _d.CPGF_MD_TEMPLATE _method("getCurrentScene", &D::ClassType::getCurrentScene);
}


} // namespace meta_gincu




#include "cpgf/metadata/private/gmetadata_footer.h"


#endif
