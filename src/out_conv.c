/* copyright 2016 Apache 2 sddekit authors */

#include "sddekit.h"

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
	struct sd_out *receiver;
	/* interfaces to this data */
	struct sd_out sd_out;
	struct sd_out_conv sd_out_conv;
};
/* }}} */

/* n_byte copy free {{{ */

static void data_free(struct data *data)
{
	sd_free(data->state);
	sd_free(data->output);
	sd_free(data->state_out);
	sd_free(data->output_out);
	sd_free(data->kernel);
	sd_free(data); 
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


sd_declare_tag_functions(sd_out_conv)
sd_declare_tag_functions(sd_out)

/* }}} */
static enum sd_stat
setup_buffers(struct data *data, struct sd_out_sample *samp)
{
	data->n_dim = samp->n_dim;
	data->n_out = samp->n_out;
	/* first call, alloc buffers */
	if ((data->state = sd_malloc(sizeof(double) * data->length * samp->n_dim)) == NULL
	 || (data->output = sd_malloc(sizeof(double) * data->length * samp->n_out)) == NULL
	 || (data->state_out = sd_malloc(sizeof(double) * samp->n_dim)) == NULL
	 || (data->output_out = sd_malloc(sizeof(double) * samp->n_out)) == NULL
	 ) 
	{
		if (data->state != NULL) sd_free(data->state);
		if (data->output != NULL) sd_free(data->output);
		if (data->state_out != NULL) sd_free(data->state_out);
		sd_err("alloc conv buffers failed.");
		return SD_ERR;
	}
	data->n_to_skip = data->n_skip;
	data->position = data->length - 1; /* so pos resets to 0 on first call */
	return SD_OK;
}

static void
store_sample(struct data *data, struct sd_out_sample *samp)
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

static enum sd_stat
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
	struct sd_out_sample samp_out = {
		.time = data->time,
		.n_dim = data->n_dim,
		.n_out = data->n_out,
		.state = data->state_out,
		.output = data->output_out
	};
	data->n_to_skip = data->n_skip;
	return data->receiver->apply(data->receiver, &samp_out);
}

static enum sd_stat
apply(struct sd_out *sd_out, struct sd_out_sample *samp)
{
	struct data *data = sd_out->data;
	if (data->state == NULL)
	{
		enum sd_stat stat = setup_buffers(data, samp);
		if (stat != SD_OK)
			return stat;
	}
	store_sample(data, samp);
	if (--data->n_to_skip == 0)
	{
		enum sd_stat stat = push_sample_to_receiver(data);
		if (stat != SD_CONT)
			return stat;
	}
	return SD_CONT;
}

static uint32_t get_pos(struct sd_out_conv *c) { return ((struct data*) c->data)->position; }
static uint32_t get_len(struct sd_out_conv *c) { return ((struct data*) c->data)->length; }
static uint32_t get_n_skip(struct sd_out_conv *c) { return ((struct data*) c->data)->n_skip; }
static struct sd_out *get_receiver(struct sd_out_conv *c) { return ((struct data*) c->data)->receiver; }

static uint32_t get_n_dim(struct sd_out *c) { return ((struct data*) c->data)->n_dim; }
static uint32_t get_n_out(struct sd_out *c) { return ((struct data*) c->data)->n_out; }

static struct sd_out *as_out(struct sd_out_conv *sd_out_conv)
{
	return &((struct data *) sd_out_conv->data)->sd_out;
}

static struct sd_out_conv sd_out_conv_defaults = {
	sd_declare_tag_vtable(sd_out_conv),
	.as_out = &as_out,
	.get_position = &get_pos,
	.get_length = &get_len,
	.get_n_skip = &get_n_skip,
	.get_receiver = &get_receiver
};

static struct sd_out sd_out_defaults = {
	sd_declare_tag_vtable(sd_out),
	.apply = &apply,
	.get_n_dim = &get_n_dim,
	.get_n_out = &get_n_out
};

struct sd_out_conv *
sd_out_conv_new(uint32_t length, double *kernel, uint32_t n_skip, struct sd_out *receiver)
{
	struct data *data, zero = {0};
	if ((data = sd_malloc(sizeof(struct data))) == NULL 
	 || (*data = zero, receiver == NULL)
	 || (data->kernel = sd_malloc(sizeof(double) * length)) == NULL
	)
	{
		if (data != NULL) sd_free(data);
		sd_err("alloc fail or NULL receiver.");
		return NULL;
	}
	data->receiver = receiver;
	data->sd_out = sd_out_defaults;
	data->sd_out_conv = sd_out_conv_defaults;
	data->sd_out.data = data->sd_out_conv.data = data;
	data->length = length;
	data->n_skip = data->n_to_skip = n_skip;
	memcpy(data->kernel, kernel, sizeof(double) * length);
	return &(data->sd_out_conv);
}

/* vim: foldmethod=marker
 */
