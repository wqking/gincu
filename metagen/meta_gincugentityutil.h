// Auto generated file, don't modify.

#ifndef CPGF_META_GINCUGENTITYUTIL_H
#define CPGF_META_GINCUGENTITYUTIL_H


#include "cpgf/gmetadefine.h"
#include "cpgf/metadata/gmetadataconfig.h"
#include "cpgf/metadata/private/gmetadata_header.h"
#include "cpgf/gmetapolicy.h"


using namespace gincu;


namespace meta_gincu { 


template <typename D>
void buildMetaClass_Global_gentityutil(D _d)
{
    (void)_d;
    using namespace cpgf;
    
    _d.CPGF_MD_TEMPLATE _method("computeRenderableMatrix", (GMatrix44 (*) (const GComponentTransform *, const GSize &))&computeRenderableMatrix);
    _d.CPGF_MD_TEMPLATE _method("computeRenderableMatrix", (GMatrix44 (*) (const GComponentTransform *, const GComponentRender *))&computeRenderableMatrix)
        ._default(copyVariantFromCopyable<const GComponentRender *>((const GComponentRender *)nullptr))
    ;
    _d.CPGF_MD_TEMPLATE _method("getComponentManagerFromEntity", (GComponentManager * (*) (const GEntity *))&getComponentManagerFromEntity);
    _d.CPGF_MD_TEMPLATE _method("getParentLocalTransform", (GComponentLocalTransform * (*) (const GEntity *))&getParentLocalTransform);
    _d.CPGF_MD_TEMPLATE _method("getAncestor", (GEntity * (*) (GEntity *))&getAncestor);
    _d.CPGF_MD_TEMPLATE _method("getZOrder", (int (*) (GEntity *))&getZOrder);
}


} // namespace meta_gincu




#include "cpgf/metadata/private/gmetadata_footer.h"


#endif
