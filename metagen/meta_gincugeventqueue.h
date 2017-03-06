// Auto generated file, don't modify.

#ifndef CPGF_META_GINCUGEVENTQUEUE_H
#define CPGF_META_GINCUGEVENTQUEUE_H


#include "cpgf/gmetadefine.h"
#include "cpgf/metadata/gmetadataconfig.h"
#include "cpgf/metadata/private/gmetadata_header.h"
#include "cpgf/gmetapolicy.h"


using namespace gincu;


namespace meta_gincu { 


template <typename D>
void buildMetaClass_GEventQueue(D _d)
{
    (void)_d;
    using namespace cpgf;
    
    _d.CPGF_MD_TEMPLATE _constructor<void * ()>();
    _d.CPGF_MD_TEMPLATE _method("dispatchAll", &D::ClassType::dispatchAll);
    _d.CPGF_MD_TEMPLATE _method("addListener", (void (D::ClassType::*) (const GEventType, const GEventQueue::EventListener&, const GEvent::TagType))&D::ClassType::addListener)
        ._default(copyVariantFromCopyable((const GEvent::TagType)nullptr))
    ;
    _d.CPGF_MD_TEMPLATE _method("addListener", (void (D::ClassType::*) (const GEventQueue::EventListener&, const GEvent::TagType))&D::ClassType::addListener)
        ._default(copyVariantFromCopyable((const GEvent::TagType)nullptr))
    ;
    _d.CPGF_MD_TEMPLATE _method("removeListener", (void (D::ClassType::*) (const GEventType, const GEventQueue::EventListener&, const GEvent::TagType))&D::ClassType::removeListener)
        ._default(copyVariantFromCopyable((const GEvent::TagType)nullptr))
    ;
    _d.CPGF_MD_TEMPLATE _method("removeListener", (void (D::ClassType::*) (const GEventQueue::EventListener&, const GEvent::TagType))&D::ClassType::removeListener)
        ._default(copyVariantFromCopyable((const GEvent::TagType)nullptr))
    ;
    _d.CPGF_MD_TEMPLATE _method("send", &D::ClassType::send, cpgf::MakePolicy<cpgf::GMetaRuleCopyConstReference<0> >());
    _d.CPGF_MD_TEMPLATE _method("post", &D::ClassType::post, cpgf::MakePolicy<cpgf::GMetaRuleCopyConstReference<0> >());
    _d.CPGF_MD_TEMPLATE _method("dispatch", &D::ClassType::dispatch);
}


} // namespace meta_gincu




#include "cpgf/metadata/private/gmetadata_footer.h"


#endif
