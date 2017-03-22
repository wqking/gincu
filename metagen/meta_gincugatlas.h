// Auto generated file, don't modify.

#ifndef CPGF_META_GINCUGATLAS_H
#define CPGF_META_GINCUGATLAS_H


#include "cpgf/gmetadefine.h"
#include "cpgf/metadata/gmetadataconfig.h"
#include "cpgf/metadata/private/gmetadata_header.h"
#include "cpgf/gmetapolicy.h"


using namespace gincu;


namespace meta_gincu { 


template <typename D>
void buildMetaClass_Global_gatlas(D _d)
{
    (void)_d;
    using namespace cpgf;
    
    _d.CPGF_MD_TEMPLATE _enum<GAtlasFormat>("GAtlasFormat")
        ._element("spritePackText", gincu::GAtlasFormat::spritePackText)
    ;
}


template <typename D>
void buildMetaClass_GAtlas(D _d)
{
    (void)_d;
    using namespace cpgf;
    
    _d.CPGF_MD_TEMPLATE _constructor<void * ()>();
    _d.CPGF_MD_TEMPLATE _constructor<void * (const std::shared_ptr< GAtlasData > &)>();
    _d.CPGF_MD_TEMPLATE _method("registerLoader", &D::ClassType::registerLoader);
    _d.CPGF_MD_TEMPLATE _method("getLoaderMap", &D::ClassType::getLoaderMap);
    _d.CPGF_MD_TEMPLATE _method("getImage", &D::ClassType::getImage);
    _d.CPGF_MD_TEMPLATE _method("getNameList", &D::ClassType::getNameList);
    _d.CPGF_MD_TEMPLATE _method("getRectList", &D::ClassType::getRectList);
    _d.CPGF_MD_TEMPLATE _method("getTexture", &D::ClassType::getTexture);
    _d.CPGF_MD_TEMPLATE _method("getImageCount", &D::ClassType::getImageCount);
    _d.CPGF_MD_TEMPLATE _method("getIndex", &D::ClassType::getIndex);
}


template <typename D>
void buildMetaClass_GAtlasData(D _d)
{
    (void)_d;
    using namespace cpgf;
    
    _d.CPGF_MD_TEMPLATE _method("load", &D::ClassType::load);
    _d.CPGF_MD_TEMPLATE _method("getImage", &D::ClassType::getImage);
    _d.CPGF_MD_TEMPLATE _method("getIndex", &D::ClassType::getIndex);
    _d.CPGF_MD_TEMPLATE _method("getNameList", &D::ClassType::getNameList);
    _d.CPGF_MD_TEMPLATE _method("getRectList", &D::ClassType::getRectList);
    _d.CPGF_MD_TEMPLATE _method("getTexture", &D::ClassType::getTexture);
    _d.CPGF_MD_TEMPLATE _method("appendSubImage", &D::ClassType::appendSubImage);
    _d.CPGF_MD_TEMPLATE _method("setImageName", &D::ClassType::setImageName);
}


} // namespace meta_gincu




#include "cpgf/metadata/private/gmetadata_footer.h"


#endif
