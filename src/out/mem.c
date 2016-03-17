/* copyright 2016 Apache 2 sddekit authors */

#include "sddekit.h"

struct data
{
	uint32_t n_sample, capacity, n_dim, n_out;
	double *states, *outputs;
	struct sd_out sd_out;
	struct sd_out_mem sd_out_mem;
};

/* getters {{{ */

#define GET(type, field) \
static type \
get_ ## field(struct sd_out_mem *sd_out_mem) \
{ \
	return ((struct data *) sd_out_mem->data)->field; \
}

GET(uint32_t, n_sample)
GET(double *, states)
GET(double *, outputs)

#undef GET

static uint32_t get_n_dim(struct sd_out *sd_out)
{
	return ((struct data *) sd_out->data)->n_dim;
}

static uint32_t get_n_out(struct sd_out *sd_out)
{
	return ((struct data *) sd_out->data)->n_out;
}

static struct sd_out * mem_as_out(struct sd_out_mem *sd_out_mem)
{
	return &(((struct data *)sd_out_mem->data)->sd_out);
}

/* }}} */

static void data_free(struct data *data) 
{
	sd_free(data->states);
	sd_free(data->outputs);
	sd_free(data);
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
	if ((copy = sd_malloc(sizeof(struct data))) == NULL
	 || (*copy = zero, 0)
	 || (copy->states = sd_malloc(bytes_per_n * data->n_dim)) == NULL
	 || (copy->outputs = sd_malloc(bytes_per_n * data->n_out)) == NULL
	)
	{
		if (copy->states != NULL)
			sd_free(copy->states);
		if (copy != NULL)
			sd_free(copy);
		sd_err("alloc out mem copy failed.");
		return NULL;
	}
	copy->n_sample = data->n_sample;
	copy->capacity = data->capacity;
	copy->n_dim = data->n_dim;
	copy->n_out = data->n_out;
	copy->sd_out = data->sd_out;
	copy->sd_out_mem = data->sd_out_mem;
	memcpy(copy->states, data->states, bytes_per_n * copy->n_dim);
	memcpy(copy->outputs, data->outputs, bytes_per_n * copy->n_out);
	return copy;
}

sd_declare_tag_functions(sd_out)
sd_declare_tag_functions(sd_out_mem)

/* apply impl {{{ */

static enum sd_stat
setup_buffers(struct data *data, struct sd_out_sample *samp)
{
	data->n_dim = samp->n_dim;
	data->n_out = samp->n_out;
	if ((data->states = sd_malloc(sizeof(double) * data->n_dim)) == NULL
	 || (data->outputs = sd_malloc(sizeof(double) * data->n_out)) == NULL
	)
	{
		sd_err("alloc out mem buffers failed.");
		if (data->states != NULL)
			sd_free(data->states);
		return SD_ERR;
	}
	data->capacity = 1;
	return SD_OK;
}

static void append_sample(struct data *data, struct sd_out_sample *samp)
{
	memcpy(data->states + data->n_sample * data->n_dim,
		samp->state, sizeof(double) * data->n_dim);
	memcpy(data->states + data->n_sample * data->n_out,
		samp->output, sizeof(double) * data->n_out);
	data->n_sample++;
}

static enum sd_stat
realloc_buffers(struct data *data)
{
	uint32_t new_bytes = sizeof(double) * data->capacity * 2;
	double *new_states = NULL, *new_outputs = NULL;
	/* If realloc return is not NULL, we *must* use it */
	if ((new_states = sd_realloc(data->states, new_bytes * data->n_dim)) != NULL)
		data->states = new_states;
	if ((new_outputs = sd_realloc(data->outputs, new_bytes * data->n_out)) != NULL)
		data->outputs = new_outputs;
	if (new_states == NULL || new_outputs == NULL)
	{
		sd_err("failed to allocate memory.");
		return SD_ERR;
	}
	data->capacity *= 2;
	return SD_OK;
}

static enum sd_stat
apply(struct sd_out *sd_out, struct sd_out_sample *samp)
{
	struct data *data = sd_out->data;
	if (data->capacity==0) {
		enum sd_stat stat = setup_buffers(data, samp);
		if (stat != SD_OK)
			return stat;
	}
	append_sample(data, samp);
	if (data->n_sample == data->capacity)
	{
		enum sd_stat stat = realloc_buffers(data);
		if (stat != SD_OK)
			return stat;
	}
	return SD_CONT;
}

/* }}} */

/* vtables {{{ */

static struct sd_out_mem sd_out_mem_defaults = {
	sd_declare_tag_vtable(sd_out_mem),
	.as_out = &mem_as_out,
	.get_n_sample = &get_n_sample,
	.get_states = &get_states,
	.get_outputs = &get_outputs
};

static struct sd_out sd_out_defaults = {
	sd_declare_tag_vtable(sd_out),
	.get_n_dim = &get_n_dim,
	.get_n_out = &get_n_out,
	.apply = &apply
};

/* }}} */

struct sd_out_mem *sd_out_mem_new() 
{
	struct data *data, zero = {0};
	if ((data = sd_malloc(sizeof(struct data))) == NULL)
	{
		sd_err("alloc out mem failed.");
		return NULL;
	}
	data->states = NULL;
	data->outputs = NULL;
	data->n_sample = 0;
	data->capacity = 0;
	data->sd_out = sd_out_defaults;
	data->sd_out_mem = sd_out_mem_defaults;
	data->sd_out.data = data->sd_out_mem.data = data;
	return &data->sd_out_mem;
}

/* vim: foldmethod=marker
 */
