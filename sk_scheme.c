/* Apache 2.0 INS-AMU 2015 */

#include <math.h>

#include <stdlib.h>

#include "sk_scheme.h"
#include "sk_util.h"

int sk_sch_em_init(sk_sch_em_data *d, int nx)
{
	SK_MALLOCHECK(d->f=malloc(sizeof(double)*nx));
	SK_MALLOCHECK(d->g=malloc(sizeof(double)*nx));
	SK_MALLOCHECK(d->z=malloc(sizeof(double)*nx));
	return 0;
}

void sk_sch_em_free(sk_sch_em_data *d)
{
	free(d->f);
	free(d->g);
	free(d->z);
}

SK_DEFSCH(sk_sch_em)
{
	int i;
	double sqrt_dt;
	sk_sch_em_data *d = data;
	(*sys)(sysd, t, nx, x, d->f, d->g, NULL, NULL, nc, c);
	sk_util_fill_gauss(rng, nx, d->z);
	sqrt_dt = sqrt(dt);
	for (i=0; i<nx; i++)
		x[i] += dt * d->f[i] + sqrt_dt * d->g[i] * d->z[i];
	return 0;
}
