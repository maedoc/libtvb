/* Apache 2.0 INS-AMU 2015 */

#ifndef SK_SCHEME_H
#define SK_SCHEME_H

#include "sk_solv.h"

/* Euler-Maruyama O(1) general purpose */
typedef struct {
	double *f, *g, *z;
} sk_sch_em_data;

int sk_sch_em_init(sk_sch_em_data *d, int nx);

void sk_sch_em_free(sk_sch_em_data *d);

SK_DEFSCH(sk_sch_em);

/* E-M for colored noise, derived from Fox 1998, 
 * (no proof of convergence for multiplicate noise!)
 */
typedef struct { 
	int first_call;
	double *f, *g, *z, *eps, lam; 
} sk_sch_emcolor_data;

int sk_sch_emcolor_init(sk_sch_emcolor_data *d, int nx, double lam);

void sk_sch_emcolor_free(sk_sch_emcolor_data *d);

SK_DEFSCH(sk_sch_emcolor);

/* c.f. Manella 2002, O(2) in drift term, additive noise only */
typedef struct {
	double *fl, *fr, *gl, *gr, *z, *xr;
} sk_sch_heun_data;

int sk_sch_heun_init(sk_sch_heun_data *d, int nx);

void sk_sch_heun_free(sk_sch_heun_data *d);

SK_DEFSCH(sk_sch_heun);

/* TODO http://arxiv.org/pdf/1506.05708v1.pdf LL for mult noise  */
SK_DEFSCH(llmult);

#endif
