/* copyright 2016 Apache 2 sddekit authors */

#include "sddekit.h"
#include "sch/base.h"

struct data
{
	struct sch_base base;
	double *fl, *fr, *gl, *gr, *z, *xr, sqrt_dt;
};

/* obj free nbyte copy {{{ */

static void heun_free(struct sd_sch *sch)
{
	struct data *d = sch->data;
    sch_base_pointers_free(&d->base);
	sd_free(d->fl);;
	sd_free(d->fr);;
	sd_free(d->gl);;
	sd_free(d->gr);;
	sd_free(d->z);;
	sd_free(d->xr);;
	sd_free(d);
}

static uint32_t
n_byte(struct sd_sch *sd_sch)
{
	struct data *data = sd_sch->data;
	uint32_t byte_count = sizeof(struct data);
	byte_count += sizeof(double ) * data->base.n_dim * 6;
	byte_count += sch_base_pointers_n_byte(&data->base);
	return byte_count;
}

static struct sd_sch*
copy(struct sd_sch *sd_sch)
{
	struct data *data = sd_sch->data;
	struct sch_base *base = &data->base;
	struct sd_sch *copy;
	copy = sd_sch_new_heun(base->time, base->dt,
			base->sys, base->hist, base->rng);
	if (copy == NULL)
		sd_err("copy heun sch failed.");
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

static enum sd_stat heun_apply(struct sd_sch *sch)
{
	enum sd_stat stat;
	struct data *d = sch->data;
	struct sch_base *b = &(d->base);
	struct sd_sys_in in = sch_base_sys_in(b, b->time);
	struct sd_sys_out out = sch_base_sys_out(b, d->fl, d->gl);

	/* predictor */
	b->hist->query(b->hist, b->time, b->input);
	if ((stat = b->sys->apply(b->sys, &in, &out)) != SD_OK)
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
	if ((stat = b->sys->apply(b->sys, &in, &out)) != SD_OK)
		return stat;
	b->rng->fill_norm(b->rng, b->n_dim, d->z);
	for (uint32_t i=0; i<b->n_dim; i++)
		b->state[i] += 0.5 * (b->dt*(d->fl[i] + d->fr[i]) 
				+ d->sqrt_dt*(d->gl[i] + d->gr[i])*d->z[i]);
	b->hist->update(b->hist, in.time, b->output);
    
    /* update time */
    b->time += b->dt;
	return SD_OK;
}

static struct sd_out_sample sample(struct sd_sch *sd_sch)
{
    struct data *data = sd_sch->data;
    return sch_base_sample(&data->base);
}

struct sd_sch *
sd_sch_new_heun(double time, double dt,
		struct sd_sys *sys, struct sd_hist *hist, struct sd_rng *rng)
{
	struct data *d, z = {0};
	uint32_t n_dim = sys->get_n_dim(sys)
	       , n_in  = sys->get_n_in(sys)
	       , n_out = sys->get_n_out(sys)
	       ;
	if ((d = sd_malloc(sizeof(struct data))) == NULL
	 || (*d=z, 0)
	 || (d->fl=sd_malloc(sizeof(double)*n_dim))==NULL
	 || (d->fr=sd_malloc(sizeof(double)*n_dim))==NULL
	 || (d->gl=sd_malloc(sizeof(double)*n_dim))==NULL
	 || (d->gr=sd_malloc(sizeof(double)*n_dim))==NULL
	 || (d->z=sd_malloc(sizeof(double)*n_dim))==NULL
	 || (d->xr=sd_malloc(sizeof(double)*n_dim))==NULL
     || sch_base_init(&d->base,
            time, dt,
            n_dim, n_in, n_out,
            sys, hist, rng, 
            n_byte, heun_free, copy, heun_apply, &sample) != SD_OK
	)
	{
		if (d->fl!=NULL) sd_free(d->fl);
		if (d->fr!=NULL) sd_free(d->fr);
		if (d->gl!=NULL) sd_free(d->gl);
		if (d->gr!=NULL) sd_free(d->gr);
		if (d->z!=NULL) sd_free(d->z);
		if (d->xr!=NULL) sd_free(d->xr);
		if (d != NULL) sd_free(d);
		sd_err("alloc for heun scheme failed.");
		return NULL;
	}
	d->base.sch.data = d;
	return &(d->base.sch);
}

/* vim: foldmethod=marker
 */
