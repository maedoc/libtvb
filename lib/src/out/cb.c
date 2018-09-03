/* copyright 2016 Apache 2 libtvb authors */

#include "libtvb.h"

struct data
{
	struct tvb_out out;
	void *user_data;
	enum tvb_stat (*user_apply)(
		void *user_data,
		struct tvb_out_sample *sample);
};

static enum tvb_stat apply(struct tvb_out *out,
		          struct tvb_out_sample *sample)
{
	struct data *d = out->data;
	return d->user_apply(d->user_data, sample);
}

/* obj {{{ */

static void cb_free(struct tvb_out *out)
{
	tvb_free(out->data);
}

static uint32_t n_byte(struct tvb_out *out)
{
	(void) out;
	return sizeof(struct tvb_out);
}

static struct tvb_out* copy(struct tvb_out *out)
{
	struct data *data = out->data;
	struct tvb_out *copy;
	copy = tvb_out_new_cb(data->user_data, data->user_apply);
	if (copy == NULL)
	{
		tvb_err("out cb copy failed.");
	}
	return copy;
}

/* }}} */

static struct tvb_out defaults = {
	.free = &cb_free,
	.copy = &copy,
	.n_byte = &n_byte,
	.apply = &apply
};

TVB_API struct tvb_out *
tvb_out_new_cb(void *user_data,
	enum tvb_stat (*user_apply)(
		void *, struct tvb_out_sample *))
{
	struct data *data;
        if ((data = tvb_malloc(sizeof(struct data))) == NULL)
	{
		tvb_err("alloc out cb failed.");
		return NULL;
	}
	data->out = defaults;
	data->out.data = data;
	data->user_data = user_data;
	data->user_apply = user_apply;
	return &(data->out);
}
