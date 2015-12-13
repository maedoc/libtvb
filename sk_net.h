/* Apache 2.0 INS-AMU 2015 */

#ifndef SK_NET_H
#define SK_NET_H

#include "sk_solv.h"

/* sk_net provides a sk_sys which adapts another sk_sys into a network.
 *
 * In TVB we have just a model & pre/post coupling functions, but post can be
 * folded into model as expression of afferent, and pre folded in as a auxiliary.
 * The only challenge is that auxiliary must be evaluated also by sys before
 * calculating connectivity.
 *
 * To handlea further extension, we wish to allow for hybrid models where different
 * nodes have different models.
 */

typedef void (*sk_net_pre)(int nx, double *xj, double *xi);
typedef void (*sk_net_post)(int nx, double *gx);

struct sk_net {
    sk_net_pre pre;
    sk_net_post post;
    sk_sys node_sys;
    int nnz;
    double *nzw;
    void *data;
};

SK_DEFSYS(sk_net_sys);

#endif
