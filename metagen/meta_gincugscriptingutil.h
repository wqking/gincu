// Auto generated file, don't modify.

#ifndef CPGF_META_GINCUGSCRIPTINGUTIL_H
#define CPGF_META_GINCUGSCRIPTINGUTIL_H


#include "cpgf/gmetadefine.h"
#include "cpgf/metadata/gmetadataconfig.h"
#include "cpgf/metadata/private/gmetadata_header.h"
#include "cpgf/gmetapolicy.h"


using namespace gincu;


namespace meta_gincu { 


template <typename D>
void buildMetaClass_Global_gscriptingutil(D _d)
{
    (void)_d;
    using namespace cpgf;
    
    _d.CPGF_MD_TEMPLATE _method("intializeScriptEngine", (void (*) (const GScriptLanguage))&intializeScriptEngine);
    _d.CPGF_MD_TEMPLATE _method("finalizeScriptEngine", (void (*) (const GScriptLanguage))&finalizeScriptEngine);
    _d.CPGF_MD_TEMPLATE _method("createScriptRunner", (cpgf::GScriptRunner * (*) (const GScriptLanguage))&createScriptRunner);
    _d.CPGF_MD_TEMPLATE _enum<GScriptLanguage>("GScriptLanguage")
        ._element("slV8Javascript", gincu::GScriptLanguage::slV8Javascript)
        ._element("slSpiderMonkeyJavaScript", gincu::GScriptLanguage::slSpiderMonkeyJavaScript)
        ._element("slLua", gincu::GScriptLanguage::slLua)
        ._element("slPython", gincu::GScriptLanguage::slPython)
    ;
}


} // namespace meta_gincu




#include "cpgf/metadata/private/gmetadata_footer.h"


#endif
