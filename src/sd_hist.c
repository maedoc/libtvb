/* copyright 2016 Apache 2 sddekit authors */

#include "sddekit.h"

typedef struct hist_data
{
	/*               nu+1   nu    nu    nu   nd, maxvi */
	uint32_t nd, nu, *lim, *len, *pos, *uvi, *vi, *vi2i, maxvi;
	/*   sum(len)  nu     nd 		*/
	double *buf, *maxd, *del, dt, t;
} hist_data;

uint32_t get_maxvi(sd_hist *h) { return ((hist_data*) h->ptr)->maxvi; }
uint32_t get_vi2i(sd_hist *h, uint32_t vi) { return ((hist_data*) h->ptr)->vi2i[vi]; }

static void update_time(sd_hist *hist, double new_t)
{
	uint32_t i, n_steps;
	hist_data *h = hist->ptr;

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
}

static void hist_free(sd_hist *hist)
{
	hist_data *h = hist->ptr;
	sd_free(h->uvi);
	sd_free(h->del);
	sd_free(h->vi);
	sd_free(h->maxd);
	sd_free(h->lim);
	sd_free(h->len);
	sd_free(h->pos);
	sd_free(h->vi2i);
	sd_free(h->buf);
	sd_free(h);
	sd_free(hist);
}

