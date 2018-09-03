/* copyright 2016 Apache 2 libtvb authors */

#include "libtvb.h"

/* temporal convolution */

/* data {{{ */
struct data
{
	/* pos of latest sample in buffer, len of buffer */
	uint32_t position, length;
	/* downsample factor & counter */
	uint32_t n_skip, n_to_skip;
	/* length of x & c inputs */
	uint32_t n_dim, n_out;
	/* state, coupling buffers & filter / conv kernel coefs */
	double time, *state, *output, *state_out, *output_out, *kernel;
	/* out to which we'll pass data */
	struct tvb_out *receiver;
	/* interfaces to this data */
	struct tvb_out tvb_out;
	struct tvb_out_conv tvb_out_conv;
};
/* }}} */

/* n_byte copy free {{{ */

static void data_free(struct data *data)
{
	tvb_free(data->state);
	tvb_free(data->output);
	tvb_free(data->state_out);
	tvb_free(data->output_out);
	tvb_free(data->kernel);
	tvb_free(data); 
}

static uint32_t data_n_byte(struct data *data)
{
	(void) data;
	uint32_t byte_count = sizeof(struct data);
	uint32_t n_dim_out = data->n_dim + data->n_out;
	byte_count += sizeof(double) * (n_dim_out + data->length * n_dim_out);
	return byte_count;
}

static struct data * data_copy(struct data *data)
{
	(void) data;
	/* call constructor.. */
	return NULL;
}


tvb_declare_tag_functions(tvb_out_conv)
tvb_declare_tag_functions(tvb_out)

/* }}} */
static enum tvb_stat
setup_buffers(struct data *data, struct tvb_out_sample *samp)
{
	data->n_dim = samp->n_dim;
	data->n_out = samp->n_out;
	/* first call, alloc buffers */
	if ((data->state = tvb_malloc(sizeof(double) * data->length * samp->n_dim)) == NULL
	 || (data->output = tvb_malloc(sizeof(double) * data->length * samp->n_out)) == NULL
	 || (data->state_out = tvb_malloc(sizeof(double) * samp->n_dim)) == NULL
	 || (data->output_out = tvb_malloc(sizeof(double) * samp->n_out)) == NULL
	 ) 
	{
		if (data->state != NULL) tvb_free(data->state);
		if (data->output != NULL) tvb_free(data->output);
		if (data->state_out != NULL) tvb_free(data->state_out);
		tvb_err("alloc conv buffers failed.");
		return TVB_ERR;
	}
	data->n_to_skip = data->n_skip;
	data->position = data->length - 1; /* so pos resets to 0 on first call */
	return TVB_OK;
}

static void
store_sample(struct data *data, struct tvb_out_sample *samp)
{
	data->position++;
	if (data->position == data->length)
		data->position = 0;
	memcpy(data->state + data->position * data->n_dim,
		samp->state, sizeof(double) * data->n_dim);
	memcpy(data->output + data->position * data->n_out,
		samp->output, sizeof(double) * data->n_out);
	data->time = samp->time;
}

static enum tvb_stat
push_sample_to_receiver(struct data *data)
{
	/* zero output buffers */
	for (uint32_t i=0; i<data->n_dim; i++)
		data->state_out[i] = 0.0;
	for (uint32_t i=0; i<data->n_out; i++)
		data->output_out[i] = 0.0;
	/* integrate over time */
	for (uint32_t i=0; i<data->length; i++)
	{
		/* circular index on buffer starts at oldest sample, moving forward through time */
		uint32_t ci = (data->position + 1 + i) % data->length;
		/* filter index moves backward through time */
		uint32_t fi = data->length - i - 1;
		/* increment weighted sums for state */
		for (uint32_t j=0; j<data->n_dim; j++)
			data->state_out[j] += data->kernel[fi] 
				* data->state[ci * data->n_dim + j];
		/* and output vectors */
		for (uint32_t j=0; j<data->n_out; j++)
			data->output_out[j] += data->kernel[fi]
				* data->output[ci * data->n_out + j];
	}
	struct tvb_out_sample samp_out = {
		.time = data->time,
		.n_dim = data->n_dim,
		.n_out = data->n_out,
		.state = data->state_out,
		.output = data->output_out
	};
	data->n_to_skip = data->n_skip;
	return data->receiver->apply(data->receiver, &samp_out);
}

static enum tvb_stat
apply(struct tvb_out *tvb_out, struct tvb_out_sample *samp)
{
	struct data *data = tvb_out->data;
	if (data->state == NULL)
	{
		enum tvb_stat stat = setup_buffers(data, samp);
		if (stat != TVB_OK)
			return stat;
	}
	store_sample(data, samp);
	if (--data->n_to_skip == 0)
	{
		enum tvb_stat stat = push_sample_to_receiver(data);
		if (stat != TVB_CONT)
			return stat;
	}
	return TVB_CONT;
}

static uint32_t get_pos(struct tvb_out_conv *c) { return ((struct data*) c->data)->position; }
static uint32_t get_len(struct tvb_out_conv *c) { return ((struct data*) c->data)->length; }
static uint32_t get_n_skip(struct tvb_out_conv *c) { return ((struct data*) c->data)->n_skip; }
static struct tvb_out *get_receiver(struct tvb_out_conv *c) { return ((struct data*) c->data)->receiver; }

static uint32_t get_n_dim(struct tvb_out *c) { return ((struct data*) c->data)->n_dim; }
static uint32_t get_n_out(struct tvb_out *c) { return ((struct data*) c->data)->n_out; }

static struct tvb_out *as_out(struct tvb_out_conv *tvb_out_conv)
{
	return &((struct data *) tvb_out_conv->data)->tvb_out;
}

static struct tvb_out_conv tvb_out_conv_defaults = {
	tvb_declare_tag_vtable(tvb_out_conv),
	.as_out = &as_out,
	.get_position = &get_pos,
	.get_length = &get_len,
	.get_n_skip = &get_n_skip,
	.get_receiver = &get_receiver
};

static struct tvb_out tvb_out_defaults = {
	tvb_declare_tag_vtable(tvb_out),
	.apply = &apply,
	.get_n_dim = &get_n_dim,
	.get_n_out = &get_n_out
};

struct tvb_out_conv *
tvb_out_conv_new(uint32_t length, double *kernel, uint32_t n_skip, struct tvb_out *receiver)
{
	struct data *data, zero = {0};
	if ((data = tvb_malloc(sizeof(struct data))) == NULL 
	 || (*data = zero, receiver == NULL)
	 || (data->kernel = tvb_malloc(sizeof(double) * length)) == NULL
	)
	{
		if (data != NULL) tvb_free(data);
		tvb_err("alloc fail or NULL receiver.");
		return NULL;
	}
	data->receiver = receiver;
	data->tvb_out = tvb_out_defaults;
	data->tvb_out_conv = tvb_out_conv_defaults;
	data->tvb_out.data = data->tvb_out_conv.data = data;
	data->length = length;
	data->n_skip = data->n_to_skip = n_skip;
	memcpy(data->kernel, kernel, sizeof(double) * length);
	return &(data->tvb_out_conv);
}

/* vim: foldmethod=marker
 */
