// Auto generated file, don't modify.

#ifndef CPGF_META_GINCUGSCENE_H
#define CPGF_META_GINCUGSCENE_H


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
    _d.CPGF_MD_TEMPLATE _method("addEntity", &D::ClassType::addEntity, cpgf::MakePolicy<cpgf::GMetaRuleTransferOwnership<0> >());
    _d.CPGF_MD_TEMPLATE _method("removeEntity", &D::ClassType::removeEntity);
    _d.CPGF_MD_TEMPLATE _method("setTouchCapture", &D::ClassType::setTouchCapture);
    _d.CPGF_MD_TEMPLATE _method("getTouchCapture", &D::ClassType::getTouchCapture);
    _d.CPGF_MD_TEMPLATE _method("getPrimaryCamera", &D::ClassType::getPrimaryCamera);
    _d.CPGF_MD_TEMPLATE _method("getTweenList", &D::ClassType::getTweenList);
}


class GSceneWrapper : public gincu::GScene, public cpgf::GScriptWrapper {
public:
    
    GSceneWrapper()
        : gincu::GScene() {}
    
    void doOnExit()
    {
        cpgf::GScopedInterface<cpgf::IScriptFunction> func(this->getScriptFunction("doOnExit"));
        if(func)
        {
            cpgf::invokeScriptFunctionOnObject(func.get(), this);
            return;
        }
    }
    
    void doOnEnter()
    {
        cpgf::GScopedInterface<cpgf::IScriptFunction> func(this->getScriptFunction("doOnEnter"));
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
    }
};


template <typename D>
void buildMetaClass_GSceneWrapper(D _d)
{
    (void)_d;
    using namespace cpgf;
    
    
    GSceneWrapper::cpgf__register(_d);
    
    buildMetaClass_GScene<D>(_d);
}


} // namespace meta_gincu




#include "cpgf/metadata/private/gmetadata_footer.h"


#endif
