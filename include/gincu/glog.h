#ifndef GLOG_H
#define GLOG_H

#ifndef GINCU_LOG_LEVEL
#define GINCU_LOG_LEVEL G_LOG_LEVEL_INFO
#endif

#define ZF_LOG_LEVEL GINCU_LOG_LEVEL

#define G_LOG_LEVEL_VERBOSE		ZF_LOG_VERBOSE	/* 1 */
#define G_LOG_LEVEL_DEBUG		ZF_LOG_DEBUG	/* 2 */
#define G_LOG_LEVEL_INFO		ZF_LOG_INFO		/* 3 */
#define G_LOG_LEVEL_WARNING		ZF_LOG_WARN		/* 4 */
#define G_LOG_LEVEL_ERROR		ZF_LOG_ERROR	/* 5 */
#define G_LOG_LEVEL_FATAL		ZF_LOG_FATAL	/* 6 */
#define G_LOG_LEVEL_NONE		ZF_LOG_NONE		/* 0xff */

#define G_LOG_VERBOSE	ZF_LOGV
#define G_LOG_DEBUG		ZF_LOGD
#define G_LOG_INFO		ZF_LOGI
#define G_LOG_WARNING	ZF_LOGW
#define G_LOG_ERROR		ZF_LOGE
#define G_LOG_FATAL		ZF_LOGF

#include "zf_log.h"

#endif
