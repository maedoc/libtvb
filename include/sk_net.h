/* Apache 2.0 INS-AMU 2015 */

#ifndef SK_NET_H
#define SK_NET_H

#include "sk_solv.h"

/* sk_net provides a sk_sys which adapts another sk_sys into a network.
 *
 * In TVB we have just a model & pre/post coupling functions, but post can be
 * folded into model as expression of afferent, and pre folded in as expression
 * pushed into efferent, so c array becomes in/out.
 */


/* TODO extend to heterogeneous node model */
struct sk_net_data {
    sk_sys node_sys;
    int nnz;
    double *nzw;
    void *node_data;
};

SK_DEFSYS(sk_net_sys);

#endif
