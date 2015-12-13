/* Apache 2.0 INS-AMU 2015 */

#include "sk_net.h"

static void init(struct sk_net *n, int nx, int nc)
{
}

int sk_net_sys(int nx, double *x, double *f, double *g, 
               double *Jf, double *Jg, int nc, double *c, void *data)
{
    struct sk_net *n = (struct sk_net*) data;

    if (x==NULL)
        init(n, nx, nc);
}
