// Auto generated file, don't modify.

#ifndef CPGF_META_GINCUGGEOMETRY_H
#define CPGF_META_GINCUGGEOMETRY_H


#include "cpgf/gmetadefine.h"
#include "cpgf/metadata/gmetadataconfig.h"
#include "cpgf/metadata/private/gmetadata_header.h"
#include "cpgf/gmetapolicy.h"


using namespace gincu;


namespace meta_gincu { 


template <typename D>
void buildMetaClass_Global_ggeometry(D _d)
{
    (void)_d;
    using namespace cpgf;
    
    _d.CPGF_MD_TEMPLATE _method("getPosition", (GPoint (*) (const GRect &))&getPosition);
    _d.CPGF_MD_TEMPLATE _method("getSize", (GSize (*) (const GRect &))&getSize);
    _d.CPGF_MD_TEMPLATE _method("createRect", (GRect (*) (const GPoint &, const GSize &))&createRect);
    _d.CPGF_MD_TEMPLATE _method("isInRect", (bool (*) (const GPoint &, const GRect &))&isInRect);
    _d.CPGF_MD_TEMPLATE _operator<GVector2 (*)(const GVector2 &, const GVector2 &)>(mopHolder + mopHolder);
    _d.CPGF_MD_TEMPLATE _operator<GVector2 (*)(const GVector2 &, const GVector2 &)>(mopHolder - mopHolder);
    _d.CPGF_MD_TEMPLATE _operator<GVector2 (*)(const GVector2 &, const float)>(mopHolder * mopHolder);
    _d.CPGF_MD_TEMPLATE _operator<bool (*)(const GVector2 &, const GVector2 &)>(mopHolder == mopHolder);
    _d.CPGF_MD_TEMPLATE _operator<bool (*)(const GVector2 &, const GVector2 &)>(mopHolder != mopHolder);
    _d.CPGF_MD_TEMPLATE _operator<GVector2 (*)(const GVector2 &)>(-mopHolder);
    _d.CPGF_MD_TEMPLATE _operator<GSize (*)(const GSize &, const GSize &)>(mopHolder + mopHolder);
    _d.CPGF_MD_TEMPLATE _operator<GSize (*)(const GSize &, const GSize &)>(mopHolder - mopHolder);
    _d.CPGF_MD_TEMPLATE _operator<GSize (*)(const GSize &, const float)>(mopHolder * mopHolder);
    _d.CPGF_MD_TEMPLATE _operator<bool (*)(const GSize &, const GSize &)>(mopHolder == mopHolder);
    _d.CPGF_MD_TEMPLATE _operator<bool (*)(const GSize &, const GSize &)>(mopHolder != mopHolder);
    _d.CPGF_MD_TEMPLATE _operator<bool (*)(const GRect &, const GRect &)>(mopHolder == mopHolder);
    _d.CPGF_MD_TEMPLATE _operator<bool (*)(const GRect &, const GRect &)>(mopHolder != mopHolder);
}


template <typename D>
void buildMetaClass_GRect(D _d)
{
    (void)_d;
    using namespace cpgf;
    
    _d.CPGF_MD_TEMPLATE _field("x", &D::ClassType::x);
    _d.CPGF_MD_TEMPLATE _field("y", &D::ClassType::y);
    _d.CPGF_MD_TEMPLATE _field("width", &D::ClassType::width);
    _d.CPGF_MD_TEMPLATE _field("height", &D::ClassType::height);
}


template <typename D>
void buildMetaClass_GSize(D _d)
{
    (void)_d;
    using namespace cpgf;
    
    _d.CPGF_MD_TEMPLATE _field("width", &D::ClassType::width);
    _d.CPGF_MD_TEMPLATE _field("height", &D::ClassType::height);
}


template <typename D>
void buildMetaClass_GVector2(D _d)
{
    (void)_d;
    using namespace cpgf;
    
    _d.CPGF_MD_TEMPLATE _field("x", &D::ClassType::x);
    _d.CPGF_MD_TEMPLATE _field("y", &D::ClassType::y);
}


} // namespace meta_gincu




#include "cpgf/metadata/private/gmetadata_footer.h"


#endif
