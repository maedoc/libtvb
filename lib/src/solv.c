/* copyright 2016 Apache 2 libtvb authors */

#include "libtvb.h"
#include <time.h>

struct data
{
	enum tvb_stat cont;
	struct tvb_sch *sch;
	struct tvb_out *out;
	struct tvb_sol sol;
};

static void tvb_sol_free(struct tvb_sol *sol)
{
	tvb_free(sol->data);
}

static uint32_t tvb_sol_n_byte(struct tvb_sol *sol)
{
	struct data *data = sol->data;
	uint32_t n_byte = sizeof(struct data);
	n_byte += data->sch->n_byte(data->sch);
	n_byte += data->out->n_byte(data->out);
	return n_byte;
}

static struct tvb_sol *tvb_sol_copy(struct tvb_sol *sol)
{
    struct data *data = sol->data;
    struct tvb_sch *sch = data->sch;
    return tvb_sol_new_default(
        sch->get_time(sch),
        sch->get_state(sch),
        sch,
        data->out
    );
}

static enum tvb_stat cont(struct tvb_sol *sol)
{
	clock_t tic = clock();
	struct data *data = sol->data;
	struct tvb_out *out = data->out;
    struct tvb_sch *sch = data->sch;
	data->cont = TVB_CONT;
	do {
		if (sch->apply(sch)!=TVB_OK)
		{
			tvb_err("scheme application failed.");
			return TVB_ERR;
		}
        struct tvb_out_sample sample = sch->sample(sch);
		data->cont = out->apply(out, &sample);
    } while (data->cont == TVB_CONT);
	clock_t toc = clock();
	double walltime = (double) (toc - tic) / CLOCKS_PER_SEC;
	tvb_log_debug("continuation required %.3f s walltime", walltime);
	return TVB_OK;
}

struct tvb_sch *get_scheme(struct tvb_sol *sol)
{
    struct data *data = sol->data;
    return data->sch;    
}

struct tvb_out *get_out(struct tvb_sol *sol)
{
    struct data *data = sol->data;
    return data->out;    
}

double get_time(struct tvb_sol *sol)
{
    struct data *data = sol->data;
    return data->sch->get_time(data->sch);
}

static struct tvb_sol tvb_sol_defaults = {
    tvb_declare_tag_vtable(tvb_sol),
    .get_scheme = &get_scheme,
    .get_out = &get_out,
    .cont = &cont,
    .get_time = &get_time
};

struct tvb_sol *
tvb_sol_new_default(double init_time, double *init_state,
		   struct tvb_sch *sch, struct tvb_out *out)
{
	struct data *data;
	if ((data = tvb_malloc(sizeof(struct data))) == NULL)
	{
		tvb_err("failed to alloc solver");
		return NULL;
	}
    data->cont = TVB_CONT;
    data->out = out;
    data->sch = sch;
    data->sol = tvb_sol_defaults;
    data->sol.data = data;
    return &data->sol;
}
