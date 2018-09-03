/* copyright 2016 Apache 2 libtvb authors */

#include "libtvb.h"
#include "sch/base.h"
#include <math.h>

struct data
{
	struct sch_base base;
	double *f, *g, *z, sqrt_dt;
};

/* free & n_byte {{{ */

void one_step_free(struct tvb_sch *sch)
{
	struct data *d = sch->data;
    sch_base_pointers_free(&d->base);
	tvb_free(d->f);
	tvb_free(d->g);
	tvb_free(d->z);
	tvb_free(d);
}

static uint32_t
n_byte(struct tvb_sch *tvb_sch)
{
	struct data *data = tvb_sch->data;
	uint32_t byte_count = sizeof(struct data);
	byte_count += sizeof(double) * data->base.n_dim * 3;
	byte_count += sch_base_pointers_n_byte(&data->base);
	return byte_count;
}

/* }}} */

/* apply {{{ */

static enum tvb_stat
one_step_apply(struct tvb_sch *sch)
{
	enum tvb_stat stat;
	struct data *d = sch->data;
	struct sch_base *b = &d->base;
	struct tvb_sys_in in = sch_base_sys_in(b, b->time);
	struct tvb_sys_out out = sch_base_sys_out(b, d->f, d->g);

	/* query hist, compute drift & diffusion, rng */
	b->hist->query(b->hist, b->time, b->input);
	if ((stat=b->sys->apply(b->sys, &in, &out))!=TVB_OK)
		return stat;
	b->rng->fill_norm(b->rng, b->n_dim, d->z);

	/* compute step & set history */
	return TVB_OK;
}

static enum tvb_stat
id_apply(struct tvb_sch *sch)
{
	enum tvb_stat stat;
	struct data *d = sch->data;
	struct sch_base *b = &d->base;
	if ((stat = one_step_apply(sch))!=TVB_OK)
		return stat;
	for (uint32_t i=0; i<b->n_dim; i++)
		b->state[i] = d->f[i] + d->g[i] * d->z[i];
	b->time += 1;
	b->hist->update(b->hist, b->time, b->output);
	return TVB_OK;
}

static enum tvb_stat
em_apply(struct tvb_sch *sch)
{
	enum tvb_stat stat;
	struct data *d = sch->data;
	struct sch_base *b = &d->base;
	if ((stat = one_step_apply(sch)) != TVB_OK)
		return stat;
	for (uint32_t i=0; i<b->n_dim; i++)
		b->state[i] += d->base.dt * d->f[i] \
			       + d->sqrt_dt * d->g[i] * d->z[i];
	b->time += b->dt;
	b->hist->update(b->hist, b->time, b->output);
	return TVB_OK;
}

static struct tvb_sch*
copy(struct tvb_sch *tvb_sch)
{
	struct data *data = tvb_sch->data;
	struct sch_base *base = &data->base;
	struct tvb_sch *copy;
	if (tvb_sch->apply == &id_apply)
		copy = tvb_sch_new_id(base->time,
				base->sys, base->hist, base->rng);
	else
		copy = tvb_sch_new_em(base->time, base->dt,
				base->sys, base->hist, base->rng);
	if (copy == NULL)
		tvb_err("copy one step sch failed.");
	struct data *copy_data = copy->data;
	sch_base_pointers_copy(base, &copy_data->base);
	memcpy(copy_data->f, data->f, sizeof(double) * base->n_dim);
	memcpy(copy_data->g, data->g, sizeof(double) * base->n_dim);
	memcpy(copy_data->z, data->z, sizeof(double) * base->n_dim);
	return copy;
}

static struct tvb_out_sample sample(struct tvb_sch *tvb_sch)
{
    struct data *data = tvb_sch->data;
    return sch_base_sample(&data->base);
}

/* constructors {{{ */

static struct tvb_sch *
new_one_step(double time, double dt,
    struct tvb_sys *sys, struct tvb_hist *hist, struct tvb_rng *rng)
{
	struct data *d, z = {0};;
	/* n_dim, n_in, n_out allocations here, scheme owns it all */
	uint32_t n_dim = sys->get_n_dim(sys)
           , n_in = sys->get_n_in(sys)
           , n_out = sys->get_n_out(sys);
	if ((d = tvb_malloc(sizeof(struct data))) == NULL
	 || (*d=z, 0)
	 || (d->f = tvb_malloc(sizeof(double)*n_dim)) == NULL
	 || (d->g = tvb_malloc(sizeof(double)*n_dim)) == NULL
	 || (d->z = tvb_malloc(sizeof(double)*n_dim)) == NULL
     || sch_base_init(&d->base,
            time, dt,
            n_dim, n_in, n_out,
            sys, hist, rng,
            n_byte,
            one_step_free,
            copy,
            one_step_apply,  &sample) != TVB_OK
		)
	{
		if (d->f!=NULL) tvb_free(d->f);
		if (d->g!=NULL) tvb_free(d->g);
		if (d->z!=NULL) tvb_free(d->z);
        if (d != NULL) tvb_free(d);
		tvb_err("alloc scheme failed.");
		return NULL;
	}
	d->sqrt_dt = sqrt(dt);
	
	d->base.sch.data = d;
	d->base.sch.copy = &copy;
	d->base.sch.n_byte = &n_byte;
	d->base.sch.free = &one_step_free;
	return &d->base.sch;
}

struct tvb_sch *
tvb_sch_new_id(
    double time,
    struct tvb_sys *sys,struct tvb_hist *hist, struct tvb_rng *rng)
{
	struct tvb_sch *new = new_one_step(time, 1.0, sys, hist, rng);
	new->apply = &id_apply;
	return new;
}

struct tvb_sch *
tvb_sch_new_em(double time, double dt,
    struct tvb_sys *sys, struct tvb_hist *hist, struct tvb_rng *rng)
{
	struct tvb_sch *new = new_one_step(time, dt, sys, hist, rng);
	new->apply = &em_apply;
	return new;
}

/* }}} */

/* vim: foldmethod=marker
 */
