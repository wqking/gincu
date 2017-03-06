// Auto generated file, don't modify.

#ifndef CPGF_META_GINCUGUTIL_H
#define CPGF_META_GINCUGUTIL_H


#include "cpgf/gmetadefine.h"
#include "cpgf/metadata/gmetadataconfig.h"
#include "cpgf/metadata/private/gmetadata_header.h"
#include "cpgf/gmetapolicy.h"


using namespace gincu;


namespace meta_gincu { 


template <typename D>
void buildMetaClass_Global_gutil(D _d)
{
    (void)_d;
    using namespace cpgf;
    
    _d.CPGF_MD_TEMPLATE _method("isEqual", (bool (*) (const int, const int))&isEqual);
    _d.CPGF_MD_TEMPLATE _method("isEqual", (bool (*) (const unsigned int, const unsigned int))&isEqual);
    _d.CPGF_MD_TEMPLATE _method("isEqual", (bool (*) (const long long, const long long))&isEqual);
    _d.CPGF_MD_TEMPLATE _method("isEqual", (bool (*) (const double, const double))&isEqual);
    _d.CPGF_MD_TEMPLATE _method("isEqual", (bool (*) (const float, const float))&isEqual);
    _d.CPGF_MD_TEMPLATE _method("degreeToRadian", (float (*) (const float))&degreeToRadian);
    _d.CPGF_MD_TEMPLATE _method("getRand", (int (*) ())&getRand);
    _d.CPGF_MD_TEMPLATE _method("getRand", (int (*) (const int, const int))&getRand);
    _d.CPGF_MD_TEMPLATE _method("getRand", (int (*) (const int))&getRand);
    _d.CPGF_MD_TEMPLATE _method("sleepMilliseconds", (void (*) (const unsigned int))&sleepMilliseconds);
    _d.CPGF_MD_TEMPLATE _method("getMilliseconds", (unsigned int (*) ())&getMilliseconds);
}


template <typename T>
inline bool opErAToRWrapper_ReferenceWrapperLessCompare__opFunction(const ReferenceWrapperLessCompare<T > * self, const T & a, const T & b) {
    return (*self)(a, b);
}


template <typename D, typename T>
void buildMetaClass_ReferenceWrapperLessCompare(D _d)
{
    (void)_d;
    using namespace cpgf;
    
    _d.CPGF_MD_TEMPLATE _operator<bool (*)(const T &, const T &)>(mopHolder(mopHolder));
    _d.CPGF_MD_TEMPLATE _method("_opFunction", (bool (*) (const ReferenceWrapperLessCompare<T > *, const T &, const T &))&opErAToRWrapper_ReferenceWrapperLessCompare__opFunction<T>, cpgf::MakePolicy<cpgf::GMetaRuleExplicitThis >());
}


} // namespace meta_gincu




#include "cpgf/metadata/private/gmetadata_footer.h"


#endif
