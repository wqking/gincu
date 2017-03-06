// Auto generated file, don't modify.


#include "gincu/gfont.h"

#include "meta_gincugfont.h"

using namespace cpgf;

namespace meta_gincu { 


#ifdef CPGF_METAGEN_LINKAGE_SPEC
CPGF_METAGEN_LINKAGE_SPEC
#endif
GDefineMetaInfo createMetaClass_GFont()
{
    GDefineMetaGlobalDangle _d = GDefineMetaGlobalDangle::dangle();
    {
        GDefineMetaClass<gincu::GFont> _nd = GDefineMetaClass<gincu::GFont>::lazyDeclare("GFont", &buildMetaClass_GFont);
        _d._class(_nd);
    }
    return _d.getMetaInfo();
}


#ifdef CPGF_METAGEN_LINKAGE_SPEC
CPGF_METAGEN_LINKAGE_SPEC
#endif
GDefineMetaInfo createMetaClass_GFontData()
{
    GDefineMetaGlobalDangle _d = GDefineMetaGlobalDangle::dangle();
    {
        GDefineMetaClass<gincu::GFontData> _nd = GDefineMetaClass<gincu::GFontData>::Policy<MakePolicy<GMetaRuleDefaultConstructorAbsent, GMetaRuleCopyConstructorAbsent> >::lazyDeclare("GFontData", &buildMetaClass_GFontData);
        _d._class(_nd);
    }
    return _d.getMetaInfo();
}


} // namespace meta_gincu


