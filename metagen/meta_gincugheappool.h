// Auto generated file, don't modify.

#ifndef CPGF_META_GINCUGHEAPPOOL_H
#define CPGF_META_GINCUGHEAPPOOL_H


#include "cpgf/gmetadefine.h"
#include "cpgf/metadata/gmetadataconfig.h"
#include "cpgf/metadata/private/gmetadata_header.h"
#include "cpgf/gmetapolicy.h"


using namespace gincu;


namespace meta_gincu { 


template <typename D>
void buildMetaClass_Global_gheappool(D _d)
{
    (void)_d;
    using namespace cpgf;
    
    _d.CPGF_MD_TEMPLATE _enum<GHeapPoolPurgeStrategy>("GHeapPoolPurgeStrategy")
        ._element("never", gincu::GHeapPoolPurgeStrategy::never)
        ._element("onSceneFreed", gincu::GHeapPoolPurgeStrategy::onSceneFreed)
        ._element("onSceneSwitched", gincu::GHeapPoolPurgeStrategy::onSceneSwitched)
        ._element("onFree", gincu::GHeapPoolPurgeStrategy::onFree)
    ;
}


template <typename D>
void buildMetaClass_GHeapPool(D _d)
{
    (void)_d;
    using namespace cpgf;
    
    _d.CPGF_MD_TEMPLATE _constructor<void * (const std::size_t, const std::size_t, const GHeapPoolPurgeStrategy)>()
        ._default(copyVariantFromCopyable<const GHeapPoolPurgeStrategy>(GHeapPoolPurgeStrategy::onSceneSwitched))
        ._default(copyVariantFromCopyable<const std::size_t>(256))
        ._default(copyVariantFromCopyable<const std::size_t>(64))
    ;
    _d.CPGF_MD_TEMPLATE _method("getInstance", &D::ClassType::getInstance);
    _d.CPGF_MD_TEMPLATE _method("allocate", &D::ClassType::allocate);
    _d.CPGF_MD_TEMPLATE _method("free", &D::ClassType::free);
    _d.CPGF_MD_TEMPLATE _method("purge", &D::ClassType::purge);
    _d.CPGF_MD_TEMPLATE _method("getPurgeStrategy", &D::ClassType::getPurgeStrategy);
}


template <typename D, class T>
void buildMetaClass_GHeapPoolAllocator(D _d)
{
    (void)_d;
    using namespace cpgf;
    
    _d.CPGF_MD_TEMPLATE _constructor<void * ()>();
    _d.CPGF_MD_TEMPLATE _field("heapPool", &D::ClassType::heapPool);
    _d.CPGF_MD_TEMPLATE _method("allocate", &D::ClassType::allocate);
    _d.CPGF_MD_TEMPLATE _method("deallocate", &D::ClassType::deallocate);
}


inline bool opErAToRWrapper_GHeapSizedPool_ChunkRange__opLess(const GHeapSizedPool::ChunkRange * self, const GHeapSizedPool::ChunkRange& other) {
    return (*self) < other;
}


template <typename D>
void buildMetaClass_GHeapSizedPool(D _d)
{
    (void)_d;
    using namespace cpgf;
    
    _d.CPGF_MD_TEMPLATE _constructor<void * (const std::size_t, const std::size_t, const std::size_t, const GHeapPoolPurgeStrategy)>()
        ._default(copyVariantFromCopyable<const GHeapPoolPurgeStrategy>(GHeapPoolPurgeStrategy::onSceneSwitched))
        ._default(copyVariantFromCopyable<const std::size_t>(256))
        ._default(copyVariantFromCopyable<const std::size_t>(64))
    ;
    _d.CPGF_MD_TEMPLATE _method("allocate", (void * (D::ClassType::*) ())&D::ClassType::allocate);
    _d.CPGF_MD_TEMPLATE _method("allocate", (void * (D::ClassType::*) (const std::size_t))&D::ClassType::allocate);
    _d.CPGF_MD_TEMPLATE _method("free", &D::ClassType::free);
    _d.CPGF_MD_TEMPLATE _method("purge", &D::ClassType::purge);
}


} // namespace meta_gincu




#include "cpgf/metadata/private/gmetadata_footer.h"


#endif
