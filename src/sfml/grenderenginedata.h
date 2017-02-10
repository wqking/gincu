#include "grenderengineconfig.h"

// the implementation is include corresponding renderengine cpp

#if GINCU_MULTI_THREAD_RENDER
#include "grenderenginedatamultithread.h"
#else
#include "grenderenginedatasinglethread.h"
#endif
