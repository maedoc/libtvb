/* Apache 2.0 INS-AMU 2015 */

#include <stdlib.h>
#include <string.h>

#include "sk_test.h"
#include "sk_hist.h"

void hist_t_fill(int n, double *t, int *indices, double *buf)
{
    memcpy(buf, t, n*sizeof(double));
    indices[0] = indices[0]; /* avoid unused warning */
}
#define ND 3

int test_hist()
{
    int i, vi[ND], nb;
    double dt, vd[ND], x[43];
    struct sk_hist *h;

    /* set up */
    dt = 0.1;
    vi[0] = 42;
    vi[1] = 42;
    vi[2] = 31;
    vd[0] = 5.5 * dt;
    vd[1] = 4.5 * dt;
    vd[2] = 33.3 * dt;
    h = malloc (sizeof(struct sk_hist));

    sk_hist_init(h, ND, vi, vd, dt);
    sk_test_true(h->nd==ND);
    sk_test_true(h->t==0.0);
    sk_test_true(h->dt==dt);
    sk_test_true(h->nu==2);
    sk_test_true(h->lim[0]==0);
    sk_test_true(h->lim[1]==36);
    sk_test_true(h->lim[2]==8 + 36);
    sk_test_true(h->len[0]==36);
    sk_test_true(h->len[1]==8);
    sk_test_true(h->pos[0]==0);
    sk_test_true(h->pos[1]==0);
    sk_test_true(h->uvi[0]==31);
    sk_test_true(h->uvi[1]==42);
    sk_test_true(h->maxvi==42);
    sk_test_true(h->vi2i[31]==0);
    sk_test_true(h->vi2i[42]==1);
    sk_test_true(h->maxd[1]==vd[0]);
    sk_test_true(h->maxd[0]==vd[2]);
    sk_test_true(h->vi[0]==42);
    sk_test_true(h->vi[1]==42);
    sk_test_true(h->vi[2]==31);
    sk_test_true(h->del[0]==vd[0]);
    sk_test_true(h->del[1]==vd[1]);
    sk_test_true(h->del[2]==vd[2]);
    sk_test_true(h->buf!=NULL);

    sk_hist_fill(h, &hist_t_fill);
    for (i=0; i<35; i++)
        sk_test_true(h->buf[i]==-i*dt);
    sk_test_true(h->buf[35]==dt);
    for (i=0; i<7; i++)
        sk_test_true(h->buf[36+i]==-i*dt);
    sk_test_true(h->buf[36+7]==dt);

    sk_hist_get(h, dt/3, x);
    sk_test_tol(x[0], -vd[0]+dt/3, 1e-15);
    sk_test_tol(x[1], -vd[1]+dt/3, 1e-15);

    x[31] = 1.5;
    x[42] = 1.0;
    sk_hist_set(h, dt/2.0, x);
    sk_test_tol(h->buf[35], 3.0, 1e-15);
    sk_test_tol(h->buf[36 + 7], 2.0, 1e-15);

    nb = sizeof(struct sk_hist);
    nb += sizeof(int) * (3+2+2+2+3+42);
    nb += sizeof(double) * (44+2+3);
    sk_test_true(nb == sk_hist_nbytes(h));

	return 0;
}
