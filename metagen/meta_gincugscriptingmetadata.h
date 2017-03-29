// Auto generated file, don't modify.

#ifndef CPGF_META_GINCUGSCRIPTINGMETADATA_H
#define CPGF_META_GINCUGSCRIPTINGMETADATA_H


#include "cpgf/gmetadefine.h"
#include "cpgf/metadata/gmetadataconfig.h"
#include "cpgf/metadata/private/gmetadata_header.h"
#include "cpgf/gmetapolicy.h"


using namespace gincu;


namespace meta_gincu { 


template <typename D>
void buildMetaClass_Global_gscriptingmetadata(D _d)
{
    (void)_d;
    using namespace cpgf;
    
    _d.CPGF_MD_TEMPLATE _method("createOnTouchedCallback", (OnTouchCallback (*) (cpgf::IScriptFunction *))&createOnTouchedCallback);
    _d.CPGF_MD_TEMPLATE _method("createFloatAccessor", (FloatAccessor (*) (const cpgf::GVariant &, const std::string &, const std::string &))&createFloatAccessor, cpgf::MakePolicy<cpgf::GMetaRuleCopyConstReference<1>, cpgf::GMetaRuleCopyConstReference<2> >());
    _d.CPGF_MD_TEMPLATE _method("createSharedPointer", (std::shared_ptr< void > (*) (const cpgf::GVariant &))&createSharedPointer);
}


} // namespace meta_gincu




#include "cpgf/metadata/private/gmetadata_footer.h"


#endif
