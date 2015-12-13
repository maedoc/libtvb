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
SK_DEFSCH(emcolor);
/*
def em_color(f, g, Δt, λ, x):
    i = 0
    nd = x.shape
    ϵ = sqrt(g(i, x) * λ) * randn(*nd)
    E = exp(-λ * Δt)
    while True:
	yield x, ϵ
	i += 1
	x += Δt * (f(i, x) + ϵ)
	h = sqrt(g(i, x) * λ * (1 - E**2)) * randn(*nd)
	ϵ = ϵ * E + h
*/

/* c.f. Manella 2002, O(2) in drift term, additive noise only */
SK_DEFSCH(heun);
/*

        call sys(x, fl, gl, Jf, Jg, c, par)
        call sys(x + dt * fl, fr, gr, Jf, Jg, c, par)
        call randn(z)
        x = x + 0.5_dp * (dt*(fl + fr) + sqrt(dt)*(gl + gr)*z)
*/

/* http://arxiv.org/pdf/1506.05708v1.pdf LL for mult noise  */
SK_DEFSCH(llmult);

#endif
