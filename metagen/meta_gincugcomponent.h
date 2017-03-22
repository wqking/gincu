// Auto generated file, don't modify.

#ifndef CPGF_META_GINCUGCOMPONENT_H
#define CPGF_META_GINCUGCOMPONENT_H


#include "cpgf/gmetadefine.h"
#include "cpgf/metadata/gmetadataconfig.h"
#include "cpgf/metadata/private/gmetadata_header.h"
#include "cpgf/gmetapolicy.h"
#include "cpgf/scriptbind/gscriptbindutil.h"
#include "cpgf/scriptbind/gscriptwrapper.h"
#include "cpgf/gscopedinterface.h"


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
        ._element("render", gincu::GComponentType::render)
        ._element("transform", gincu::GComponentType::transform)
        ._element("localTransform", gincu::GComponentType::localTransform)
        ._element("touchHandler", gincu::GComponentType::touchHandler)
        ._element("anchor", gincu::GComponentType::anchor)
        ._element("animation", gincu::GComponentType::animation)
        ._element("camera", gincu::GComponentType::camera)
    ;
}


template <typename D>
void buildMetaClass_GComponent(D _d)
{
    (void)_d;
    using namespace cpgf;
    
    _d.CPGF_MD_TEMPLATE _constructor<void * (const GComponentType)>();
    _d.CPGF_MD_TEMPLATE _method("setEntity", &D::ClassType::setEntity);
    _d.CPGF_MD_TEMPLATE _method("getType", &D::ClassType::getType);
    _d.CPGF_MD_TEMPLATE _method("getEntity", &D::ClassType::getEntity);
}


class GComponentWrapper : public gincu::GComponent, public cpgf::GScriptWrapper {
public:
    
    GComponentWrapper(const GComponentType type)
        : gincu::GComponent(type) {}
    
    void setType(const GComponentType type)
    {
        gincu::GComponent::setType(type);
    }
    
    void doAfterSetEntity()
    {
        cpgf::GScopedInterface<cpgf::IScriptFunction> func(this->getScriptFunction("doAfterSetEntity"));
        if(func)
        {
            cpgf::invokeScriptFunctionOnObject(func.get(), this);
            return;
        }
    }
    template <typename D>
    static void cpgf__register(D _d)
    {
        (void)_d;
        using namespace cpgf;
        _d.CPGF_MD_TEMPLATE _method("setType", (void (D::ClassType::*) (const GComponentType))&D::ClassType::setType);
    }
};


template <typename D>
void buildMetaClass_GComponentWrapper(D _d)
{
    (void)_d;
    using namespace cpgf;
    
    
    GComponentWrapper::cpgf__register(_d);
    
    buildMetaClass_GComponent<D>(_d);
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
