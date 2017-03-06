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
        ._element("componentAdded", gincu::componentAdded)
        ._element("componentRemoving", gincu::componentRemoving)
    ;
}


inline GEntity & opErAToRWrapper_GEntity__opAssign(GEntity * self, const GEntity & __arg0) {
    return (*self) = __arg0;
}


template <typename D>
void buildMetaClass_GEntity(D _d)
{
    (void)_d;
    using namespace cpgf;
    
    _d.CPGF_MD_TEMPLATE _constructor<void * ()>();
    _d.CPGF_MD_TEMPLATE _constructor<void * (const GEntity &)>();
    _d.CPGF_MD_TEMPLATE _method("addComponent", &D::ClassType::addComponent);
    _d.CPGF_MD_TEMPLATE _method("removeComponent", &D::ClassType::removeComponent);
    _d.CPGF_MD_TEMPLATE _method("addEventCallback", &D::ClassType::addEventCallback);
    _d.CPGF_MD_TEMPLATE _method("removeEventCallback", &D::ClassType::removeEventCallback);
    _d.CPGF_MD_TEMPLATE _method("setComponentManager", &D::ClassType::setComponentManager);
    _d.CPGF_MD_TEMPLATE _method("getComponentManager", &D::ClassType::getComponentManager);
    _d.CPGF_MD_TEMPLATE _method("getComponentByTypeId", &D::ClassType::getComponentByTypeId);
    _d.CPGF_MD_TEMPLATE _operator< new (cpgf::GMetaSelf)>(mopHolder());
    _d.CPGF_MD_TEMPLATE _operator< delete (cpgf::GMetaSelf)>(mopHolder());
    _d.CPGF_MD_TEMPLATE _operator<GEntity & (*)(cpgf::GMetaSelf, const GEntity &)>(mopHolder = mopHolder);
    _d.CPGF_MD_TEMPLATE _method("_opAssign", (GEntity & (*) (GEntity *, const GEntity &))&opErAToRWrapper_GEntity__opAssign, cpgf::MakePolicy<cpgf::GMetaRuleExplicitThis >());
}


} // namespace meta_gincu




#include "cpgf/metadata/private/gmetadata_footer.h"


#endif
