/* copyright 2016 Apache 2 libtvb authors */

#include "libtvb.h"

struct data
{
	bool ignore_state, ignore_output;
	uint32_t n_dim, n_out;
	struct tvb_out *receiver;
	struct tvb_out tvb_out;
};

static enum tvb_stat apply(struct tvb_out *tvb_out, struct tvb_out_sample *samp)
{
	struct data *data = tvb_out->data;
	struct tvb_out_sample samp_out = *samp;
	if (data->ignore_state)
	{
		samp_out.n_dim = 0;
		samp_out.state = NULL;
	}
	if (data->ignore_output)
	{
		samp_out.n_out = 0;
		samp_out.output = NULL;
	}
	data->n_dim = samp_out.n_dim;
	data->n_out = samp_out.n_out;
	return data->receiver->apply(data->receiver, &samp_out);
}

static void data_free(struct tvb_out *tvb_out)
{
	tvb_free(tvb_out->data);
}

static uint32_t data_n_byte(struct tvb_out *tvb_out)
{
	return sizeof(struct data);
}

static struct tvb_out *data_copy(struct tvb_out *tvb_out)
{
	struct data *data = tvb_out->data;
	struct tvb_out *copy = tvb_out_new_ign(
		data->ignore_state,
		data->ignore_output,
		data->receiver);
	if (copy == NULL)
		tvb_err("copy out ign failed.");
	return copy;
}

static uint32_t get_n_dim(struct tvb_out *tvb_out)
{
	return ((struct data *) tvb_out->data)->n_dim;
}

static uint32_t get_n_out(struct tvb_out *tvb_out)
{
	return ((struct data *) tvb_out->data)->n_out;
}

static struct tvb_out tvb_out_defaults = {
	.free = &data_free,
	.n_byte = &data_n_byte,
	.copy = &data_copy,
	.apply = &apply,
	.get_n_dim = &get_n_dim,
	.get_n_out = &get_n_out
};

struct tvb_out *
tvb_out_new_ign(bool ignore_state, bool ignore_output, struct tvb_out *receiver)
{
	struct data *data, zero = {0};
	if ((data = tvb_malloc(sizeof(struct data))) == NULL
	 || (*data = zero, receiver == NULL)
	)
	{
		if (data != NULL) tvb_free(data);
		tvb_err("alloc ign out failed or NULL receiver.");
		return NULL;
	}
	data->ignore_state = ignore_state;
	data->ignore_output = ignore_output;
	data->receiver = receiver;
	data->tvb_out = tvb_out_defaults;
	data->tvb_out.data = data;
	return &(data->tvb_out);
}
