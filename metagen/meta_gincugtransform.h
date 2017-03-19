// Auto generated file, don't modify.

#ifndef CPGF_META_GINCUGTRANSFORM_H
#define CPGF_META_GINCUGTRANSFORM_H


#include "cpgf/gmetadefine.h"
#include "cpgf/metadata/gmetadataconfig.h"
#include "cpgf/metadata/private/gmetadata_header.h"
#include "cpgf/gmetapolicy.h"


using namespace gincu;


namespace meta_gincu { 


template <typename D>
void buildMetaClass_GTransform(D _d)
{
    (void)_d;
    using namespace cpgf;
    
    _d.CPGF_MD_TEMPLATE _constructor<void * ()>();
    _d.CPGF_MD_TEMPLATE _constructor<void * (const GPoint &, const GScale &)>()
        ._default(copyVariantFromCopyable<const GScale &>({1.0f, 1.0f}))
    ;
    _d.CPGF_MD_TEMPLATE _constructor<void * (const GMatrix44 &)>();
    _d.CPGF_MD_TEMPLATE _method("getPosition", &D::ClassType::getPosition);
    _d.CPGF_MD_TEMPLATE _method("setPosition", &D::ClassType::setPosition);
    _d.CPGF_MD_TEMPLATE _method("getOrigin", &D::ClassType::getOrigin);
    _d.CPGF_MD_TEMPLATE _method("setOrigin", &D::ClassType::setOrigin);
    _d.CPGF_MD_TEMPLATE _method("getScale", &D::ClassType::getScale);
    _d.CPGF_MD_TEMPLATE _method("setScale", &D::ClassType::setScale);
    _d.CPGF_MD_TEMPLATE _method("getRotation", &D::ClassType::getRotation);
    _d.CPGF_MD_TEMPLATE _method("setRotation", &D::ClassType::setRotation);
    _d.CPGF_MD_TEMPLATE _method("getMatrix", &D::ClassType::getMatrix);
    _d.CPGF_MD_TEMPLATE _method("setProjectionMode", &D::ClassType::setProjectionMode);
}


} // namespace meta_gincu




#include "cpgf/metadata/private/gmetadata_footer.h"


#endif
