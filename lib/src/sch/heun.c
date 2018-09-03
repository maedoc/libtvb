/* copyright 2016 Apache 2 libtvb authors */

#include "libtvb.h"
#include "sch/base.h"

struct data
{
	struct sch_base base;
	double *fl, *fr, *gl, *gr, *z, *xr, sqrt_dt;
};

/* obj free nbyte copy {{{ */

static void heun_free(struct tvb_sch *sch)
{
	struct data *d = sch->data;
    sch_base_pointers_free(&d->base);
	tvb_free(d->fl);;
	tvb_free(d->fr);;
	tvb_free(d->gl);;
	tvb_free(d->gr);;
	tvb_free(d->z);;
	tvb_free(d->xr);;
	tvb_free(d);
}

static uint32_t
n_byte(struct tvb_sch *tvb_sch)
{
	struct data *data = tvb_sch->data;
	uint32_t byte_count = sizeof(struct data);
	byte_count += sizeof(double ) * data->base.n_dim * 6;
	byte_count += sch_base_pointers_n_byte(&data->base);
	return byte_count;
}

static struct tvb_sch*
copy(struct tvb_sch *tvb_sch)
{
	struct data *data = tvb_sch->data;
	struct sch_base *base = &data->base;
	struct tvb_sch *copy;
	copy = tvb_sch_new_heun(base->time, base->dt,
			base->sys, base->hist, base->rng);
	if (copy == NULL)
		tvb_err("copy heun sch failed.");
	struct data *copy_data = copy->data;
	sch_base_pointers_copy(base, &copy_data->base);
	memcpy(copy_data->fl, data->fl, sizeof(double) * base->n_dim);
	memcpy(copy_data->fr, data->fr, sizeof(double) * base->n_dim);
	memcpy(copy_data->gl, data->gl, sizeof(double) * base->n_dim);
	memcpy(copy_data->gr, data->gr, sizeof(double) * base->n_dim);
	memcpy(copy_data->z, data->z, sizeof(double) * base->n_dim);
	memcpy(copy_data->xr, data->xr, sizeof(double) * base->n_dim);
	return copy;
}

/* }}} */

static enum tvb_stat heun_apply(struct tvb_sch *sch)
{
	enum tvb_stat stat;
	struct data *d = sch->data;
	struct sch_base *b = &(d->base);
	struct tvb_sys_in in = sch_base_sys_in(b, b->time);
	struct tvb_sys_out out = sch_base_sys_out(b, d->fl, d->gl);

	/* predictor */
	b->hist->query(b->hist, b->time, b->input);
	if ((stat = b->sys->apply(b->sys, &in, &out)) != TVB_OK)
		return stat;
	for (uint32_t i=0; i<b->n_dim; i++)
		d->xr[i] = b->state[i] + b->dt * d->fl[i];
	b->hist->update(b->hist, b->time, b->output);

	/* corrector */
	b->hist->query(b->hist, b->time + b->dt, b->output);
	in.time += b->dt;
	in.state = d->xr;
	out.drift = d->fr;
	out.diffusion = d->gr;
	if ((stat = b->sys->apply(b->sys, &in, &out)) != TVB_OK)
		return stat;
	b->rng->fill_norm(b->rng, b->n_dim, d->z);
	for (uint32_t i=0; i<b->n_dim; i++)
		b->state[i] += 0.5 * (b->dt*(d->fl[i] + d->fr[i]) 
				+ d->sqrt_dt*(d->gl[i] + d->gr[i])*d->z[i]);
	b->hist->update(b->hist, in.time, b->output);
    
    /* update time */
    b->time += b->dt;
	return TVB_OK;
}

static struct tvb_out_sample sample(struct tvb_sch *tvb_sch)
{
    struct data *data = tvb_sch->data;
    return sch_base_sample(&data->base);
}

struct tvb_sch *
tvb_sch_new_heun(double time, double dt,
		struct tvb_sys *sys, struct tvb_hist *hist, struct tvb_rng *rng)
{
	struct data *d, z = {0};
	uint32_t n_dim = sys->get_n_dim(sys)
	       , n_in  = sys->get_n_in(sys)
	       , n_out = sys->get_n_out(sys)
	       ;
	if ((d = tvb_malloc(sizeof(struct data))) == NULL
	 || (*d=z, 0)
	 || (d->fl=tvb_malloc(sizeof(double)*n_dim))==NULL
	 || (d->fr=tvb_malloc(sizeof(double)*n_dim))==NULL
	 || (d->gl=tvb_malloc(sizeof(double)*n_dim))==NULL
	 || (d->gr=tvb_malloc(sizeof(double)*n_dim))==NULL
	 || (d->z=tvb_malloc(sizeof(double)*n_dim))==NULL
	 || (d->xr=tvb_malloc(sizeof(double)*n_dim))==NULL
     || sch_base_init(&d->base,
            time, dt,
            n_dim, n_in, n_out,
            sys, hist, rng, 
            n_byte, heun_free, copy, heun_apply, &sample) != TVB_OK
	)
	{
		if (d->fl!=NULL) tvb_free(d->fl);
		if (d->fr!=NULL) tvb_free(d->fr);
		if (d->gl!=NULL) tvb_free(d->gl);
		if (d->gr!=NULL) tvb_free(d->gr);
		if (d->z!=NULL) tvb_free(d->z);
		if (d->xr!=NULL) tvb_free(d->xr);
		if (d != NULL) tvb_free(d);
		tvb_err("alloc for heun scheme failed.");
		return NULL;
	}
	d->base.sch.data = d;
	return &(d->base.sch);
}

/* vim: foldmethod=marker
 */
