/* copyright 2016 Apache 2 sddekit authors */

#ifndef SDDEKIT_H
#define SDDEKIT_H

#ifdef __cplusplus
extern "C" {
#endif

/* for bool, uint32_t & size_t types */ 
#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>

/* handle symbol export/import for MSVC/Windows */
#ifdef SD_API_EXPORT
    #define SD_API __declspec(dllexport)
#else
    #ifdef SD_API_IMPORT
        #define SD_API __declspec(dllimport)
    #else
        #define SD_API
    #endif
#endif

/* cases where restrict not supported or not desired */
#ifdef SD_NO_RESTRICT
#define restrict 
#endif

/* TODO look at test failures under single precision */
#ifdef SD_USE_SINGLE_PRECISION
#define double float
#endif

#include "util/status.h"
#include "util/ver.h"
#include "util/malloc.h"
#include "util/misc.h"
#include "util/log.h"
#include "util/interface_macros.h"
#include "util/ocl.h"

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

#endif /* SDDEKIT_H */