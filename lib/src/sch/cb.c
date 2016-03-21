/* copyright 2016 Apache 2 sddekit authors */

#include "sddekit.h"
#include "sch/base.h"

struct data
{
	struct sch_base base;
	void *user_data;
	enum sd_stat (*user_apply)(void *);
};

static enum sd_stat apply(struct sd_sch *sd_sch)
{
	struct data *data = sd_sch->data;
	return data->user_apply(data->user_data);
}

/* obj free n byte copy {{{ */

static void cb_free(struct sd_sch *sd_sch)
{
	sd_free(sd_sch->data);
}

static uint32_t n_byte(struct sd_sch *sd_sch)
{
	(void) sd_sch;
	uint32_t byte_count = sizeof(struct data);
	return byte_count;
}

static struct sd_sch *copy(struct sd_sch *sd_sch)
{
	struct data *data = sd_sch->data;
	struct sch_base *base = &data->base;
	struct sd_sch *copy;
	copy = sd_sch_new_cb(base->time, base->dt,
		base->sys, base->hist, base->rng,
		data->user_data, data->user_apply);
	if (copy == NULL)
		sd_err("copy sch cb failed.");
	return copy;
}

/* }}} */

struct sd_sch *
sd_sch_new_cb(
	double time, double dt,
	struct sd_sys *sys,
	struct sd_hist *hist,
	struct sd_rng *rng,
	void *user_data,
	enum sd_stat(*user_apply)(void *))
{
	struct data *data;
	if ((data = sd_malloc(sizeof(struct data))) == NULL)
	{
		sd_err("alloc sch cb failed.");
		return NULL;
	}
	sch_base_init(&data->base,
		time, dt,
		sys->get_n_dim(sys),
		sys->get_n_in(sys),
		sys->get_n_out(sys),
		sys, hist, rng,
		&n_byte, &cb_free, &copy, &apply);
	data->base.sch.data = data;
	data->user_data = user_data;
	data->user_apply = user_apply;
	return &data->base.sch;
}

/* vim: foldmethod=marker
 */