static sd_stat fill(sd_hist *hist, sd_hfill *hf)
{
	uint32_t i, j, ui, o, n, *vi;
	double *t;
	char *errmsg;
	hist_data *h = hist->ptr;
	errmsg = NULL;
	t = NULL;
	vi = NULL;

	n = h->lim[h->nu];
	if ((t = sd_malloc (sizeof(double) * n))==NULL ||
		(vi = sd_malloc (sizeof(uint32_t) * n))==NULL) {
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

	if (hf->apply(hf, n, t, vi, h->buf) != SD_OK)
		errmsg = "history fill function failed.";

end:
	if (t!=NULL) sd_free(t);
	if (vi!=NULL) sd_free(vi);

	return errmsg == NULL ? SD_OK : SD_ERR;
}

static void get(sd_hist *hist, double t, double *aff)
{
	uint32_t i;
	hist_data *h = hist->ptr;

	if (h==NULL)
		return;

	for (i = 0; i < h->nd; i++)
	{
		uint32_t ui = h->vi2i[h->vi[i]] /* unique variable index */
		       ,  p = h->pos[ui]        /* rel pos in ui's var buf */
		       ,  l = h->len[ui]        /* len of ui's var buf */
		       ,  o = h->lim[ui];       /* offset of ui's buf in h->buf */

		/* TODO the following dt is not sol dt or hist dt, find better name */
		double dt = (t - h->del[i]) - (h->t - (l - 2)*h->dt);

		/* relative buffer indices */
		int64_t i0 = (int64_t) ceil((l - 2) - dt / h->dt);
		if (i0 < 0)
			i0 += l;
		int64_t i1 = i0 > 0 ? ((uint32_t) i0) - 1 : l - 1;

		/* absolute buffer indices */
		uint32_t i0_ = (p + i0) % l + o
		       , i1_ = (p + i1) % l + o;

#ifdef SDDEBUG
		if ((i0_ < h->lim[ui]) || (i0_ >= h->lim[ui+1]))
			sd_log_debug("[sd_hist_get] oob: i0_=%d not in [%d, %d) at %s:%d\n",
                                     i0_, h->lim[ui], h->lim[ui+1], __FILE__, __LINE__ );
		if ((i1_ < h->lim[ui]) || (i1_ >= h->lim[ui+1]))
			sd_log_debug("[sd_hist_get] oob: i0_=%d not in [%d, %d) at %s:%d\n",
                                     i1_, h->lim[ui], h->lim[ui+1], __FILE__, __LINE__ );
#endif

		double y0 = h->buf[i0_] /* consider sse read */
		     , y1 = h->buf[i1_]
		     ,  m = (y1 - y0) / h->dt
		     , dx = (t - h->del[i]) - (h->t - i0*h->dt);

		aff[i] = m * dx + y0;
	}
}

static void set(sd_hist *hist, double t, double *eff)
{
	uint32_t i, i0, i1;
	double x0, dx, dt;
	hist_data *h = hist->ptr;

	update_time(hist, t);

	for (i=0; i<h->nu; i++)
	{
		i0 = h->pos[i];
		i1 = i0 ? i0 - 1 : h->len[i] - 1;
		i0 += h->lim[i];
		i1 += h->lim[i];
#ifdef SDDEBUG
        if ((i0 < h->lim[i]) || (i0 > h->lim[i+1]))
            fprintf(stderr, "[sd_hist_set] t=%.3f ui=%d, i0=%d not in [%d,%d) %s:%d\n", 
		    t, i, i0, h->lim[i], h->lim[i+1], __FILE__, __LINE__);
        if ((i1 < h->lim[i]) || (i1 > h->lim[i+1]))
            fprintf(stderr, "[sd_hist_set] t=%.3f ui=%d, i1=%d not in [%d,%d) %s:%d\n", 
		    t, i, i1, h->lim[i], h->lim[i+1], __FILE__, __LINE__);
#endif
		x0 = h->buf[i0];
		dt = t - h->t;

#ifdef SDDEBUG
		if (dt < 0)
			sd_log_debug( "[sd_hist] unhandled dt<0 at %s:%d\n", __FILE__, __LINE__ );
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

static uint32_t nbytes(sd_hist *hist)
{
	uint32_t nb;
	hist_data *h = hist->ptr;
	nb = sizeof(sd_hist) + sizeof(hist_data);
	nb += sizeof(uint32_t) * ((h->nu+1) + 3*h->nu + h->nd + (h->maxvi + 1));
	nb += sizeof(double) * (h->lim[h->nu] + h->nu + h->nd);
	return nb;
}

static uint32_t get_nu(sd_hist *h) {
	return ((hist_data*) h->ptr)->nu;
}

static double get_buf_lin(sd_hist *hist, uint32_t index)
{
	hist_data *h = hist->ptr;
#ifdef SDDEBUG
	if (index >= h->lim[h->nu])
		sd_log_debug( "[hist->get_buf_lin] oob index=%d not in [0, %d)\n", index, h->lim[h->nu] );
#endif
	return h->buf[index];
}

static double get_t(sd_hist *h) {
	return ((hist_data*) h->ptr)->t;
}

static double get_dt(sd_hist *h) {
	return ((hist_data*) h->ptr)->dt;
}

static uint32_t get_lim(sd_hist *h, uint32_t i) {
	return ((hist_data*) h->ptr)->lim[i];
}

static uint32_t get_len(sd_hist *h, uint32_t i) {
	return ((hist_data*) h->ptr)->len[i];
}

static uint32_t get_nd(sd_hist *h) {
	return ((hist_data*) h->ptr)->nd;
}

static uint32_t get_pos(sd_hist *h, uint32_t i) {
	return ((hist_data*) h->ptr)->pos[i];
}

static uint32_t get_uvi(sd_hist *h, uint32_t i) {
	return ((hist_data*) h->ptr)->uvi[i];
}

static uint32_t get_vi(sd_hist *h, uint32_t i) {
	return ((hist_data*) h->ptr)->vi[i];
}

static double get_maxd(sd_hist *h, uint32_t i) {
	return ((hist_data*) h->ptr)->maxd[i];
}

static bool buf_is_null(sd_hist *h) {
	return ((hist_data*) h->ptr)->buf == NULL;
}

static double get_vd(sd_hist *h, uint32_t i) {
	return ((hist_data*) h->ptr)->del[i];
}

static sd_hist sd_hist_defaults = {
	.ptr = NULL,
	.get_maxvi = &get_maxvi,
	.get_vi2i = &get_vi2i,
	.get_nu = &get_nu,
	.free = &hist_free,
	.fill = &fill,
	.get = &get,
	.set = &set,
	.nbytes = &nbytes,
	.get_buf_lin = &get_buf_lin,
	.get_nd = &get_nd,
	.get_t = &get_t,
	.get_dt = &get_dt,
	.get_lim = &get_lim,
	.get_len = &get_len,
	.get_pos = &get_pos,
	.get_uvi = &get_uvi,
	.get_maxd = &get_maxd,
	.get_vi = &get_vi,
	.get_vd = &get_vd,
	.buf_is_null = &buf_is_null
};

static sd_stat setup_buffer_structure(hist_data *h, double dt)
{
	uint32_t i, j, ui;
	double maxd;
	char *errmsg;
	/* alloc */
	if (
		(h->maxd = sd_malloc (sizeof(double) * h->nu))==NULL ||
		(h->lim = sd_malloc (sizeof(uint32_t) * (h->nu + 1)))==NULL ||
		(h->len = sd_malloc (sizeof(uint32_t) * h->nu))==NULL ||
		(h->pos = sd_malloc (sizeof(uint32_t) * h->nu))==NULL
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
	if ((h->vi2i = sd_malloc (sizeof(uint32_t) * (h->maxvi + 1)))==NULL) {
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
	return SD_OK;
fail:
	if (h->maxd!=NULL) sd_free(h->maxd);
	if (h->lim!=NULL) sd_free(h->lim);
	if (h->len!=NULL) sd_free(h->len);
	if (h->pos!=NULL) sd_free(h->pos);
	if (h->vi2i!=NULL) sd_free(h->vi2i);
	sd_err(errmsg);
	return SD_ERR;
}

sd_hist *
sd_hist_new_default(uint32_t nd, uint32_t *vi, double *vd, double t0, double dt)
{
	sd_hist *hist;
	hist_data *h = NULL, zh = { 0 };
	if ((hist = sd_malloc(sizeof(sd_hist))) == NULL
		|| (h = hist->ptr = sd_malloc(sizeof(hist_data))) == NULL
		|| (*h = zh, (h->nd = nd) < 1)
		|| sd_util_uniqi(nd, vi, &(h->nu), &(h->uvi)) != SD_OK
		|| (h->del = sd_malloc(sizeof(double) * nd)) == NULL
		|| (h->vi = sd_malloc(sizeof(uint32_t) * nd)) == NULL
		|| (memcpy(h->del, vd, nd * sizeof(double)),
		    memcpy(h->vi, vi, nd * sizeof(uint32_t)),
			0)
		|| setup_buffer_structure(h, dt) != SD_OK
		|| (h->buf = sd_malloc(sizeof(double) * h->lim[h->nu])) == NULL
		)
	{
		if (hist != NULL) sd_free(hist);
		if (h != NULL)
		{
			if (h->buf!=NULL) sd_free(h->buf);
			if (h->uvi!=NULL) sd_free(h->uvi);
			if (h->del!=NULL) sd_free(h->del);
			if (h->vi!=NULL) sd_free(h->vi);
		}
		sd_err("number of delays < 1 or memory alloc failed.");
		return NULL;
	}
	h->dt = dt;
	h->t = t0;
	*hist = sd_hist_defaults;
	hist->ptr = h;
	return hist;
}

static sd_stat val_fill_apply(sd_hfill *hf, uint32_t n, double * restrict t,
							  uint32_t *indices, double * restrict buf)
{
	uint32_t i;
	double value = *((double*)hf->ptr);
	(void)t; (void)indices;
	for (i = 0; i < n; i++)
		buf[i] = value;
	return SD_OK;
}

static void val_fill_free(sd_hfill *hf)
{
	sd_free(hf->ptr);
	sd_free(hf);
}

sd_hfill *
sd_hfill_new_val(double val)
{
	sd_hfill *hf;
	if ((hf=sd_malloc(sizeof(sd_hfill))) == NULL
		|| (hf->ptr=sd_malloc(sizeof(double))) == NULL)
	{
		sd_err("alloc hfill failed.");
		return hf;
	}
	*((double*)hf->ptr) = val;
	hf->free = &val_fill_free;
	hf->apply = &val_fill_apply;
	return hf;
}
