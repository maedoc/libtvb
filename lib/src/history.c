/* copyright 2016 Apache 2 libtvb authors */

#include "libtvb.h"
#include <math.h>

struct hist_data
{
	/*               nu+1   nu    nu    nu   nd, maxvi+1 */
	uint32_t nd, nu, *lim, *len, *pos, *uvi, *vi, *vi2i, maxvi;
	/*   sum(len)  nu     nd 		*/
	double *buf, *maxd, *del, dt, t;
};

/* single delay buffer {{{ */

/* 24-byte overhead, but only 16 for single query. Current CPUs often have
 * 64-byte cache lines, so this is 25% overhead.
 */
struct delay_buffer 
{
	/*! Time step between buffer sample points. */
	float time_step;
	/*! Time of most recent update to data. */
	float current_time;
	/*! Index of output vector which is source of data. */
	uint32_t source_index;
	/*! Length of data. */
       	uint32_t length;
	/*! Position of most recent update to data. */
        uint32_t position;
	/*! Maximum delay for all terms referencing source_index. */
	float max_delay;
	/*! Array of delayed data values. */
	float *data;
};

/* delay buffer new free copy nbyte {{{ */

static uint32_t
delay_buffer_n_byte(struct delay_buffer *buf)
{
	uint32_t byte_count = sizeof(struct delay_buffer);
	byte_count += buf->length * sizeof(double);
	return byte_count;
}

static struct delay_buffer*
delay_buffer_new(double time_step, uint32_t source_index, double max_delay)
{
	struct delay_buffer *buf, zero = {0};
	if ((buf = tvb_malloc(sizeof(struct delay_buffer))) == NULL
	 || (*buf = zero, 0)
	 || (buf->data = tvb_malloc(sizeof(double)*
		(buf->length = (uint32_t) (ceil(max_delay) + 2)))) == NULL
	 )
	{
		if (buf != NULL)
			tvb_free(buf);
		tvb_err("alloc delay buffer failed.");
		return NULL;
	}
	buf->time_step = time_step;
	buf->source_index = source_index;
	buf->max_delay = max_delay;
	buf->current_time = 0.0;
	buf->position = 0;
	return buf;
}

static struct delay_buffer *
delay_buffer_copy(struct delay_buffer *buf)
{
	struct delay_buffer *copy = delay_buffer_new(
		buf->time_step, buf->source_index, buf->max_delay);
	if (copy == NULL)
		{tvb_err("alloc delay buffer copy failed.");}
	else
		memcpy(copy->data, buf->data, sizeof(double) * buf->length);
	return copy;
}

static void
delay_buffer_free(struct delay_buffer *buffer)
{
	tvb_free(buffer->data);
	tvb_free(buffer);
}

/* }}} */

static inline enum tvb_stat
update_delay_buffer(struct delay_buffer *buffer, double time, double *value);

static inline enum tvb_stat
query_delay_buffer(struct delay_buffer *buffer, double time, double *value);

/* }}} */

/* sparse delay set {{{ */

/* Handles a set of delays, non-contiguous source indices 
 * into system output. 
 *
 * Decomposing hist into delay buffer & set provides more refined granularity
 * and thus better memory use. Short-range delays can be separated from
 * long-range (even given different time steps), allowing for a sparser
 * overall structure in both.
 */
struct sparse_delay_set
{
	/*! Number of delay terms. */
	uint32_t n_delay;
	/*! Number of unique sources. */
	uint32_t n_unique;
	/*! Maximum source index. */
	uint32_t max_index;
	/*! Array of buffers, one per unique source index. */
	struct delay_buffer *buffers;
	/*! Delay value per delay term. */
	double *delays;
	/*! Index of buffers per delay term. */
	uint32_t *buf_term_map;
	/* TODO invert this index so that on a query operation, we can load
	 * the buffer for a single source once, and fill out all the targets
	 * per source. Writes are no longer sequential (but weren't a
	 * bottleneck), but reads are more confined perhaps even to a
	 * cache line? Parallelize over sources, perhaps better memory use.
	 * We could furthermore order targets by delay so that reading from
	 * delay buffer is sequential. Again, this perhaps moves the random
	 * access from reads to writes.
	 */
	uint32_t *inv_buf_term_map;
};

/* }}} */

static void update_time(struct tvb_hist *hist, double new_t)/*{{{*/
{
	uint32_t i, n_steps;
	struct hist_data *h = hist->data;

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
		if (h->pos[i] < n_steps)
			h->pos[i] = h->len[i] - n_steps;
		else
			h->pos[i] -= n_steps;
	}
}/*}}}*/

