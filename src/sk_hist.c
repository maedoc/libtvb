/* copyright 2016 Apache 2 sddekit authors */

#include "stdlib.h"
#include "string.h"
#include "math.h"

#include "sk_util.h"
#include "sk_hist.h"
#include "sk_malloc.h"
#include "sk_log.h"
#include "sk_err.h"

struct sk_hist
{
	/*           nu+1   nu    nu    nu   nd, maxvi */
	int nd, nu, *lim, *len, *pos, *uvi, *vi, *vi2i, maxvi;
	/*   sum(len)  nu     nd 		*/
	double *buf, *maxd, *del, dt, t;
};

sk_hist *sk_hist_alloc() {
	sk_hist *new, zero = {0};
	new = sk_malloc(sizeof(sk_hist));
	*new = zero;
	return new;
}

int sk_hist_get_maxvi(sk_hist *h) {
	return h->maxvi;
}

int sk_hist_get_vi2i(sk_hist *h, int vi) {
	return h->vi2i[vi];
}

static int setup_buffer_structure(sk_hist *h)
{
	int i, j, ui;
	double maxd;
	char *errmsg;

	if (
		(h->maxd = sk_malloc (sizeof(double) * h->nu))==NULL ||
		(h->lim = sk_malloc (sizeof(double) * (h->nu + 1)))==NULL ||
		(h->len = sk_malloc (sizeof(double) * h->nu))==NULL ||
		(h->pos = sk_malloc (sizeof(double) * h->nu))==NULL
	   ) {
		errmsg = "failed to alloc internal storage.";
		goto fail;
	}


	/* vi2i requires max(uvi) then filling in vi2i[ui]=i */
	h->maxvi = 0;
	for (i=0; i<h->nu; i++)
		if (h->uvi[i] > h->maxvi)
			h->maxvi = h->uvi[i];

	if ((h->vi2i = sk_malloc (sizeof(int) * (h->maxvi + 1)))==NULL) {
		errmsg = "failed to alloc internal storage.";
		goto fail;
	}

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
	return 0;
fail:
	if (h->maxd!=NULL) sk_free(h->maxd);
	if (h->lim!=NULL) sk_free(h->lim);
	if (h->len!=NULL) sk_free(h->len);
	if (h->pos!=NULL) sk_free(h->pos);
	if (h->vi2i!=NULL) sk_free(h->vi2i);
	sk_err(errmsg);
	return 1;
}

int sk_hist_init(sk_hist * restrict h, int nd, int * restrict vi, double * restrict vd, double t0, double dt)
{
	char *errmsg;
#define FAILIF(cond, msg) if (cond) { \
		errmsg = msg; \
		goto fail; \
	}
	h->dt = dt;
	h->t = t0;
	FAILIF((h->nd = nd)<1, "at least one delay required to init history.")
	FAILIF(sk_util_uniqi(nd, vi, &(h->nu), &(h->uvi)),
		"failed to make list of unique delay var indices.")
	FAILIF((h->del = sk_malloc (sizeof(double) * nd))==NULL,
		"failed to alloc internal delay array.");
	memcpy(h->del, vd, nd * sizeof(double));
	FAILIF((h->vi = sk_malloc (sizeof(int) * nd))==NULL,
		"failed to allocate internal index array.")
	memcpy(h->vi, vi, nd * sizeof(int));
	FAILIF(setup_buffer_structure(h),
		"failed to build internal buffer structure");
	FAILIF((h->buf = sk_malloc (sizeof(double) * h->lim[h->nu]))==NULL,
		"failed to allocate history buffer.")
#undef FAILIF
	return 0;
fail:
	if (h->buf!=NULL) sk_free(h->buf);
	if (h->uvi!=NULL) sk_free(h->uvi);
	if (h->del!=NULL) sk_free(h->del);
	if (h->vi!=NULL) sk_free(h->vi);
	sk_err(errmsg);
	return 1;
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
	sk_free(h);
}

