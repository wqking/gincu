// Auto generated file, don't modify.

#ifndef CPGF_META_GINCUGBLENDMODE_H
#define CPGF_META_GINCUGBLENDMODE_H


#include "cpgf/gmetadefine.h"
#include "cpgf/metadata/gmetadataconfig.h"
#include "cpgf/metadata/private/gmetadata_header.h"
#include "cpgf/gmetapolicy.h"


using namespace gincu;


namespace meta_gincu { 


template <typename D>
void buildMetaClass_Global_gblendmode(D _d)
{
    (void)_d;
    using namespace cpgf;
    
    _d.CPGF_MD_TEMPLATE _field("blendModeDefault", &blendModeDefault);
    _d.CPGF_MD_TEMPLATE _method("blendModeAlpha", (constexpr GBlendMode (*) ())&blendModeAlpha);
    _d.CPGF_MD_TEMPLATE _method("blendModeAdd", (constexpr GBlendMode (*) ())&blendModeAdd);
    _d.CPGF_MD_TEMPLATE _method("blendModeMultiply", (constexpr GBlendMode (*) (GBlendFunc::destColor, GBlendFunc::zero))&blendModeMultiply);
    _d.CPGF_MD_TEMPLATE _method("blendModeNone", (constexpr GBlendMode (*) (GBlendFunc::one, GBlendFunc::zero))&blendModeNone);
    _d.CPGF_MD_TEMPLATE _enum<GBlendFunc>("GBlendFunc")
        ._element("zero", gincu::zero)
        ._element("one", gincu::one)
        ._element("sourceColor", gincu::sourceColor)
        ._element("oneMinusSourceColor", gincu::oneMinusSourceColor)
        ._element("destColor", gincu::destColor)
        ._element("oneMinusDestColor", gincu::oneMinusDestColor)
        ._element("sourceAlpha", gincu::sourceAlpha)
        ._element("oneMinusSourceAlpha", gincu::oneMinusSourceAlpha)
        ._element("destAlpha", gincu::destAlpha)
        ._element("oneMinusDestAlpha", gincu::oneMinusDestAlpha)
    ;
    _d.CPGF_MD_TEMPLATE _enum<GBlendEquation>("GBlendEquation")
        ._element("add", gincu::add)
        ._element("subtract", gincu::subtract)
        ._element("reverseSubtract", gincu::reverseSubtract)
    ;
    _d.CPGF_MD_TEMPLATE _operator<bool (*)(const GBlendModeChannel &, const GBlendModeChannel &)>(mopHolder == mopHolder);
    _d.CPGF_MD_TEMPLATE _operator<bool (*)(const GBlendMode &, const GBlendMode &)>(mopHolder == mopHolder);
    _d.CPGF_MD_TEMPLATE _operator<bool (*)(const GBlendMode &, const GBlendMode &)>(mopHolder != mopHolder);
}


template <typename D>
void buildMetaClass_GBlendMode(D _d)
{
    (void)_d;
    using namespace cpgf;
    
    _d.CPGF_MD_TEMPLATE _constructor<void * ()>();
    _d.CPGF_MD_TEMPLATE _constructor<void * (const GBlendModeChannel, const GBlendModeChannel)>();
    _d.CPGF_MD_TEMPLATE _field("colorChannel", &D::ClassType::colorChannel);
    _d.CPGF_MD_TEMPLATE _field("alphaChannel", &D::ClassType::alphaChannel);
    _d.CPGF_MD_TEMPLATE _method("alphaChannel", &D::ClassType::alphaChannel);
}


template <typename D>
void buildMetaClass_GBlendModeChannel(D _d)
{
    (void)_d;
    using namespace cpgf;
    
    _d.CPGF_MD_TEMPLATE _constructor<void * ()>();
    _d.CPGF_MD_TEMPLATE _constructor<void * (const GBlendFunc, const GBlendFunc, const GBlendEquation)>()
        ._default(copyVariantFromCopyable(GBlendEquation::add))
    ;
    _d.CPGF_MD_TEMPLATE _field("source", &D::ClassType::source);
    _d.CPGF_MD_TEMPLATE _field("dest", &D::ClassType::dest);
    _d.CPGF_MD_TEMPLATE _field("func", &D::ClassType::func);
}


} // namespace meta_gincu




#include "cpgf/metadata/private/gmetadata_footer.h"


#endif
