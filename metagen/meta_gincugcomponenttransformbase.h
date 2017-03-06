// Auto generated file, don't modify.

#ifndef CPGF_META_GINCUGCOMPONENTTRANSFORMBASE_H
#define CPGF_META_GINCUGCOMPONENTTRANSFORMBASE_H


#include "cpgf/gmetadefine.h"
#include "cpgf/metadata/gmetadataconfig.h"
#include "cpgf/metadata/private/gmetadata_header.h"
#include "cpgf/gmetapolicy.h"


using namespace gincu;


namespace meta_gincu { 


template <typename D, typename T>
void buildMetaClass_GComponentTransformBase(D _d)
{
    (void)_d;
    using namespace cpgf;
    
    _d.CPGF_MD_TEMPLATE _constructor<void * ()>();
    _d.CPGF_MD_TEMPLATE _constructor<void * (const GPoint &, const GScale &, const bool)>();
    _d.CPGF_MD_TEMPLATE _method("getPosition", &D::ClassType::getPosition);
    _d.CPGF_MD_TEMPLATE _method("setPosition", &D::ClassType::setPosition);
    _d.CPGF_MD_TEMPLATE _method("getOrigin", &D::ClassType::getOrigin);
    _d.CPGF_MD_TEMPLATE _method("setOrigin", &D::ClassType::setOrigin);
    _d.CPGF_MD_TEMPLATE _method("getScale", &D::ClassType::getScale);
    _d.CPGF_MD_TEMPLATE _method("setScale", &D::ClassType::setScale);
    _d.CPGF_MD_TEMPLATE _method("getRotation", &D::ClassType::getRotation);
    _d.CPGF_MD_TEMPLATE _method("setRotation", &D::ClassType::setRotation);
    _d.CPGF_MD_TEMPLATE _method("isVisible", &D::ClassType::isVisible);
    _d.CPGF_MD_TEMPLATE _method("setVisible", &D::ClassType::setVisible);
    _d.CPGF_MD_TEMPLATE _method("getZOrder", &D::ClassType::getZOrder);
    _d.CPGF_MD_TEMPLATE _method("setZOrder", &D::ClassType::setZOrder);
    _d.CPGF_MD_TEMPLATE _method("getTransform", (const GTransform & (D::ClassType::*) () const)&D::ClassType::getTransform, cpgf::MakePolicy<cpgf::GMetaRuleCopyConstReference<-1> >());
    _d.CPGF_MD_TEMPLATE _method("getTransform", (GTransform & (D::ClassType::*) ())&D::ClassType::getTransform);
    _d.CPGF_MD_TEMPLATE _method("setTransform", &D::ClassType::setTransform, cpgf::MakePolicy<cpgf::GMetaRuleCopyConstReference<0> >());
}


} // namespace meta_gincu




#include "cpgf/metadata/private/gmetadata_footer.h"


#endif
