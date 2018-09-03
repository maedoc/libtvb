/* copyright 2016 Apache 2 libtvb authors */

#include "libtvb.h"

struct data
{
	uint32_t n_dim, n_out;
	double time;
	struct tvb_out tvb_out;
};

/* out n dim n out apply {{{ */

static uint32_t
out_n_dim(struct tvb_out *tvb_out)
{
	return ((struct data *) tvb_out->data)->n_dim;
}

static uint32_t
out_n_out(struct tvb_out *tvb_out)
{
	return ((struct data *) tvb_out->data)->n_out;
}

static enum
tvb_stat apply(struct tvb_out *tvb_out, struct tvb_out_sample *samp)
{
	struct data *data = tvb_out->data;
	data->n_dim = samp->n_dim;
	data->n_out = samp->n_out;
	return samp->time < data->time ? TVB_CONT : TVB_STOP;
}

/* }}} */

/* ojb free n byte copy {{{ */

static void data_free(struct tvb_out *tvb_out)
{
	tvb_free(tvb_out->data);
}

static uint32_t data_n_byte(struct data *data)
{
	(void) data;
	return sizeof(struct data);
}

static struct data *data_copy(struct data *data)
{
	struct data *copy = tvb_out_new_until(data->time)->data;
	if (copy == NULL)
		tvb_err("copy out until failed.");
	return copy;
}

tvb_declare_tag_functions(tvb_out)

/* }}} */

static struct tvb_out tvb_out_defaults = {
	tvb_declare_tag_vtable(tvb_out),
	.get_n_dim = &out_n_dim,
	.get_n_out = &out_n_out,
	.apply = &apply
};

TVB_API struct tvb_out *
tvb_out_new_until(double time)
{
	struct data *data, zero = {0};
	if ((data = tvb_malloc(sizeof(struct data))) == NULL)
	{
		tvb_err("alloc out until failed.");
		return NULL;
	}
	data->time = time;
	data->tvb_out = tvb_out_defaults;
	data->tvb_out.data = data;
	return &(data->tvb_out);
}

/* vim: foldmethod=marker
 */
