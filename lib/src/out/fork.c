/* copyright 2016 Apache 2 libtvb authors */

#include "libtvb.h"

struct data
{
	uint32_t n_receiver, n_dim, n_out;
	struct tvb_out **receivers;
	struct tvb_out tvb_out;
	struct tvb_out_fork tvb_out_fork;
};

/* obj n_byte free copy {{{ */

static uint32_t data_n_byte(struct data *data)
{
	uint32_t byte_count = sizeof(struct data);
	byte_count += sizeof(struct tvb_out *) * data->n_receiver;
	return byte_count;
}

static void data_free(struct data *data)
{
	tvb_free(data->receivers);
	tvb_free(data);
}

static struct data *data_copy(struct data *data)
{
	struct data *copy = tvb_out_fork_new(data->n_receiver, data->receivers)->data;
	if (copy == NULL)
		{tvb_err("copy out fork failed.");}
	return copy;
}

tvb_declare_tag_functions(tvb_out)
tvb_declare_tag_functions(tvb_out_fork)

/* }}} */

/* out apply n_dim n_out {{{ */

static enum tvb_stat fork_apply(
	struct tvb_out *tvb_out, struct tvb_out_sample *samp)
{
	struct data *data = tvb_out->data;
	data->n_dim = samp->n_dim;
	data->n_out = samp->n_out;
	for (uint32_t i=0; i<data->n_receiver; i++)
	{
		struct tvb_out *recv = data->receivers[i];
		enum tvb_stat stat = recv->apply(recv, samp);
		if (stat != TVB_CONT)
			return stat;
	}
	return TVB_CONT;
}

static uint32_t out_n_dim(struct tvb_out *tvb_out)
{
	return ((struct data *) tvb_out->data)->n_dim;
}

static uint32_t out_n_out(struct tvb_out *tvb_out)
{
	return ((struct data *) tvb_out->data)->n_out;
}

/* }}} */

/* fork getters {{{ */

static struct tvb_out *
fork_as_out(struct tvb_out_fork *fork)
{
	return &((struct data *) fork->data)->tvb_out;
}

static uint32_t 
fork_get_n_receiver(struct tvb_out_fork *fork)
{
	return ((struct data *) fork->data)->n_receiver;
}

static struct tvb_out *
fork_get_receiver(struct tvb_out_fork *fork, uint32_t i)
{
	return ((struct data *) fork->data)->receivers[i];
}


/* }}} */

/* vtables {{{ */

static struct tvb_out tvb_out_defaults = {
	tvb_declare_tag_vtable(tvb_out),
	.get_n_dim = &out_n_dim,
	.get_n_out = &out_n_out,
	.apply = &fork_apply
};

static struct tvb_out_fork tvb_out_fork_defaults = {
	tvb_declare_tag_vtable(tvb_out_fork),
	.as_out = &fork_as_out,
	.get_n_receiver = &fork_get_n_receiver,
	.get_receiver = &fork_get_receiver
};

/* }}} */

struct tvb_out_fork *
tvb_out_fork_new(uint32_t n_receiver, struct tvb_out **receivers)
{
	struct data *data, zero = {0};
	/* alloc & error check {{{ */
	if ((data = tvb_malloc(sizeof(struct data))) == NULL
	 || (*data = zero, n_receiver == 0 || receivers == NULL)
	 || (data->receivers = tvb_malloc(sizeof(struct tvb_out *) * n_receiver)) == NULL
	)
	{
		if (data != NULL) tvb_free(data);
		tvb_err("alloc out fork fail or n_receiver=0 or NULL receiver array.");
		return NULL;
	}
	/* }}} */
	data->n_receiver = n_receiver;
	memcpy(data->receivers, receivers, sizeof(struct tvb_out *) * n_receiver);
	data->tvb_out = tvb_out_defaults;
	data->tvb_out_fork = tvb_out_fork_defaults;
	data->tvb_out.data = data->tvb_out_fork.data = data;
	return &data->tvb_out_fork;
}

/* vim: foldmethod=marker
 */
