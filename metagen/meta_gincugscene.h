// Auto generated file, don't modify.

#ifndef CPGF_META_GINCUGSCENE_H
#define CPGF_META_GINCUGSCENE_H


#include "cpgf/gmetadefine.h"
#include "cpgf/metadata/gmetadataconfig.h"
#include "cpgf/metadata/private/gmetadata_header.h"
#include "cpgf/gmetapolicy.h"


using namespace gincu;


namespace meta_gincu { 


template <typename D>
void buildMetaClass_Global_gscene(D _d)
{
    (void)_d;
    using namespace cpgf;
    
}


template <typename D>
void buildMetaClass_GScene(D _d)
{
    (void)_d;
    using namespace cpgf;
    
    _d.CPGF_MD_TEMPLATE _constructor<void * ()>();
    _d.CPGF_MD_TEMPLATE _method("onEnter", &D::ClassType::onEnter);
    _d.CPGF_MD_TEMPLATE _method("onExit", &D::ClassType::onExit);
    _d.CPGF_MD_TEMPLATE _method("enableRender", &D::ClassType::enableRender);
    _d.CPGF_MD_TEMPLATE _method("addEntity", &D::ClassType::addEntity);
    _d.CPGF_MD_TEMPLATE _method("removeEntity", &D::ClassType::removeEntity);
    _d.CPGF_MD_TEMPLATE _method("setTouchCapture", &D::ClassType::setTouchCapture);
    _d.CPGF_MD_TEMPLATE _method("getTouchCapture", &D::ClassType::getTouchCapture);
    _d.CPGF_MD_TEMPLATE _method("getPrimaryCamera", &D::ClassType::getPrimaryCamera);
    _d.CPGF_MD_TEMPLATE _method("getTweenList", &D::ClassType::getTweenList);
}


} // namespace meta_gincu




#include "cpgf/metadata/private/gmetadata_footer.h"


#endif
