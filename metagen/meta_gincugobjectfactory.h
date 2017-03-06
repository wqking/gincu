// Auto generated file, don't modify.

#ifndef CPGF_META_GINCUGOBJECTFACTORY_H
#define CPGF_META_GINCUGOBJECTFACTORY_H


#include "cpgf/gmetadefine.h"
#include "cpgf/metadata/gmetadataconfig.h"
#include "cpgf/metadata/private/gmetadata_header.h"
#include "cpgf/gmetapolicy.h"


using namespace gincu;


namespace meta_gincu { 


template <typename D>
void buildMetaClass_Global_gobjectfactory(D _d)
{
    (void)_d;
    using namespace cpgf;
    
}


template <typename D, typename T>
void buildMetaClass_GAfterObjectCreated(D _d)
{
    (void)_d;
    using namespace cpgf;
    
    _d.CPGF_MD_TEMPLATE _method("afterCreated", &D::ClassType::afterCreated);
}


template <typename D, typename T>
void buildMetaClass_GAfterObjectCreatedSetName(D _d)
{
    (void)_d;
    using namespace cpgf;
    
    _d.CPGF_MD_TEMPLATE _method("afterCreated", &D::ClassType::afterCreated);
}


template <typename D, typename T, typename AfterCreated, typename ParamType>
void buildMetaClass_GObjectFactory(D _d)
{
    (void)_d;
    using namespace cpgf;
    
    _d.CPGF_MD_TEMPLATE _method("registerObject", (void (D::ClassType::*) (const std::string &, typename GObjectFactory<T, AfterCreated, ParamType >::ObjectCreator, const ParamType &))&D::ClassType::registerObject);
    _d.CPGF_MD_TEMPLATE _method("registerObject", (void (D::ClassType::*) (const std::string &, typename GObjectFactory<T, AfterCreated, ParamType >::ObjectCreator))&D::ClassType::registerObject);
    _d.CPGF_MD_TEMPLATE _method("createObject", &D::ClassType::createObject);
    _d.CPGF_MD_TEMPLATE _method("getParam", &D::ClassType::getParam);
    _d.CPGF_MD_TEMPLATE _method("has", &D::ClassType::has);
    {
        GDefineMetaClass<typename GObjectFactory<T, AfterCreated, ParamType >::RegisterEntry> _nd = GDefineMetaClass<typename GObjectFactory<T, AfterCreated, ParamType >::RegisterEntry>::declare("RegisterEntry");
        _nd.CPGF_MD_TEMPLATE _field("name", &GObjectFactory<T, AfterCreated, ParamType >::RegisterEntry::name);
        _nd.CPGF_MD_TEMPLATE _field("creator", &GObjectFactory<T, AfterCreated, ParamType >::RegisterEntry::creator);
        _nd.CPGF_MD_TEMPLATE _field("param", &GObjectFactory<T, AfterCreated, ParamType >::RegisterEntry::param);
        _d.CPGF_MD_TEMPLATE _class(_nd);
    }
}


template <typename D>
void buildMetaClass_GObjectFactoryBase(D _d)
{
    (void)_d;
    using namespace cpgf;
    
    _d.CPGF_MD_TEMPLATE _method("getNameList", &D::ClassType::getNameList);
}


} // namespace meta_gincu




#include "cpgf/metadata/private/gmetadata_footer.h"


#endif
