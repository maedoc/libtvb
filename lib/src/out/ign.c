/* copyright 2016 Apache 2 sddekit authors */

#include "sddekit.h"

struct data
{
	bool ignore_state, ignore_output;
	uint32_t n_dim, n_out;
	struct sd_out *receiver;
	struct sd_out sd_out;
};

static enum sd_stat apply(struct sd_out *sd_out, struct sd_out_sample *samp)
{
	struct data *data = sd_out->data;
	struct sd_out_sample samp_out = *samp;
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

static void data_free(struct sd_out *sd_out)
{
	sd_free(sd_out->data);
}

static uint32_t data_n_byte(struct sd_out *sd_out)
{
	return sizeof(struct data);
}

static struct sd_out *data_copy(struct sd_out *sd_out)
{
	struct data *data = sd_out->data;
	struct sd_out *copy = sd_out_new_ign(
		data->ignore_state,
		data->ignore_output,
		data->receiver);
	if (copy == NULL)
		sd_err("copy out ign failed.");
	return copy;
}

static uint32_t get_n_dim(struct sd_out *sd_out)
{
	return ((struct data *) sd_out->data)->n_dim;
}

static uint32_t get_n_out(struct sd_out *sd_out)
{
	return ((struct data *) sd_out->data)->n_out;
}

static struct sd_out sd_out_defaults = {
	.free = &data_free,
	.n_byte = &data_n_byte,
	.copy = &data_copy,
	.apply = &apply,
	.get_n_dim = &get_n_dim,
	.get_n_out = &get_n_out
};

struct sd_out *
sd_out_new_ign(bool ignore_state, bool ignore_output, struct sd_out *receiver)
{
	struct data *data, zero = {0};
	if ((data = sd_malloc(sizeof(struct data))) == NULL
	 || (*data = zero, receiver == NULL)
	)
	{
		if (data != NULL) sd_free(data);
		sd_err("alloc ign out failed or NULL receiver.");
		return NULL;
	}
	data->ignore_state = ignore_state;
	data->ignore_output = ignore_output;
	data->receiver = receiver;
	data->sd_out = sd_out_defaults;
	data->sd_out.data = data;
	return &(data->sd_out);
}
