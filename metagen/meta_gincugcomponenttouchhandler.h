// Auto generated file, don't modify.

#ifndef CPGF_META_GINCUGCOMPONENTTOUCHHANDLER_H
#define CPGF_META_GINCUGCOMPONENTTOUCHHANDLER_H


#include "cpgf/gmetadefine.h"
#include "cpgf/metadata/gmetadataconfig.h"
#include "cpgf/metadata/private/gmetadata_header.h"
#include "cpgf/gmetapolicy.h"


using namespace gincu;


namespace meta_gincu { 


template <typename D>
void buildMetaClass_GComponentRendererTouchHandler(D _d)
{
    (void)_d;
    using namespace cpgf;
    
    _d.CPGF_MD_TEMPLATE _constructor<void * ()>();
}


template <typename D>
void buildMetaClass_GComponentTouchHandler(D _d)
{
    (void)_d;
    using namespace cpgf;
    
    _d.CPGF_MD_TEMPLATE _method("getComponentType", &D::ClassType::getComponentType);
    _d.CPGF_MD_TEMPLATE _method("addOnTouch", &D::ClassType::addOnTouch);
    _d.CPGF_MD_TEMPLATE _method("removeOnTouch", &D::ClassType::removeOnTouch);
    _d.CPGF_MD_TEMPLATE _method("canHandle", &D::ClassType::canHandle);
    _d.CPGF_MD_TEMPLATE _method("handle", &D::ClassType::handle, cpgf::MakePolicy<cpgf::GMetaRuleCopyConstReference<0> >());
}


template <typename D>
void buildMetaClass_GTouchHandlerFindResult(D _d)
{
    (void)_d;
    using namespace cpgf;
    
    _d.CPGF_MD_TEMPLATE _field("handler", &D::ClassType::handler);
    _d.CPGF_MD_TEMPLATE _field("worldPosition", &D::ClassType::worldPosition);
}


} // namespace meta_gincu




#include "cpgf/metadata/private/gmetadata_footer.h"


#endif
