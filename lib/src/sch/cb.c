/* copyright 2016 Apache 2 libtvb authors */

#include "libtvb.h"
#include "sch/base.h"

struct data
{
	struct sch_base base;
	void *user_data;
	enum tvb_stat (*user_apply)(void *);
};

static enum tvb_stat apply(struct tvb_sch *tvb_sch)
{
	struct data *data = tvb_sch->data;
	return data->user_apply(data->user_data);
}

/* obj free n byte copy {{{ */

static void cb_free(struct tvb_sch *tvb_sch)
{
    struct data *data = tvb_sch->data;
    sch_base_pointers_free(&data->base);
	tvb_free(tvb_sch->data);
}

static uint32_t n_byte(struct tvb_sch *tvb_sch)
{
	(void) tvb_sch;
	uint32_t byte_count = sizeof(struct data);
	return byte_count;
}

static struct tvb_sch *copy(struct tvb_sch *tvb_sch)
{
	struct data *data = tvb_sch->data;
	struct sch_base *base = &data->base;
	struct tvb_sch *copy;
	copy = tvb_sch_new_cb(base->time, base->dt,
		base->sys, base->hist, base->rng,
		data->user_data, data->user_apply);
	if (copy == NULL)
		tvb_err("copy sch cb failed.");
	return copy;
}

static struct tvb_out_sample sample(struct tvb_sch *tvb_sch)
{
    struct data *data = tvb_sch->data;
    return sch_base_sample(&data->base);
}

struct tvb_sch *
tvb_sch_new_cb(
	double time, double dt,
	struct tvb_sys *sys,
	struct tvb_hist *hist,
	struct tvb_rng *rng,
	void *user_data,
	enum tvb_stat(*user_apply)(void *))
{
	struct data *data = NULL;
	if ((data = tvb_malloc(sizeof(struct data))) == NULL
     || sch_base_init(&data->base,
            time, dt,
            sys->get_n_dim(sys),
            sys->get_n_in(sys),
            sys->get_n_out(sys),
            sys, hist, rng,
            &n_byte, &cb_free, &copy, &apply, &sample) != TVB_OK
    )
	{
        if (data != NULL) tvb_free(data);
		tvb_err("alloc sch cb failed.");
		return NULL;
	}
	data->base.sch.data = data;
	data->user_data = user_data;
	data->user_apply = user_apply;
	return &data->base.sch;
}

/* vim: foldmethod=marker
 */
