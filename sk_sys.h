/* Apache 2.0 INS-AMU 2015 */

#ifndef SK_SYS_H
#define SK_SYS_H

#include "sk_solv.h"

typedef struct {
    double a, tau, D;
} sk_sys_exc_dat;

SK_DEFSYS(sk_sys_exc);

#endif
