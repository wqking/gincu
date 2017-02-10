#include "grenderengineconfig.h"

#if GINCU_MULTI_THREAD_RENDER
#include "grenderenginedatamultithread.hxx"
#else
#include "grenderenginedatasinglethread.hxx"
#endif
