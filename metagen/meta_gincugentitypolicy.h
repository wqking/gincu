// Auto generated file, don't modify.

#ifndef CPGF_META_GINCUGENTITYPOLICY_H
#define CPGF_META_GINCUGENTITYPOLICY_H


#include "cpgf/gmetadefine.h"
#include "cpgf/metadata/gmetadataconfig.h"
#include "cpgf/metadata/private/gmetadata_header.h"
#include "cpgf/gmetapolicy.h"


using namespace gincu;


namespace meta_gincu { 


template <typename D>
void buildMetaClass_Global_gentitypolicy(D _d)
{
    (void)_d;
    using namespace cpgf;
    
    _d.CPGF_MD_TEMPLATE _enum<GEntityStoragePolicy>("GEntityStoragePolicy")
        ._element("dynamicArray", gincu::dynamicArray)
        ._element("dynamicMap", gincu::dynamicMap)
        ._element("staticArray", gincu::staticArray)
        ._element("mixedArray", gincu::mixedArray)
        ._element("mixedMap", gincu::mixedMap)
    ;
    _d.CPGF_MD_TEMPLATE _enum<long long>("GlobalDefine_gincu_2")
        ._element("GINCU_ENTITY_STORAGE_POLICY", GINCU_ENTITY_STORAGE_POLICY)
        ._element("GINCU_ENTITY_STORAGE_POLICY_INITIAL_SIZE", GINCU_ENTITY_STORAGE_POLICY_INITIAL_SIZE)
    ;
}


template <typename D, std::size_t InitialSize>
void buildMetaClass_GEntityDynamicArray(D _d)
{
    (void)_d;
    using namespace cpgf;
    
    _d.CPGF_MD_TEMPLATE _constructor<void * ()>();
}


template <typename D>
void buildMetaClass_GEntityDynamicArrayBase(D _d)
{
    (void)_d;
    using namespace cpgf;
    
    _d.CPGF_MD_TEMPLATE _constructor<void * (const std::size_t)>();
}


template <typename D>
void buildMetaClass_GEntityDynamicMap(D _d)
{
    (void)_d;
    using namespace cpgf;
    
}


template <typename D, const std::size_t ArraySize>
void buildMetaClass_GEntityMixedArray(D _d)
{
    (void)_d;
    using namespace cpgf;
    
}


template <typename D, const std::size_t ArraySize>
void buildMetaClass_GEntityMixedMap(D _d)
{
    (void)_d;
    using namespace cpgf;
    
}


template <typename D, const std::size_t ArraySize>
void buildMetaClass_GEntityStaticArray(D _d)
{
    (void)_d;
    using namespace cpgf;
    
}


template <typename D, GEntityStoragePolicy Policy, std::size_t InitialSize>
void buildMetaClass_GEntityStoragePolicySelector(D _d)
{
    (void)_d;
    using namespace cpgf;
    
}


template <typename D, std::size_t InitialSize>
void buildMetaClass_Gincu_GEntityStoragePolicySelector< GEntityStoragePolicy_dynamicArray, InitialSize >(D _d)
{
    (void)_d;
    using namespace cpgf;
    
}


template <typename D, std::size_t InitialSize>
void buildMetaClass_Gincu_GEntityStoragePolicySelector< GEntityStoragePolicy_dynamicMap, InitialSize >(D _d)
{
    (void)_d;
    using namespace cpgf;
    
}


template <typename D, std::size_t InitialSize>
void buildMetaClass_Gincu_GEntityStoragePolicySelector< GEntityStoragePolicy_mixedArray, InitialSize >(D _d)
{
    (void)_d;
    using namespace cpgf;
    
}


template <typename D, std::size_t InitialSize>
void buildMetaClass_Gincu_GEntityStoragePolicySelector< GEntityStoragePolicy_mixedMap, InitialSize >(D _d)
{
    (void)_d;
    using namespace cpgf;
    
}


template <typename D, std::size_t InitialSize>
void buildMetaClass_Gincu_GEntityStoragePolicySelector< GEntityStoragePolicy_staticArray, InitialSize >(D _d)
{
    (void)_d;
    using namespace cpgf;
    
}


} // namespace meta_gincu




#include "cpgf/metadata/private/gmetadata_footer.h"


#endif
