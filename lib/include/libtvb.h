/* copyright 2016 Apache 2 libtvb authors */

#ifndef TVB_H
#define TVB_H

#ifdef __cplusplus
extern "C" {
#endif

/* for bool, uint32_t & size_t types */ 
#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>

/* handle symbol export/import for MSVC/Windows */
#ifdef TVB_API_EXPORT
    #define TVB_API __declspec(dllexport)
#else
    #ifdef TVB_API_IMPORT
        #define TVB_API __declspec(dllimport)
    #else
        #define TVB_API
    #endif
#endif

/* cases where restrict not supported or not desired */
#ifdef TVB_NO_RESTRICT
#define restrict 
#endif

/* TODO look at test failures under single precision */
#ifdef TVB_USE_SINGLE_PRECISION
#define double float
#endif

#include "util/status.h"
#include "util/ver.h"
#include "util/malloc.h"
#include "util/misc.h"
#include "util/log.h"
#include "util/interface_macros.h"

#include "conn/base.h"

#include "rng.h"

#include "history.h"

#include "sys/base.h"
#include "sys/gen2d.h"
#include "sys/rww.h"
#include "sys/hmje.h"
#include "sys/wc.h"
#include "sys/net.h"

#include "out/sample.h"
#include "out/base.h"
#include "out/conv.h"
#include "out/fork.h"
#include "out/linop.h"
#include "out/mem.h"

#include "sch/interface.h"
#include "sch/constructors.h"

#include "sol/base.h"

#ifdef __cplusplus
}; /* extern "C" */
#endif

#endif /* TVB_H */