int sk_hist_fill(sk_hist * restrict h, sk_hist_filler filler, void * restrict fill_data)
{
	int i, j, ui, o, n, *vi;
	double *t;
	char *errmsg;
	errmsg = NULL;

	n = h->lim[h->nu];
	if ((t = sk_malloc (sizeof(double) * n))==NULL ||
		(vi = sk_malloc (sizeof(int) * n))==NULL) {
		errmsg = "failed to allocate memory for evaluating hist fill.";
		goto end;
	}

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

	if (filler(fill_data, n, t, vi, h->buf))
		errmsg = "hist filler failed.";

end:
	if (t!=NULL) sk_free(t);
	if (vi!=NULL) sk_free(vi);

	return (int) errmsg;
}

void sk_hist_get(sk_hist * restrict h, double t, double * restrict aff)
{
	int i;

	if (h==NULL)
		return;

	for (i = 0; i < h->nd; i++)
	{
		int ui, i0, i1, i0_, i1_, p, l, o;
		double dt, y0, y1, m, dx;

		ui = h->vi2i[h->vi[i]];
		p = h->pos[ui];
		l = h->len[ui];
		o = h->lim[ui];

		dt = (t - h->del[i]) - (h->t - (l - 2)*h->dt);

		i0 = (int)ceil((l - 2) - dt / h->dt);
		if (i0 < 0)
			i0 += l;
		i1 = i0 ? i0 - 1 : l - 1;

		i0_ = (p + i0) % l + o;
		i1_ = (p + i1) % l + o;

#ifdef SKDEBUG
		if ((i0_ < h->lim[ui]) || (i0_ >= h->lim[ui+1]))
			sk_log_debug( "[sk_hist_get] oob: i0_=%d not in [%d, %d) at %s:%d\n", i0_, h->lim[ui], h->lim[ui+1], __FILE__, __LINE__ );
		if ((i1_ < h->lim[ui]) || (i1_ >= h->lim[ui+1]))
			sk_log_debug( "[sk_hist_get] oob: i1_=%d not in [%d, %d) at %s:%d\n", i1_, h->lim[ui], h->lim[ui+1], __FILE__, __LINE__ );
#endif

		/* bottleneck */
		y0 = h->buf[i0_];
		y1 = h->buf[i1_];

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
			sk_log_debug( "[sk_hist] unhandled dt<0 at %s:%d\n", __FILE__, __LINE__ );
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

int sk_hist_zero_filler(void * restrict data, int n, double * restrict t, int * restrict indices, double * restrict buf)
{
	int i;
	/* suppress unused parameter warnings */
	(void) data; (void) n; (void) t; (void) indices;
	for (i=0; i<n; i++)
		buf[i] = 0.0;
	return 0;
}

int sk_hist_get_nu(sk_hist *h) {
	return h->nu;
}

double sk_hist_get_buf_lin(sk_hist *h, int index) {
#ifdef SKDEBUG
	if ((index < 0) || (index >= h->lim[h->nu]))
		sk_log_debug( "[sk_hist_get_buf_lin] oob index=%d not in [0, %d)\n", index, h->lim[h->nu] );
#endif
	return h->buf[index];
}

double sk_hist_get_t(sk_hist *h) {
	return h->t;
}

double sk_hist_get_dt(sk_hist *h) {
	return h->dt;
}

int sk_hist_get_lim(sk_hist *h, int i) {
	return h->lim[i];
}

int sk_hist_get_len(sk_hist *h, int i) {
	return h->len[i];
}

int sk_hist_get_nd(sk_hist *h) {
	return h->nd;
}

int sk_hist_get_pos(sk_hist *h, int i) {
	return h->pos[i];
}

int sk_hist_get_uvi(sk_hist *h, int i) {
	return h->uvi[i];
}

int sk_hist_get_vi(sk_hist *h, int i) {
	return h->vi[i];
}

double sk_hist_get_maxd(sk_hist *h, int i) {
	return h->maxd[i];
}

int sk_hist_buf_is_null(sk_hist *h) {
	return h->buf == NULL;
}

double sk_hist_get_vd(sk_hist *h, int i) {
	return h->del[i];
}
