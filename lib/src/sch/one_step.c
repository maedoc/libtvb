/* copyright 2016 Apache 2 sddekit authors */

#include "sddekit.h"
#include "sch/base.h"
#include <math.h>

struct data
{
	struct sch_base base;
	double *f, *g, *z, sqrt_dt;
};

/* free & n_byte {{{ */

void one_step_free(struct sd_sch *sch)
{
	struct data *d = sch->data;
    sch_base_pointers_free(&d->base);
	sd_free(d->f);
	sd_free(d->g);
	sd_free(d->z);
	sd_free(d);
}

static uint32_t
n_byte(struct sd_sch *sd_sch)
{
	struct data *data = sd_sch->data;
	uint32_t byte_count = sizeof(struct data);
	byte_count += sizeof(double) * data->base.n_dim * 3;
	byte_count += sch_base_pointers_n_byte(&data->base);
	return byte_count;
}

/* }}} */

/* apply {{{ */

static enum sd_stat
one_step_apply(struct sd_sch *sch)
{
	enum sd_stat stat;
	struct data *d = sch->data;
	struct sch_base *b = &d->base;
	struct sd_sys_in in = sch_base_sys_in(b, b->time);
	struct sd_sys_out out = sch_base_sys_out(b, d->f, d->g);

	/* query hist, compute drift & diffusion, rng */
	b->hist->query(b->hist, b->time, b->input);
	if ((stat=b->sys->apply(b->sys, &in, &out))!=SD_OK)
		return stat;
	b->rng->fill_norm(b->rng, b->n_dim, d->z);

	/* compute step & set history */
	return SD_OK;
}

static enum sd_stat
id_apply(struct sd_sch *sch)
{
	enum sd_stat stat;
	struct data *d = sch->data;
	struct sch_base *b = &d->base;
	if ((stat = one_step_apply(sch))!=SD_OK)
		return stat;
	for (uint32_t i=0; i<b->n_dim; i++)
		b->state[i] = d->f[i] + d->g[i] * d->z[i];
	b->time += 1;
	b->hist->update(b->hist, b->time, b->output);
	return SD_OK;
}

static enum sd_stat
em_apply(struct sd_sch *sch)
{
	enum sd_stat stat;
	struct data *d = sch->data;
	struct sch_base *b = &d->base;
	if ((stat = one_step_apply(sch)) != SD_OK)
		return stat;
	for (uint32_t i=0; i<b->n_dim; i++)
		b->state[i] += d->base.dt * d->f[i] \
			       + d->sqrt_dt * d->g[i] * d->z[i];
	b->time += b->dt;
	b->hist->update(b->hist, b->time, b->output);
	return SD_OK;
}

static struct sd_sch*
copy(struct sd_sch *sd_sch)
{
	struct data *data = sd_sch->data;
	struct sch_base *base = &data->base;
	struct sd_sch *copy;
	if (sd_sch->apply == &id_apply)
		copy = sd_sch_new_id(base->time,
				base->sys, base->hist, base->rng);
	else
		copy = sd_sch_new_em(base->time, base->dt,
				base->sys, base->hist, base->rng);
	if (copy == NULL)
		sd_err("copy one step sch failed.");
	struct data *copy_data = copy->data;
	sch_base_pointers_copy(base, &copy_data->base);
	memcpy(copy_data->f, data->f, sizeof(double) * base->n_dim);
	memcpy(copy_data->g, data->g, sizeof(double) * base->n_dim);
	memcpy(copy_data->z, data->z, sizeof(double) * base->n_dim);
	return copy;
}

static struct sd_out_sample sample(struct sd_sch *sd_sch)
{
    struct data *data = sd_sch->data;
    return sch_base_sample(&data->base);
}

/* constructors {{{ */

static struct sd_sch *
new_one_step(double time, double dt,
    struct sd_sys *sys, struct sd_hist *hist, struct sd_rng *rng)
{
	struct data *d, z = {0};;
	/* n_dim, n_in, n_out allocations here, scheme owns it all */
	uint32_t n_dim = sys->get_n_dim(sys)
           , n_in = sys->get_n_in(sys)
           , n_out = sys->get_n_out(sys);
	if ((d = sd_malloc(sizeof(struct data))) == NULL
	 || (*d=z, 0)
	 || (d->f = sd_malloc(sizeof(double)*n_dim)) == NULL
	 || (d->g = sd_malloc(sizeof(double)*n_dim)) == NULL
	 || (d->z = sd_malloc(sizeof(double)*n_dim)) == NULL
     || sch_base_init(&d->base,
            time, dt,
            n_dim, n_in, n_out,
            sys, hist, rng,
            n_byte,
            one_step_free,
            copy,
            one_step_apply,  &sample) != SD_OK
		)
	{
		if (d->f!=NULL) sd_free(d->f);
		if (d->g!=NULL) sd_free(d->g);
		if (d->z!=NULL) sd_free(d->z);
        if (d != NULL) sd_free(d);
		sd_err("alloc scheme failed.");
		return NULL;
	}
	d->sqrt_dt = sqrt(dt);
	
	d->base.sch.data = d;
	d->base.sch.copy = &copy;
	d->base.sch.n_byte = &n_byte;
	d->base.sch.free = &one_step_free;
	return &d->base.sch;
}

struct sd_sch *
sd_sch_new_id(
    double time,
    struct sd_sys *sys,struct sd_hist *hist, struct sd_rng *rng)
{
	struct sd_sch *new = new_one_step(time, 1.0, sys, hist, rng);
	new->apply = &id_apply;
	return new;
}

struct sd_sch *
sd_sch_new_em(double time, double dt,
    struct sd_sys *sys, struct sd_hist *hist, struct sd_rng *rng)
{
	struct sd_sch *new = new_one_step(time, dt, sys, hist, rng);
	new->apply = &em_apply;
	return new;
}

/* }}} */

/* vim: foldmethod=marker
 */
