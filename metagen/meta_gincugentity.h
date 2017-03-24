// Auto generated file, don't modify.

#ifndef CPGF_META_GINCUGENTITY_H
#define CPGF_META_GINCUGENTITY_H


#include "cpgf/gmetadefine.h"
#include "cpgf/metadata/gmetadataconfig.h"
#include "cpgf/metadata/private/gmetadata_header.h"
#include "cpgf/gmetapolicy.h"


using namespace gincu;


namespace meta_gincu { 


template <typename D>
void buildMetaClass_Global_gentity(D _d)
{
    (void)_d;
    using namespace cpgf;
    
    _d.CPGF_MD_TEMPLATE _enum<GEntityEventType>("GEntityEventType")
        ._element("componentAdded", gincu::GEntityEventType::componentAdded)
        ._element("componentRemoving", gincu::GEntityEventType::componentRemoving)
    ;
}


template <typename D>
void buildMetaClass_GEntity(D _d)
{
    (void)_d;
    using namespace cpgf;
    
    _d.CPGF_MD_TEMPLATE _constructor<void * ()>();
    _d.CPGF_MD_TEMPLATE _method("addComponent", &D::ClassType::addComponent, cpgf::MakePolicy<cpgf::GMetaRuleTransferOwnership<0> >());
    _d.CPGF_MD_TEMPLATE _method("removeComponent", &D::ClassType::removeComponent);
    _d.CPGF_MD_TEMPLATE _method("addEventCallback", &D::ClassType::addEventCallback);
    _d.CPGF_MD_TEMPLATE _method("removeEventCallback", &D::ClassType::removeEventCallback);
    _d.CPGF_MD_TEMPLATE _method("setComponentManager", &D::ClassType::setComponentManager);
    _d.CPGF_MD_TEMPLATE _method("getComponentManager", &D::ClassType::getComponentManager);
    _d.CPGF_MD_TEMPLATE _method("getComponentByTypeId", &D::ClassType::getComponentByTypeId);
}


} // namespace meta_gincu




#include "cpgf/metadata/private/gmetadata_footer.h"


#endif
