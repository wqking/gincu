#include "grenderengineconfig.h"

#if GINCU_MULTI_THREAD_RENDER
#include "grenderenginedatamultithread.h"
#else
#include "grenderenginedatasinglethread.h"
#endif
