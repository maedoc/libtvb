/* Apache 2.0 INS-AMU 2015 */

#include "stdlib.h"
#include "string.h"
#include "math.h"

#include "sk_util.h"
#include "sk_hist.h"
#include "sk_malloc.h"

static void setup_buffer_structure(sk_hist *h)
{
	int i, j, ui;
	double maxd;

	h->maxd = sk_malloc (sizeof(double) * h->nu);
	h->lim = sk_malloc (sizeof(double) * (h->nu + 1));
	h->len = sk_malloc (sizeof(double) * h->nu);
	h->pos = sk_malloc (sizeof(double) * h->nu);

	/* vi2i requires max(uvi) then filling in vi2i[ui]=i */
	h->maxvi = 0;
	for (i=0; i<h->nu; i++)
		if (h->uvi[i] > h->maxvi)
			h->maxvi = h->uvi[i];

	h->vi2i = sk_malloc (sizeof(int) * (h->maxvi + 1));

	for (i=0; i<h->nu; i++)
	{
		ui = h->uvi[i];
		h->vi2i[ui] = i;
		maxd = 0.0;
		for (j=0; j<h->nd; j++)
			if (h->vi[j]==ui && h->del[j]>maxd)
				maxd = h->del[j];
		h->maxd[i] = maxd;
		h->len[i] = ceil(maxd / h->dt) + 2;
		h->pos[i] = 0;
		if (i==0)
			h->lim[i] = 0;
		else
			h->lim[i] = h->lim[i-1] + h->len[i-1];
	}
	h->lim[h->nu] = h->lim[h->nu-1] + h->len[h->nu-1];
}

void sk_hist_init(sk_hist * restrict h, int nd, int * restrict vi, double * restrict vd, double t0, double dt)
{
	h->dt = dt;
	h->t = t0;
	h->nd = nd;

	/* identify unique delayed variable indices
	 * NB: this allocates h->uci
	 */
	sk_util_uniqi(nd, vi, &(h->nu), &(h->uvi));

	/* alloc & copy the delay values */
	h->del = sk_malloc (sizeof(double) * nd);
	memcpy(h->del, vd, nd * sizeof(double));

	/* and indices */
	h->vi = sk_malloc (sizeof(int) * nd);
	memcpy(h->vi, vi, nd * sizeof(int));

	/* setup maxd, off, len, pos */
	setup_buffer_structure(h);

	/* alloc buf */
	h->buf = sk_malloc (sizeof(double) * h->lim[h->nu]);
}

void sk_hist_free(sk_hist *h)
{
	sk_free(h->uvi);
	sk_free(h->del);
	sk_free(h->vi);
	sk_free(h->maxd);
	sk_free(h->lim);
	sk_free(h->len);
	sk_free(h->pos);
	sk_free(h->vi2i);
	sk_free(h->buf);
}

void sk_hist_fill(sk_hist * restrict h, sk_hist_filler filler, void * restrict fill_data)
{
	int i, j, ui, o, n, *vi;
	double *t;

	n = h->lim[h->nu];
	t = sk_malloc (sizeof(double) * n);
	vi = sk_malloc (sizeof(int) * n);

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

	filler(fill_data, n, t, vi, h->buf);

	sk_free(t);
	sk_free(vi);
}

void sk_hist_get(sk_hist * restrict h, double t, double * restrict aff)
{
	int i;

	if (h==NULL)
		return;

	for (i = 0; i < h->nd; i++)
	{
		int ui, i0, i1, p, l, o;
		double dt, y0, y1, m, dx;

		ui = h->vi2i[h->vi[i]];
		p = h->pos[ui];
		l = h->len[ui];
		o = h->lim[ui];

		dt = (t - h->del[i]) - (h->t - (l - 2)*h->dt);

		i0 = (int)ceil((l - 2) - dt / h->dt);
		i1 = i0 ? i0 - 1 : l - 1;

		/* bottleneck */
		y0 = h->buf[(p + i0) % l + o];
		y1 = h->buf[(p + i1) % l + o];

		m = (y1 - y0) / h->dt;

		dx = (t - h->del[i]) - (h->t - i0*h->dt);

		aff[i] = m * dx + y0;
		continue;
	}
}

static void update_time(sk_hist *h, double new_t)
{
	int i, n_steps;

	/* the current time must always be contained between 
	 * pos and pos-1 in the buffer
	 * 
	 * TODO handle case of irregular time step where new_t could 
	 * be several h->dt ahead, and we need to fill in the buffer
	 * correctly.
	 */
	n_steps = 0;
	while ((h->t + h->dt) <= new_t)
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

void sk_hist_set(sk_hist * restrict h, double t, double * restrict eff)
{
	int i, i0, i1;
	double x0, dx, dt;

	if (h==NULL)
		return;

	update_time(h, t);

	for (i=0; i<h->nu; i++)
	{
		i0 = h->pos[i];
		i1 = i0 ? i0 - 1 : h->len[i] - 1;
		i0 += h->lim[i];
		i1 += h->lim[i];
#ifdef SKDEBUG
        if ((i0 < h->lim[i]) || (i0 > h->lim[i+1]))
            fprintf(stderr, "[sk_hist_set] t=%.3f ui=%d, i0=%d not in [%d,%d) %s:%d\n", 
		    t, i, i0, h->lim[i], h->lim[i+1], __FILE__, __LINE__);
        if ((i1 < h->lim[i]) || (i1 > h->lim[i+1]))
            fprintf(stderr, "[sk_hist_set] t=%.3f ui=%d, i1=%d not in [%d,%d) %s:%d\n", 
		    t, i, i1, h->lim[i], h->lim[i+1], __FILE__, __LINE__);
#endif
		x0 = h->buf[i0];
		dt = t - h->t;

#ifdef SKDEBUG
		if (dt < 0)
			fprintf(stderr, "[sk_hist] unhandled dt<0 at %s:%d\n", __FILE__, __LINE__);
#endif

		if (dt > 0) {
			/* extrapolate from (x(h->t), x(t)) to next grid point*/
			dx = eff[h->vi2i[h->uvi[i]]] - h->buf[i0];
			h->buf[i1] = (dx / dt) * h->dt + x0;
		} else {
			/* reset grid point value */
			h->buf[i0] = eff[h->vi2i[h->uvi[i]]];
		}
	}
}

int sk_hist_nbytes(sk_hist *h)
{
	int nb;
	nb = sizeof(sk_hist);
	nb += sizeof(int) * ((h->nu+1) + 3*h->nu + h->nd + h->maxvi);
	nb += sizeof(double) * (h->lim[h->nu] + h->nu + h->nd);
	return nb;
}

void sk_hist_zero_filler(void * restrict data, int n, double * restrict t, int * restrict indices, double * restrict buf)
{
	int i;
	/* suppress unused parameter warnings */
	(void) data; (void) n; (void) t; (void) indices;
	for (i=0; i<n; i++)
		buf[i] = 0.0;
}
