/* copyright 2016 Apache 2 sddekit authors */

#include "sddekit.h"

struct data
{
	struct sd_out out;
	void *user_data;
	enum sd_stat (*user_apply)(
		void *user_data,
		struct sd_out_sample *sample);
};

static enum sd_stat apply(struct sd_out *out,
		          struct sd_out_sample *sample)
{
	struct data *d = out->data;
	return d->user_apply(d->user_data, sample);
}

/* obj {{{ */

static void cb_free(struct sd_out *out)
{
	sd_free(out->data);
}

static uint32_t n_byte(struct sd_out *out)
{
	(void) out;
	return sizeof(struct sd_out);
}

static struct sd_out* copy(struct sd_out *out)
{
	struct data *data = out->data;
	struct sd_out *copy;
	copy = sd_out_new_cb(data->user_data, data->user_apply);
	if (copy == NULL)
	{
		sd_err("out cb copy failed.");
	}
	return copy;
}

/* }}} */

static struct sd_out defaults = {
	.free = &cb_free,
	.copy = &copy,
	.n_byte = &n_byte,
	.apply = &apply
};

SD_API struct sd_out *
sd_out_new_cb(void *user_data,
	enum sd_stat (*user_apply)(
		void *, struct sd_out_sample *))
{
	struct data *data;
        if ((data = sd_malloc(sizeof(struct data))) == NULL)
	{
		sd_err("alloc out cb failed.");
		return NULL;
	}
	data->out = defaults;
	data->out.data = data;
	data->user_data = user_data;
	data->user_apply = user_apply;
	return &(data->out);
}
