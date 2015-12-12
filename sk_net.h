/* Apache 2.0 INS-AMU 2015 */

#ifndef SK_NET_H
#define SK_NET_H

#include "sk_sys.h"

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

int sk_net_sys(int nx, double *x, double *f, double *g, 
               double *Jf, double *Jg, int nc, double *c, void *data);

#endif
