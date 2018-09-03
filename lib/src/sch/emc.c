/* copyright 2016 Apache 2 libtvb authors */

#include "libtvb.h"
#include "sch/base.h"
#include <math.h>

struct data
{ 
	struct sch_base base;
	bool first_call;
	double *f, *g, *z, *eps, lam, E;
};

/* obj free n byte copy {{{ */

static void
emc_free(struct tvb_sch *sch)
{
	struct data *d = sch->data;
    sch_base_pointers_free(&d->base);
	tvb_free(d->f);
	tvb_free(d->g);
	tvb_free(d->z);
	tvb_free(d->eps);
	tvb_free(d);
}

static uint32_t
emc_n_byte(struct tvb_sch *tvb_sch)
{
	struct data *data = tvb_sch->data;
	uint32_t byte_count = sizeof(struct data);
	byte_count += sizeof(double ) * data->base.n_dim * 4;
	byte_count += sch_base_pointers_n_byte(&data->base);
	return byte_count;
}

static struct tvb_sch*
emc_copy(struct tvb_sch *tvb_sch)
{
	struct data *data = tvb_sch->data;
	struct sch_base *base = &data->base;
	struct tvb_sch *copy;
	copy = tvb_sch_new_emc(base->time, base->dt,
			data->lam, base->sys, base->hist, base->rng);
	if (copy == NULL)
		tvb_err("copy emc sch failed.");
	struct data *copy_data = copy->data;
	sch_base_pointers_copy(base, &copy_data->base);
	memcpy(copy_data->f, data->f, sizeof(double) * base->n_dim);
	memcpy(copy_data->g, data->g, sizeof(double) * base->n_dim);
	memcpy(copy_data->z, data->z, sizeof(double) * base->n_dim);
	memcpy(copy_data->eps, data->eps, sizeof(double) * base->n_dim);
	return copy;
}

static struct tvb_out_sample sample(struct tvb_sch *tvb_sch)
{
    struct data *data = tvb_sch->data;
    return sch_base_sample(&data->base);
}

/* apply {{{ */

static enum tvb_stat emc_apply(struct tvb_sch *sch)
{
	enum tvb_stat stat;
	struct data *d = sch->data;
	struct sch_base *b = &(d->base);
	struct tvb_sys_in in = sch_base_sys_in(b, b->time);
	struct tvb_sys_out out = sch_base_sys_out(b, d->f, d->g);
	if (d->first_call) {
		b->rng->fill_norm(b->rng, b->n_dim, d->z);
		if ((stat = b->sys->apply(b->sys, &in, &out)) != TVB_OK)
			return stat;
		for (uint32_t i=0; i<b->n_dim; i++)
			d->eps[i] = sqrt(d->g[i] * d->lam) * d->z[i];
		d->E = exp(-d->lam * b->dt);
		d->first_call = false;
	}
	b->rng->fill_norm(b->rng, b->n_dim, d->z);
	b->hist->query(b->hist, b->time, b->input);
	if ((stat = b->sys->apply(b->sys, &in, &out)) != TVB_OK)
		return stat;
	for (uint32_t i=0; i<b->n_dim; i++) {
		b->state[i] += b->dt * (d->f[i] + d->eps[i]);
		d->eps[i] *= d->E;
		d->eps[i] += sqrt(d->g[i] * d->lam * (1 - d->E*d->E)) * d->z[i];
	}
	b->time += b->dt;
	b->hist->update(b->hist, b->time, b->output);
	return TVB_OK;
}

/* }}} */

struct tvb_sch *
tvb_sch_new_emc(double time, double dt, double lam,
	       struct tvb_sys *sys, struct tvb_hist *hist, struct tvb_rng *rng)
{
	struct data *d, z={0};
	uint32_t n_dim = sys->get_n_dim(sys)
	       , n_in  = sys->get_n_in(sys)
	       , n_out = sys->get_n_out(sys)
	       ;
	if ((d = tvb_malloc(sizeof(struct data))) == NULL
	 || (*d=z, 0)
	 || (d->f=tvb_malloc(sizeof(double)*n_dim))==NULL
	 || (d->g=tvb_malloc(sizeof(double)*n_dim))==NULL
	 || (d->z=tvb_malloc(sizeof(double)*n_dim))==NULL
	 || (d->eps=tvb_malloc(sizeof(double)*n_dim))==NULL
     || sch_base_init(&d->base,
            time, dt,
            n_dim, n_in, n_out,
            sys, hist, rng, 
            emc_n_byte, emc_free, emc_copy, emc_apply, &sample) != TVB_OK
	)
	{
		if (d->f!=NULL) tvb_free(d->f);
		if (d->g!=NULL) tvb_free(d->g);
		if (d->z!=NULL) tvb_free(d->z);
		if (d->eps!=NULL) tvb_free(d->eps);
		if (d != NULL) tvb_free(d);
		tvb_err("alloc for emc scheme failed.");
		return NULL;
	}
	d->first_call = true;
	d->lam = lam;
	d->base.sch.data = d;
	return &(d->base.sch);
}

/* vim: foldmethod=marker
 */
