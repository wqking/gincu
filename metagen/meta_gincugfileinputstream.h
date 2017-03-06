// Auto generated file, don't modify.

#ifndef CPGF_META_GINCUGFILEINPUTSTREAM_H
#define CPGF_META_GINCUGFILEINPUTSTREAM_H


#include "cpgf/gmetadefine.h"
#include "cpgf/metadata/gmetadataconfig.h"
#include "cpgf/metadata/private/gmetadata_header.h"
#include "cpgf/gmetapolicy.h"


using namespace gincu;


namespace meta_gincu { 


template <typename D>
void buildMetaClass_GFileInputStream(D _d)
{
    (void)_d;
    using namespace cpgf;
    
    _d.CPGF_MD_TEMPLATE _constructor<void * ()>();
    _d.CPGF_MD_TEMPLATE _constructor<void * (const std::string &)>();
    _d.CPGF_MD_TEMPLATE _method("open", &D::ClassType::open);
    _d.CPGF_MD_TEMPLATE _method("close", &D::ClassType::close);
    _d.CPGF_MD_TEMPLATE _method("read", &D::ClassType::read);
    _d.CPGF_MD_TEMPLATE _method("seek", &D::ClassType::seek);
    _d.CPGF_MD_TEMPLATE _method("tell", &D::ClassType::tell);
    _d.CPGF_MD_TEMPLATE _method("getSize", &D::ClassType::getSize);
}


template <typename D>
void buildMetaClass_GFileInputStreamData(D _d)
{
    (void)_d;
    using namespace cpgf;
    
    _d.CPGF_MD_TEMPLATE _method("open", &D::ClassType::open);
    _d.CPGF_MD_TEMPLATE _method("read", &D::ClassType::read);
    _d.CPGF_MD_TEMPLATE _method("seek", &D::ClassType::seek);
    _d.CPGF_MD_TEMPLATE _method("tell", &D::ClassType::tell);
    _d.CPGF_MD_TEMPLATE _method("getSize", &D::ClassType::getSize);
}


} // namespace meta_gincu




#include "cpgf/metadata/private/gmetadata_footer.h"


#endif
