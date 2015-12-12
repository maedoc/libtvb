/* Apache 2.0 INS-AMU 2015 */

#include "stdlib.h"
#include "string.h"
#include "math.h"

#include "sk_util.h"
#include "sk_hist.h"


static void setup_buffer_structure(struct sk_hist *h)
{
	int i, j, ui;
	double maxd;

	SK_MALLOCHECK(h->maxd = malloc (sizeof(double) * h->nu));
	SK_MALLOCHECK(h->lim = malloc (sizeof(double) * (h->nu + 1)));
	SK_MALLOCHECK(h->len = malloc (sizeof(double) * h->nu));
	SK_MALLOCHECK(h->pos = malloc (sizeof(double) * h->nu));

	/* vi2i requires max(uvi) then filling in vi2i[ui]=i */
	h->maxvi = 0;
	for (i=0; i<h->nu; i++)
		if (h->uvi[i] > h->maxvi)
			h->maxvi = h->uvi[i];

	SK_MALLOCHECK(h->vi2i = malloc (sizeof(int) * (h->maxvi + 1)));

	for (i=0; i<h->nu; i++)
	{
		ui = h->uvi[i];
		h->vi2i[ui] = i;
		maxd = 0.0;
		/* TODO double check */
		for (j=0; j<h->nd; j++)
			if (h->vi[j]==ui && h->del[j]>maxd)
				maxd = h->del[j];
		h->maxd[i] = maxd;
		h->len[i] = ceil(maxd / h->dt) + 2;
		h->pos[i] = 0;
		if (i==0)
			h->lim[i] = 0;
		else
			h->lim[i] = h->pos[i-1] + h->len[i-1];
	}
	h->lim[h->nu] = h->lim[h->nu-1] + h->len[h->nu-1];
}

void sk_hist_init(struct sk_hist *h, int nd, int *vi, double *vd, double t0, double dt)
{
	h->dt = dt;
	h->t = t0;
	h->nd = nd;

	/* identify unique delayed variable indices
	 * NB: this allocates h->uci
	 */
	sk_util_uniqi(nd, vi, &(h->nu), &(h->uvi));

	/* alloc & copy the delay values */
	SK_MALLOCHECK(h->del = malloc (sizeof(double) * nd));
	memcpy(h->del, vd, nd * sizeof(double));

	/* and indices */
	SK_MALLOCHECK(h->vi = malloc (sizeof(int) * nd));
	memcpy(h->vi, vi, nd * sizeof(int));

	/* setup maxd, off, len, pos */
	setup_buffer_structure(h);

	/* alloc buf */
	SK_MALLOCHECK(h->buf = malloc (sizeof(double) * h->lim[h->nu]));
}

void sk_hist_free(struct sk_hist *h)
{
	free(h->uvi);
	free(h->del);
	free(h->vi);
	free(h->maxd);
	free(h->lim);
	free(h->len);
	free(h->pos);
    free(h->vi2i);
    free(h->buf);
}

void sk_hist_fill(struct sk_hist *h, sk_hist_filler filler)
{
	int i, j, ui, o, n, *vi;
	double *t;

	n = h->lim[h->nu];
	SK_MALLOCHECK(t = malloc (sizeof(double) * n));
	SK_MALLOCHECK(vi = malloc (sizeof(int) * n));

	/* expand indices per buffer element */
	for (i=0; i<h->nu; i++)
	{
		ui = h->uvi[i];
		for (j=h->lim[i]; j<h->lim[i+1]; j++)
			vi[j] = ui;
	}
	
	/* evaluate time per buffer element */
	for (i=0; i<h->nu; i++)
	{
		for (j=0; j<(h->len[i]-1); j++)
		{
			o = h->pos[i]; 	   /* current position in buffer */
			o += j;            /* time step through buffer */
			o %= h->len[i];    /* wrap around on section length */
			o += h->lim[i];    /* offset to start of section */
			t[o] = h->t - j * h->dt;
		}
		j = h->len[i] - 1;
		o = h->pos[i]; 	   /* current position in buffer */
		o += j;            /* time step through buffer */
		o %= h->len[i];    /* wrap around on section length */
		o += h->lim[i];    /* offset to start of section */
		t[o] = h->t + h->dt; /* last point is next grid point */
	}

	filler(n, t, vi, h->buf);

	free(t);
	free(vi);
}

void sk_hist_get(struct sk_hist *h, double t, double *c)
{
	int i, i0, i1, ui;

	for (i=0; i<h->nd; i++)
	{
		ui = h->vi2i[h->vi[i]];
		i0 = h->pos[ui] - floor((t - h->del[i] - h->t) / h->dt);
		i0 %= h->len[ui];
		i1 = i0 ? i0 - 1 : h->len[ui]-1;
		i0 += h->lim[ui];
		i1 += h->lim[ui];

#ifdef SKDEBUG
        if ((i0 < 0) || (i0 > h->lim[h->nu]))
            fprintf(stderr, "[sk_hist] oob i0=%d %s:%d\n", i0, __FILE__, __LINE__);
        if ((i1 < 0) || (i1 > h->lim[h->nu]))
            fprintf(stderr, "[sk_hist] oob i1=%d %s:%d\n", i1, __FILE__, __LINE__);
#endif
		c[i] = (h->buf[i1] - h->buf[i0]) / h->dt
			* fmod((t + h->del[i]), h->dt) + h->buf[i0];
	}
}

static void update_time(struct sk_hist *h, double new_t)
{
	int i, n_steps;

	/* the current time must always be contained between 
	 * pos and pos-1 in the buffer
	 */
	n_steps = 0;
	while ((h->t + h->dt) < new_t)
	{
		h->t += h->dt;
		n_steps++;
	}

	/* if no steps to take, return early */
	if (n_steps==0)
		return;

	/* update positions */
	for (i=0; i<h->nu; i++)
	{
		h->pos[i] -= n_steps;
		if (h->pos[i] < 0)
			h->pos[i] += h->len[i];
	}
}

void sk_hist_set(struct sk_hist *h, double t, double *x)
{
	int i, i0, i1;
	double x0, dx, dt;

	update_time(h, t);

	/* extrapolate from (x(h->t), x(t)) to next grid point*/
	for (i=0; i<h->nu; i++)
	{
		i0 = h->pos[i];
		i1 = i0 ? i0 - 1 : h->len[i] - 1;
		i0 += h->lim[i];
		i1 += h->lim[i];
		x0 = h->buf[i0];
		dt = t - h->t;
		dx = x[h->uvi[i]] - h->buf[i0];
		h->buf[i1] = (dx / dt) * h->dt + x0;
	}
}

int sk_hist_nbytes(struct sk_hist *h)
{
	int nb;
	nb = sizeof(struct sk_hist);
	nb += sizeof(int) * ((h->nu+1) + 3*h->nu + h->nd + h->maxvi);
	nb += sizeof(double) * (h->lim[h->nu] + h->nu + h->nd);
	return nb;
}