static void hist_free(struct tvb_hist *hist)/*{{{*/
{
	struct hist_data *h = hist->data;
	tvb_free(h->uvi);
	tvb_free(h->del);
	tvb_free(h->vi);
	tvb_free(h->maxd);
	tvb_free(h->lim);
	tvb_free(h->len);
	tvb_free(h->pos);
	tvb_free(h->vi2i);
	tvb_free(h->buf);
	tvb_free(h);
	tvb_free(hist);
}/*}}}*/

static enum tvb_stat fill(struct tvb_hist *hist, struct tvb_hfill *hf)/*{{{*/
{
	uint32_t i, j, ui, o, n, *vi;
	double *t;
	char *errmsg;
	struct hist_data *h = hist->data;
	errmsg = NULL;
	t = NULL;
	vi = NULL;

	n = h->lim[h->nu];
	if ((t = tvb_malloc (sizeof(double) * n))==NULL ||
		(vi = tvb_malloc (sizeof(uint32_t) * n))==NULL) {
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

	if (hf->apply(hf, n, t, vi, h->buf) != TVB_OK)
		errmsg = "history fill function failed.";

end:
	if (t!=NULL) tvb_free(t);
	if (vi!=NULL) tvb_free(vi);

	return errmsg == NULL ? TVB_OK : TVB_ERR;
}/*}}}*/

static void get(struct tvb_hist *hist, double t, double *aff) /* {{{ */
{
	uint32_t i;
	struct hist_data *h = hist->data;
	uint32_t *vi2i = h->vi2i;
	uint32_t *pos = h->pos;
	uint32_t *len = h->len;
	uint32_t *lim = h->lim;
	double *buf = h->buf;
	double *del = h->del;
	double h_t = h->t, h_dt = h->dt;

	if (h==NULL)
		return;

	double inv_dt = 1.0 / h_dt;

	/* TODO iterate over sources, then targets */
	for (i = 0; i < h->nd; i++)
	{
		uint32_t ui = vi2i[h->vi[i]] /* unique variable index */
		       ,  p = pos[ui]        /* rel pos in ui's var buf */
		       ,  l = len[ui]        /* len of ui's var buf */
		       ,  o = lim[ui];       /* offset of ui's buf in h->buf */

		/* TODO the following dt is not sol dt or hist dt, find better name */
		double dt = (t - del[i]) - (h_t - (l - 2)*h_dt);

		/* relative buffer indices */
		int64_t i0 = (int64_t) ceil((l - 2) - dt * inv_dt);
		if (i0 < 0)
			i0 += l;
		int64_t i1 = i0 > 0 ? ((uint32_t) i0) - 1 : l - 1;

		/* absolute buffer indices */
		uint32_t i0_ = (p + i0) % l + o
		       , i1_ = (p + i1) % l + o;

#ifdef SDDEBUG
		if ((i0_ < h->lim[ui]) || (i0_ >= h->lim[ui+1]))
			tvb_log_debug("oob: i0_=%d not in [%d, %d) at %s:%d\n",
                                     i0_, h->lim[ui], h->lim[ui+1], __FILE__, __LINE__ );
		if ((i1_ < h->lim[ui]) || (i1_ >= h->lim[ui+1]))
			tvb_log_debug("oob: i0_=%d not in [%d, %d) at %s:%d\n",
                                     i1_, h->lim[ui], h->lim[ui+1], __FILE__, __LINE__ );
#endif

		double y0 = buf[i0_] /* bottleneck is L1 cache miss */
		     , y1 = buf[i1_] /* further reads from cache line free */
		     ,  m = (y1 - y0) * inv_dt
		     , dx = (t - del[i]) - (h_t - i0*h_dt);

		aff[i] = m * dx + y0;
	}
} /* }}} */

static void set(struct tvb_hist *hist, double t, double *eff)/*{{{*/
{
	uint32_t i, i0, i1;
	double x0, dx, dt;
	struct hist_data *h = hist->data;

	update_time(hist, t);

	for (i=0; i<h->nu; i++)
	{
		i0 = h->pos[i];
		i1 = i0 ? i0 - 1 : h->len[i] - 1;
		i0 += h->lim[i];
		i1 += h->lim[i];
#ifdef SDDEBUG
        if ((i0 < h->lim[i]) || (i0 > h->lim[i+1]))
            fprintf(stderr, "[tvb_hist_set] t=%.3f ui=%d, i0=%d not in [%d,%d) %s:%d\n", 
		    t, i, i0, h->lim[i], h->lim[i+1], __FILE__, __LINE__);
        if ((i1 < h->lim[i]) || (i1 > h->lim[i+1]))
            fprintf(stderr, "[tvb_hist_set] t=%.3f ui=%d, i1=%d not in [%d,%d) %s:%d\n", 
		    t, i, i1, h->lim[i], h->lim[i+1], __FILE__, __LINE__);
#endif
		x0 = h->buf[i0];
		dt = t - h->t;

#ifdef SDDEBUG
		if (dt < 0)
			tvb_log_debug("unhandled dt<0 at %s:%d\n", __FILE__, __LINE__ );
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
}/*}}}*/

static uint32_t nbytes(struct tvb_hist *hist)/*{{{*/
{
	uint32_t nb;
	struct hist_data *h = hist->data;
	nb = sizeof(struct tvb_hist) + sizeof(struct hist_data);
	nb += sizeof(uint32_t) * ((h->nu+1) + 3*h->nu + h->nd + h->maxvi + 1);
	nb += sizeof(double) * (h->lim[h->nu] + h->nu + h->nd);
	return nb;
}/*}}}*/

/* accessors {{{ */

static double get_t(struct tvb_hist *h) {
	return ((struct hist_data*) h->data)->t;
}

static double get_dt(struct tvb_hist *h) {
	return ((struct hist_data*) h->data)->dt;
}

static uint32_t get_nd(struct tvb_hist *h) {
	return ((struct hist_data*) h->data)->nd;
}

static double get_vi(struct tvb_hist *h, uint32_t i) {
	return ((struct hist_data*) h->data)->vi[i];
}

static double get_vd(struct tvb_hist *h, uint32_t i) {
	return ((struct hist_data*) h->data)->del[i];
}
/* }}} */

static struct tvb_hist *
hist_copy(struct tvb_hist *hist)
{
	(void) hist;
	/* need a way to distinguish between interp types, etc. */
	tvb_err("Not (yet) implemented.");
	return NULL;
}

static struct tvb_hist tvb_hist_defaults = {/*{{{*/
	.free = &hist_free,
	.n_byte = &nbytes,
	.copy = &hist_copy,
	.get_n_delay = &get_nd,
	.get_time = &get_t,
	.get_time_step = &get_dt,
	.get_var_idx = &get_vi,
	.get_var_del = &get_vd,
	.fill = &fill,
	.query = &get,
	.update = &set
};/*}}}*/

static enum tvb_stat setup_buffer_structure(struct hist_data *h, double dt)/*{{{*/
{
	uint32_t i, j, ui;
	double maxd;
	char *errmsg;
	/* alloc */
	if (
		(h->maxd = tvb_malloc (sizeof(double) * h->nu))==NULL ||
		(h->lim = tvb_malloc (sizeof(uint32_t) * (h->nu + 1)))==NULL ||
		(h->len = tvb_malloc (sizeof(uint32_t) * h->nu))==NULL ||
		(h->pos = tvb_malloc (sizeof(uint32_t) * h->nu))==NULL
	   ) {
		errmsg = "failed to alloc internal storage.";
		goto fail;
	}
	/* vi2i requires max(uvi) then filling in vi2i[ui]=i */
	h->maxvi = 0;
	for (i=0; i<h->nu; i++)
		if (h->uvi[i] > h->maxvi)
			h->maxvi = h->uvi[i];
	/* alloc */
	if ((h->vi2i = tvb_malloc (sizeof(uint32_t) * (h->maxvi + 1)))==NULL) {
		errmsg = "failed to alloc internal storage.";
		goto fail;
	}
	/* set up vi2i, maxd len pos lim */
	for (i=0; i<h->nu; i++)
	{
		ui = h->uvi[i];
		h->vi2i[ui] = i;
		maxd = 0.0;
		for (j=0; j<h->nd; j++)
			if (h->vi[j]==ui && h->del[j]>maxd)
				maxd = h->del[j];
		h->maxd[i] = maxd;
		h->len[i] = (uint32_t) ceil(maxd / dt) + 2;
		h->pos[i] = 0;
		if (i==0)
			h->lim[i] = 0;
		else
			h->lim[i] = h->lim[i-1] + h->len[i-1];
	}
	h->lim[h->nu] = h->lim[h->nu-1] + h->len[h->nu-1];
	return TVB_OK;
fail:
	if (h->maxd!=NULL) tvb_free(h->maxd);
	if (h->lim!=NULL) tvb_free(h->lim);
	if (h->len!=NULL) tvb_free(h->len);
	if (h->pos!=NULL) tvb_free(h->pos);
	if (h->vi2i!=NULL) tvb_free(h->vi2i);
	tvb_err("%s", errmsg);
	return TVB_ERR;
}/*}}}*/

struct tvb_hist *
tvb_hist_new_linterp(uint32_t nd, uint32_t *vi, double *vd, double t0, double dt)/*{{{*/
{
	struct tvb_hist *hist;
	struct hist_data *h = NULL, zero = { 0 };
	if ((hist = tvb_malloc(sizeof(struct tvb_hist))) == NULL
		|| (h = hist->data = tvb_malloc(sizeof(struct hist_data))) == NULL
		|| (*h = zero, (h->nd = nd) < 1)
		|| tvb_util_uniqi(nd, vi, &(h->nu), &(h->uvi)) != TVB_OK
		|| (h->del = tvb_malloc(sizeof(double) * nd)) == NULL
		|| (h->vi = tvb_malloc(sizeof(uint32_t) * nd)) == NULL
		|| (memcpy(h->del, vd, nd * sizeof(double)),
		    memcpy(h->vi, vi, nd * sizeof(uint32_t)),
			0)
		|| setup_buffer_structure(h, dt) != TVB_OK
		|| (h->buf = tvb_malloc(sizeof(double) * h->lim[h->nu])) == NULL
		)
	{
		if (hist != NULL) tvb_free(hist);
		if (h != NULL)
		{
			if (h->buf!=NULL) tvb_free(h->buf);
			if (h->uvi!=NULL) tvb_free(h->uvi);
			if (h->del!=NULL) tvb_free(h->del);
			if (h->vi!=NULL) tvb_free(h->vi);
		}
		tvb_err("number of delays < 1 or memory alloc failed.");
		return NULL;
	}
	h->dt = dt;
	h->t = t0;
	*hist = tvb_hist_defaults;
	hist->data = h;
	return hist;
}/*}}}*/

/* no delay variant {{{ */

static void get_no_delay(struct tvb_hist *hist, double t, double *aff)
{
	(void) t;
	struct hist_data *hd = hist->data;
	for (uint32_t i=0; i<hd->nd; i++)
		aff[i] = hd->buf[hd->vi2i[hd->vi[i]]];
}

static void set_no_delay(struct tvb_hist *hist, double t, double *eff)
{
	(void) t;
	struct hist_data *hd = hist->data;
	memcpy(hd->buf, eff, sizeof(double) * hd->maxvi);
}

struct tvb_hist *
tvb_hist_new_no_delays(uint32_t nd, uint32_t *vi, double *vd, double t0, double dt)
{
	struct tvb_hist *hist = tvb_hist_new_linterp(nd, vi, vd, t0, dt);
	if (hist == NULL)
	{
		tvb_err("hist no delay init failed.");
		return NULL;
	}
	hist->update = &get_no_delay;
	hist->query = &set_no_delay;
	return hist;
}

/* }}} */

/* nearest interp variant {{{ */

static void convert_delays_to_nearest(struct tvb_hist *hist)
{
	struct hist_data *data = hist->data;
	double *rd = data->del;
	for (uint32_t i=0; i<data->nd; i++, rd++)
		*rd = round(*rd/data->dt)*data->dt;
}

struct tvb_hist * tvb_hist_new_nearest(
	uint32_t nd, uint32_t *vi, double *vd, double t0, double dt)
{
	/* TODO consider split off file, use shared private struct */
	struct tvb_hist *hist = tvb_hist_new_linterp(nd, vi, vd, t0, dt);
	convert_delays_to_nearest(hist);
	tvb_log_debug("nearest hist for compat only, not yet optimized");
	return hist;
}

/* }}} */

/* fill {{{ */
static enum tvb_stat
val_fill_apply(struct tvb_hfill *hf, 
	       uint32_t n, double *t,
	       uint32_t *indices, double *buf)
{
	uint32_t i;
	double value = *((double*)hf->data);
	(void) t; (void) indices;
	for (i = 0; i < n; i++)
		buf[i] = value;
	return TVB_OK;
}

static struct tvb_hfill *
val_fill_copy(struct tvb_hfill *hf)
{
	struct tvb_hfill *copy;
	copy = tvb_hfill_new_val(*((double*) hf->data));
	if (copy == NULL)
		tvb_err("copy val hfill failed.");
	return copy;
}

static uint32_t
val_fill_n_byte(struct tvb_hfill *hf)
{
	(void) hf;
	uint32_t byte_count = sizeof(struct tvb_hfill);
	byte_count += sizeof(double);
	return byte_count;
}

static void val_fill_free(struct tvb_hfill *hf)
{
	tvb_free(hf->data);
	tvb_free(hf);
}

static struct tvb_hfill hfill_val_defaults = {
	.free = &val_fill_free,
	.copy = &val_fill_copy,
	.n_byte = &val_fill_n_byte,
	.apply = &val_fill_apply
};

struct tvb_hfill *
tvb_hfill_new_val(double val)
{
	struct tvb_hfill *hf;
	if ((hf = tvb_malloc(sizeof(struct tvb_hfill))) == NULL
     || (*hf = hfill_val_defaults, 0)
	 || (hf->data = tvb_malloc(sizeof(double))) == NULL)
	{
		if (hf != NULL)
			tvb_free(hf);
		tvb_err("alloc hfill failed.");
		return NULL;
	}
	*((double*) hf->data) = val;
	return hf;
}
/* }}} */

/* vim: foldmethod=marker
 */
