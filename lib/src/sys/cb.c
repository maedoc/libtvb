/* copyright 2016 Apache 2 libtvb authors */

#include "libtvb.h"

struct data
{
	struct tvb_sys tvb_sys;
    uint32_t n_dim, n_in, n_out, n_rpar, n_ipar;
	void *user_data;
	enum tvb_stat (*user_apply)(void*,
        struct tvb_sys_in*, struct tvb_sys_out*);
};

static uint32_t n_dim (struct tvb_sys *sys) 
{
    return ((struct data*) sys->data)->n_dim;
}

static uint32_t n_in(struct tvb_sys *sys) 
{
    return ((struct data*) sys->data)->n_in;
}

static uint32_t n_out(struct tvb_sys *sys) 
{
    return ((struct data*) sys->data)->n_out;
}

static uint32_t n_rpar(struct tvb_sys *sys) 
{
    return ((struct data*) sys->data)->n_rpar;
}

static uint32_t n_ipar(struct tvb_sys *sys) 
{
    return ((struct data*) sys->data)->n_ipar;
}

/* obj free n byte copy */
static void
data_free(struct data *data)
{
    tvb_free(data);
}

static uint32_t
data_n_byte(struct data *data)
{
    (void) data;
    return sizeof(struct data);    
}

static struct data * 
data_copy(struct data *data)
{
    struct data *copy = tvb_malloc(sizeof(struct data));
    if (copy == NULL)
        tvb_err("copy sys cb failed.");
    *copy = *data;
    return copy;
}

tvb_declare_tag_functions(tvb_sys)

static enum tvb_stat
apply(struct tvb_sys *sys, 
    struct tvb_sys_in *in, struct tvb_sys_out *out)
{
	struct data *d = sys->data;
	return d->user_apply(d->user_data, in, out);
}

static struct tvb_sys tvb_sys_defaults = {
    tvb_declare_tag_vtable(tvb_sys),
	.get_n_dim = &n_dim,
	.get_n_in = &n_in,
	.get_n_out = &n_out,
	.get_n_rpar = &n_rpar,
	.get_n_ipar = &n_ipar,
	.apply = &apply
};

struct tvb_sys *
tvb_sys_new_cb(uint32_t n_dim, uint32_t n_in, uint32_t n_out, 
	uint32_t n_rpar, uint32_t n_ipar,
	void *user_data,
    enum tvb_stat (*user_apply)(void *, struct tvb_sys_in*, struct tvb_sys_out*))
{
	struct data *data;
    if ((data = tvb_malloc(sizeof(struct data))) == NULL)
	{
		tvb_err("alloc sys cb failed.");
		return NULL;
	}
	data->n_dim = n_dim;
	data->n_in = n_in;
	data->n_out = n_out;
	data->n_rpar = n_rpar;
	data->n_ipar = n_ipar;
	data->tvb_sys = tvb_sys_defaults;
	data->tvb_sys.data = data;
	data->user_data = user_data;
	data->user_apply = user_apply;
	return &data->tvb_sys;
}
