/* copyright 2016 Apache 2 libtvb authors */

#include "libtvb.h"

struct data
{
	uint32_t n_sample, capacity, n_dim, n_out;
	double *states, *outputs;
	struct tvb_out tvb_out;
	struct tvb_out_mem tvb_out_mem;
};

/* getters {{{ */

#define GET(type, field) \
static type \
get_ ## field(struct tvb_out_mem *tvb_out_mem) \
{ \
	return ((struct data *) tvb_out_mem->data)->field; \
}

GET(uint32_t, n_sample)
GET(double *, states)
GET(double *, outputs)

#undef GET

static uint32_t get_n_dim(struct tvb_out *tvb_out)
{
	return ((struct data *) tvb_out->data)->n_dim;
}

static uint32_t get_n_out(struct tvb_out *tvb_out)
{
	return ((struct data *) tvb_out->data)->n_out;
}

static struct tvb_out * mem_as_out(struct tvb_out_mem *tvb_out_mem)
{
	return &(((struct data *)tvb_out_mem->data)->tvb_out);
}

/* }}} */

static void data_free(struct data *data) 
{
	tvb_free(data->states);
	tvb_free(data->outputs);
	tvb_free(data);
}

static uint32_t data_n_byte(struct data *data)
{
	uint32_t byte_count = sizeof(struct data);
	byte_count += sizeof(double) * (data->capacity * (data->n_dim + data->n_out));
	return byte_count;
}

static struct data *data_copy(struct data *data)
{
	uint32_t bytes_per_n = data->capacity * sizeof(double);
	struct data *copy, zero = {0};
	if ((copy = tvb_malloc(sizeof(struct data))) == NULL
	 || (*copy = zero, 0)
	 || (copy->states = tvb_malloc(bytes_per_n * data->n_dim)) == NULL
	 || (copy->outputs = tvb_malloc(bytes_per_n * data->n_out)) == NULL
	)
	{
		if (copy->states != NULL)
			tvb_free(copy->states);
		if (copy != NULL)
			tvb_free(copy);
		tvb_err("alloc out mem copy failed.");
		return NULL;
	}
	copy->n_sample = data->n_sample;
	copy->capacity = data->capacity;
	copy->n_dim = data->n_dim;
	copy->n_out = data->n_out;
	copy->tvb_out = data->tvb_out;
	copy->tvb_out_mem = data->tvb_out_mem;
	memcpy(copy->states, data->states, bytes_per_n * copy->n_dim);
	memcpy(copy->outputs, data->outputs, bytes_per_n * copy->n_out);
	return copy;
}

tvb_declare_tag_functions(tvb_out)
tvb_declare_tag_functions(tvb_out_mem)

/* apply impl {{{ */

static enum tvb_stat
setup_buffers(struct data *data, struct tvb_out_sample *samp)
{
	data->n_dim = samp->n_dim;
	data->n_out = samp->n_out;
	if ((data->states = tvb_malloc(sizeof(double) * data->n_dim)) == NULL
	 || (data->outputs = tvb_malloc(sizeof(double) * data->n_out)) == NULL
	)
	{
		tvb_err("alloc out mem buffers failed.");
		if (data->states != NULL)
			tvb_free(data->states);
		return TVB_ERR;
	}
	data->capacity = 1;
	return TVB_OK;
}

static void append_sample(struct data *data, struct tvb_out_sample *samp)
{
	memcpy(data->states + data->n_sample * data->n_dim,
		samp->state, sizeof(double) * data->n_dim);
	memcpy(data->states + data->n_sample * data->n_out,
		samp->output, sizeof(double) * data->n_out);
	data->n_sample++;
}

static enum tvb_stat
realloc_buffers(struct data *data)
{
	uint32_t new_bytes = sizeof(double) * data->capacity * 2;
	double *new_states = NULL, *new_outputs = NULL;
	/* If realloc return is not NULL, we *must* use it */
	if ((new_states = tvb_realloc(data->states, new_bytes * data->n_dim)) != NULL)
		data->states = new_states;
	if ((new_outputs = tvb_realloc(data->outputs, new_bytes * data->n_out)) != NULL)
		data->outputs = new_outputs;
	if (new_states == NULL || new_outputs == NULL)
	{
		tvb_err("failed to allocate memory.");
		return TVB_ERR;
	}
	data->capacity *= 2;
	return TVB_OK;
}

static enum tvb_stat
apply(struct tvb_out *tvb_out, struct tvb_out_sample *samp)
{
	struct data *data = tvb_out->data;
	if (data->capacity==0) {
		enum tvb_stat stat = setup_buffers(data, samp);
		if (stat != TVB_OK)
			return stat;
	}
	append_sample(data, samp);
	if (data->n_sample == data->capacity)
	{
		enum tvb_stat stat = realloc_buffers(data);
		if (stat != TVB_OK)
			return stat;
	}
	return TVB_CONT;
}

/* }}} */

/* vtables {{{ */

static struct tvb_out_mem tvb_out_mem_defaults = {
	tvb_declare_tag_vtable(tvb_out_mem),
	.as_out = &mem_as_out,
	.get_n_sample = &get_n_sample,
	.get_states = &get_states,
	.get_outputs = &get_outputs
};

static struct tvb_out tvb_out_defaults = {
	tvb_declare_tag_vtable(tvb_out),
	.get_n_dim = &get_n_dim,
	.get_n_out = &get_n_out,
	.apply = &apply
};

/* }}} */

struct tvb_out_mem *tvb_out_mem_new() 
{
	struct data *data, zero = {0};
	if ((data = tvb_malloc(sizeof(struct data))) == NULL)
	{
		tvb_err("alloc out mem failed.");
		return NULL;
	}
	data->states = NULL;
	data->outputs = NULL;
	data->n_sample = 0;
	data->capacity = 0;
	data->tvb_out = tvb_out_defaults;
	data->tvb_out_mem = tvb_out_mem_defaults;
	data->tvb_out.data = data->tvb_out_mem.data = data;
	return &data->tvb_out_mem;
}

/* vim: foldmethod=marker
 */
