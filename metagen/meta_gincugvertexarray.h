// Auto generated file, don't modify.

#ifndef CPGF_META_GINCUGVERTEXARRAY_H
#define CPGF_META_GINCUGVERTEXARRAY_H


#include "cpgf/gmetadefine.h"
#include "cpgf/metadata/gmetadataconfig.h"
#include "cpgf/metadata/private/gmetadata_header.h"
#include "cpgf/gmetapolicy.h"


using namespace gincu;


namespace meta_gincu { 


template <typename D>
void buildMetaClass_GVertexArray(D _d)
{
    (void)_d;
    using namespace cpgf;
    
    _d.CPGF_MD_TEMPLATE _constructor<void * ()>();
    _d.CPGF_MD_TEMPLATE _method("getCount", &D::ClassType::getCount);
    _d.CPGF_MD_TEMPLATE _method("resize", &D::ClassType::resize);
    _d.CPGF_MD_TEMPLATE _method("setAt", &D::ClassType::setAt)
        ._default(copyVariantFromCopyable<const GPoint &>(GPoint()))
        ._default(copyVariantFromCopyable<const GColor>(GVertexArray::defaultColor))
    ;
    _d.CPGF_MD_TEMPLATE _method("append", &D::ClassType::append)
        ._default(copyVariantFromCopyable<const GPoint &>(GPoint()))
        ._default(copyVariantFromCopyable<const GColor>(GVertexArray::defaultColor))
    ;
    _d.CPGF_MD_TEMPLATE _method("getPositionAt", &D::ClassType::getPositionAt);
    _d.CPGF_MD_TEMPLATE _method("getTextureUvAt", &D::ClassType::getTextureUvAt);
    _d.CPGF_MD_TEMPLATE _method("getColorAt", &D::ClassType::getColorAt);
    _d.CPGF_MD_TEMPLATE _method("getColor", &D::ClassType::getColor);
    _d.CPGF_MD_TEMPLATE _method("setColor", &D::ClassType::setColor);
    _d.CPGF_MD_TEMPLATE _method("getTextureSize", &D::ClassType::getTextureSize);
    _d.CPGF_MD_TEMPLATE _method("setTextureSize", &D::ClassType::setTextureSize);
    _d.CPGF_MD_TEMPLATE _method("getBoundingRect", &D::ClassType::getBoundingRect);
    _d.CPGF_MD_TEMPLATE _method("getData", &D::ClassType::getData);
}


template <typename D>
void buildMetaClass_GVertexArrayData(D _d)
{
    (void)_d;
    using namespace cpgf;
    
    _d.CPGF_MD_TEMPLATE _method("getCount", &D::ClassType::getCount);
    _d.CPGF_MD_TEMPLATE _method("resize", &D::ClassType::resize);
    _d.CPGF_MD_TEMPLATE _method("setAt", &D::ClassType::setAt);
    _d.CPGF_MD_TEMPLATE _method("append", &D::ClassType::append);
    _d.CPGF_MD_TEMPLATE _method("getPositionAt", &D::ClassType::getPositionAt);
    _d.CPGF_MD_TEMPLATE _method("getTextureUvAt", &D::ClassType::getTextureUvAt);
    _d.CPGF_MD_TEMPLATE _method("getColorAt", &D::ClassType::getColorAt);
    _d.CPGF_MD_TEMPLATE _method("getColor", &D::ClassType::getColor);
    _d.CPGF_MD_TEMPLATE _method("setColor", &D::ClassType::setColor);
    _d.CPGF_MD_TEMPLATE _method("getTextureSize", &D::ClassType::getTextureSize);
    _d.CPGF_MD_TEMPLATE _method("setTextureSize", &D::ClassType::setTextureSize);
    _d.CPGF_MD_TEMPLATE _method("getBoundingRect", &D::ClassType::getBoundingRect);
}


} // namespace meta_gincu




#include "cpgf/metadata/private/gmetadata_footer.h"


#endif
