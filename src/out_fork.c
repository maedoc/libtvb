/* copyright 2016 Apache 2 sddekit authors */

#include "sddekit.h"

struct data
{
	uint32_t n_receiver, n_dim, n_out;
	struct sd_out **receivers;
	struct sd_out sd_out;
	struct sd_out_fork sd_out_fork;
};

/* obj n_byte free copy {{{ */

static uint32_t data_n_byte(struct data *data)
{
	uint32_t byte_count = sizeof(struct data);
	byte_count += sizeof(struct sd_out *) * data->n_receiver;
	return byte_count;
}

static void data_free(struct data *data)
{
	sd_free(data->receivers);
	sd_free(data);
}

static struct data *data_copy(struct data *data)
{
	struct data *copy = sd_out_fork_new(data->n_receiver, data->receivers)->data;
	if (copy == NULL)
		{sd_err("copy out fork failed.");}
	return copy;
}

sd_declare_tag_functions(sd_out)
sd_declare_tag_functions(sd_out_fork)

/* }}} */

/* out apply n_dim n_out {{{ */

static enum sd_stat fork_apply(
	struct sd_out *sd_out, struct sd_out_sample *samp)
{
	struct data *data = sd_out->data;
	data->n_dim = samp->n_dim;
	data->n_out = samp->n_out;
	for (uint32_t i=0; i<data->n_receiver; i++)
	{
		struct sd_out *recv = data->receivers[i];
		enum sd_stat stat = recv->apply(recv, samp);
		if (stat != SD_CONT)
			return stat;
	}
	return SD_CONT;
}

static uint32_t out_n_dim(struct sd_out *sd_out)
{
	return ((struct data *) sd_out->data)->n_dim;
}

static uint32_t out_n_out(struct sd_out *sd_out)
{
	return ((struct data *) sd_out->data)->n_out;
}

/* }}} */

/* fork getters {{{ */

static struct sd_out *
fork_as_out(struct sd_out_fork *fork)
{
	return &((struct data *) fork->data)->sd_out;
}

static uint32_t 
fork_get_n_receiver(struct sd_out_fork *fork)
{
	return ((struct data *) fork->data)->n_receiver;
}

static struct sd_out *
fork_get_receiver(struct sd_out_fork *fork, uint32_t i)
{
	return ((struct data *) fork->data)->receivers[i];
}


/* }}} */

/* vtables {{{ */

static struct sd_out sd_out_defaults = {
	sd_declare_tag_vtable(sd_out),
	.get_n_dim = &out_n_dim,
	.get_n_out = &out_n_out,
	.apply = &fork_apply
};

static struct sd_out_fork sd_out_fork_defaults = {
	sd_declare_tag_vtable(sd_out_fork),
	.as_out = &fork_as_out,
	.get_n_receiver = &fork_get_n_receiver,
	.get_receiver = &fork_get_receiver
};

/* }}} */

struct sd_out_fork *
sd_out_fork_new(uint32_t n_receiver, struct sd_out **receivers)
{
	struct data *data, zero = {0};
	/* alloc & error check {{{ */
	if ((data = sd_malloc(sizeof(struct data))) == NULL
	 || (*data = zero, n_receiver == 0 || receivers == NULL)
	 || (data->receivers = sd_malloc(sizeof(struct sd_out *) * n_receiver))
	)
	{
		if (data != NULL) sd_free(data);
		sd_err("alloc out fork fail or n_receiver=0 or NULL receiver array.");
		return NULL;
	}
	/* }}} */
	data->n_receiver = n_receiver;
	memcpy(data->receivers, receivers, sizeof(struct sd_out *) * n_receiver);
	data->sd_out = sd_out_defaults;
	data->sd_out_fork = sd_out_fork_defaults;
	data->sd_out.data = data->sd_out_fork.data = data;
	return &data->sd_out_fork;
}

/* vim: foldmethod=marker
 */
