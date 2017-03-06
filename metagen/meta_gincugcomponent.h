// Auto generated file, don't modify.

#ifndef CPGF_META_GINCUGCOMPONENT_H
#define CPGF_META_GINCUGCOMPONENT_H


#include "cpgf/gmetadefine.h"
#include "cpgf/metadata/gmetadataconfig.h"
#include "cpgf/metadata/private/gmetadata_header.h"
#include "cpgf/gmetapolicy.h"


using namespace gincu;


namespace meta_gincu { 


template <typename D>
void buildMetaClass_Global_gcomponent(D _d)
{
    (void)_d;
    using namespace cpgf;
    
    _d.CPGF_MD_TEMPLATE _field("componentTypePrimaryCount", &componentTypePrimaryCount);
    _d.CPGF_MD_TEMPLATE _field("componentTypeUser", &componentTypeUser);
    _d.CPGF_MD_TEMPLATE _method("registerComponentId", (GComponentType (*) (const std::string &))&registerComponentId);
    _d.CPGF_MD_TEMPLATE _enum<GComponentType>("GComponentType")
        ._element("render", gincu::render)
        ._element("transform", gincu::transform)
        ._element("localTransform", gincu::localTransform)
        ._element("touchHandler", gincu::touchHandler)
        ._element("anchor", gincu::anchor)
        ._element("animation", gincu::animation)
        ._element("camera", gincu::camera)
    ;
}


inline GComponent & opErAToRWrapper_GComponent__opAssign(GComponent * self, const GComponent & __arg0) {
    return (*self) = __arg0;
}


template <typename D>
void buildMetaClass_GComponent(D _d)
{
    (void)_d;
    using namespace cpgf;
    
    _d.CPGF_MD_TEMPLATE _constructor<void * (const GComponentType)>();
    _d.CPGF_MD_TEMPLATE _constructor<void * (const GComponent &)>(cpgf::MakePolicy<cpgf::GMetaRuleCopyConstReference<0> >());
    _d.CPGF_MD_TEMPLATE _method("setEntity", &D::ClassType::setEntity);
    _d.CPGF_MD_TEMPLATE _method("getType", &D::ClassType::getType);
    _d.CPGF_MD_TEMPLATE _method("getEntity", &D::ClassType::getEntity);
    _d.CPGF_MD_TEMPLATE _operator< new (cpgf::GMetaSelf)>(mopHolder());
    _d.CPGF_MD_TEMPLATE _operator< delete (cpgf::GMetaSelf)>(mopHolder());
    _d.CPGF_MD_TEMPLATE _operator<GComponent & (*)(cpgf::GMetaSelf, const GComponent &)>(mopHolder = mopHolder, cpgf::MakePolicy<cpgf::GMetaRuleCopyConstReference<1> >());
    _d.CPGF_MD_TEMPLATE _method("_opAssign", (GComponent & (*) (GComponent *, const GComponent &))&opErAToRWrapper_GComponent__opAssign, cpgf::MakePolicy<cpgf::GMetaRuleCopyConstReference<1>, cpgf::GMetaRuleExplicitThis >());
}


template <typename D>
void buildMetaClass_GComponentIdRegister(D _d)
{
    (void)_d;
    using namespace cpgf;
    
    _d.CPGF_MD_TEMPLATE _constructor<void * (const std::string &)>();
    _d.CPGF_MD_TEMPLATE _method("getComponentId", &D::ClassType::getComponentId);
}


} // namespace meta_gincu




#include "cpgf/metadata/private/gmetadata_footer.h"


#endif
