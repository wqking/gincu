// Auto generated file, don't modify.

#ifndef CPGF_META_GINCUGLOG_H
#define CPGF_META_GINCUGLOG_H


#include "cpgf/gmetadefine.h"
#include "cpgf/metadata/gmetadataconfig.h"
#include "cpgf/metadata/private/gmetadata_header.h"
#include "cpgf/gmetapolicy.h"




namespace meta_gincu { 


template <typename D>
void buildMetaClass_Global_glog(D _d)
{
    (void)_d;
    using namespace cpgf;
    
    _d.CPGF_MD_TEMPLATE _enum<long long>("GlobalDefine_gincu_3")
        ._element("GINCU_LOG_LEVEL", GINCU_LOG_LEVEL)
        ._element("ZF_LOG_LEVEL", ZF_LOG_LEVEL)
        ._element("G_LOG_LEVEL_VERBOSE", G_LOG_LEVEL_VERBOSE)
        ._element("G_LOG_LEVEL_DEBUG", G_LOG_LEVEL_DEBUG)
        ._element("G_LOG_LEVEL_INFO", G_LOG_LEVEL_INFO)
        ._element("G_LOG_LEVEL_WARNING", G_LOG_LEVEL_WARNING)
        ._element("G_LOG_LEVEL_ERROR", G_LOG_LEVEL_ERROR)
        ._element("G_LOG_LEVEL_FATAL", G_LOG_LEVEL_FATAL)
        ._element("G_LOG_LEVEL_NONE", G_LOG_LEVEL_NONE)
        ._element("G_LOG_VERBOSE", G_LOG_VERBOSE)
        ._element("G_LOG_DEBUG", G_LOG_DEBUG)
        ._element("G_LOG_INFO", G_LOG_INFO)
        ._element("G_LOG_WARNING", G_LOG_WARNING)
        ._element("G_LOG_ERROR", G_LOG_ERROR)
        ._element("G_LOG_FATAL", G_LOG_FATAL)
        ._element("G_LOG_IF", G_LOG_IF)
    ;
}


} // namespace meta_gincu




#include "cpgf/metadata/private/gmetadata_footer.h"


#endif
