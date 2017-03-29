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
    _d.CPGF_MD_TEMPLATE _method("createFloatAccessor", (FloatAccessor (*) (void *, cpgf::IMetaClass *, const std::string &, const std::string &))&createFloatAccessor, cpgf::MakePolicy<cpgf::GMetaRuleCopyConstReference<2>, cpgf::GMetaRuleCopyConstReference<3> >());
}


} // namespace meta_gincu




#include "cpgf/metadata/private/gmetadata_footer.h"


#endif
