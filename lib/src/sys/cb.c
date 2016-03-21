/* copyright 2016 Apache 2 sddekit authors */

#include "sddekit.h"

struct data
{
	struct sd_sys sd_sys;
    uint32_t n_dim, n_in, n_out, n_rpar, n_ipar;
	void *user_data;
	enum sd_stat (*user_apply)(void*,
        struct sd_sys_in*, struct sd_sys_out*);
};

static uint32_t n_dim (struct sd_sys *sys) 
{
    return ((struct data*) sys->data)->n_dim;
}

static uint32_t n_in(struct sd_sys *sys) 
{
    return ((struct data*) sys->data)->n_in;
}

static uint32_t n_out(struct sd_sys *sys) 
{
    return ((struct data*) sys->data)->n_out;
}

static uint32_t n_rpar(struct sd_sys *sys) 
{
    return ((struct data*) sys->data)->n_rpar;
}

static uint32_t n_ipar(struct sd_sys *sys) 
{
    return ((struct data*) sys->data)->n_ipar;
}

/* obj free n byte copy */
static void
data_free(struct data *data)
{
    sd_free(data);
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
    struct data *copy = sd_malloc(sizeof(struct data));
    if (copy == NULL)
        sd_err("copy sys cb failed.");
    *copy = *data;
    return copy;
}

sd_declare_tag_functions(sd_sys)

static enum sd_stat
apply(struct sd_sys *sys, 
    struct sd_sys_in *in, struct sd_sys_out *out)
{
	struct data *d = sys->data;
	return d->user_apply(d->user_data, in, out);
}

static struct sd_sys sd_sys_defaults = {
    sd_declare_tag_vtable(sd_sys),
	.get_n_dim = &n_dim,
	.get_n_in = &n_in,
	.get_n_out = &n_out,
	.get_n_rpar = &n_rpar,
	.get_n_ipar = &n_ipar,
	.apply = &apply
};

struct sd_sys *
sd_sys_new_cb(uint32_t n_dim, uint32_t n_in, uint32_t n_out, 
	uint32_t n_rpar, uint32_t n_ipar,
	void *user_data,
    enum sd_stat (*user_apply)(void *, struct sd_sys_in*, struct sd_sys_out*))
{
	struct data *data;
    if ((data = sd_malloc(sizeof(struct data))) == NULL)
	{
		sd_err("alloc sys cb failed.");
		return NULL;
	}
	data->n_dim = n_dim;
	data->n_in = n_in;
	data->n_out = n_out;
	data->n_rpar = n_rpar;
	data->n_ipar = n_ipar;
	data->sd_sys = sd_sys_defaults;
	data->sd_sys.data = data;
	data->user_data = user_data;
	data->user_apply = user_apply;
	return &data->sd_sys;
}
