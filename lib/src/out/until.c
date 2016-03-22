/* copyright 2016 Apache 2 sddekit authors */

#include "sddekit.h"

struct data
{
	uint32_t n_dim, n_out;
	double time;
	struct sd_out sd_out;
};

/* out n dim n out apply {{{ */

static uint32_t
out_n_dim(struct sd_out *sd_out)
{
	return ((struct data *) sd_out->data)->n_dim;
}

static uint32_t
out_n_out(struct sd_out *sd_out)
{
	return ((struct data *) sd_out->data)->n_out;
}

static enum
sd_stat apply(struct sd_out *sd_out, struct sd_out_sample *samp)
{
	struct data *data = sd_out->data;
	data->n_dim = samp->n_dim;
	data->n_out = samp->n_out;
	return samp->time < data->time ? SD_CONT : SD_STOP;
}

/* }}} */

/* ojb free n byte copy {{{ */

static void data_free(struct sd_out *sd_out)
{
	sd_free(sd_out->data);
}

static uint32_t data_n_byte(struct data *data)
{
	(void) data;
	return sizeof(struct data);
}

static struct data *data_copy(struct data *data)
{
	struct data *copy = sd_out_new_until(data->time)->data;
	if (copy == NULL)
		sd_err("copy out until failed.");
	return copy;
}

sd_declare_tag_functions(sd_out)

/* }}} */

static struct sd_out sd_out_defaults = {
	sd_declare_tag_vtable(sd_out),
	.get_n_dim = &out_n_dim,
	.get_n_out = &out_n_out,
	.apply = &apply
};

SD_API struct sd_out *
sd_out_new_until(double time)
{
	struct data *data, zero = {0};
	if ((data = sd_malloc(sizeof(struct data))) == NULL)
	{
		sd_err("alloc out until failed.");
		return NULL;
	}
	data->time = time;
	data->sd_out = sd_out_defaults;
	data->sd_out.data = data;
	return &(data->sd_out);
}

/* vim: foldmethod=marker
 */
