/* copyright 2016 Apache 2 sddekit authors */

#include "sddekit.h"
#include <time.h>

struct data
{
	enum sd_stat cont;
	struct sd_sch *sch;
	struct sd_out *out;
	struct sd_sol sol;
};

static void sd_sol_free(struct sd_sol *sol)
{
	sd_free(sol->data);
}

static uint32_t sd_sol_n_byte(struct sd_sol *sol)
{
	struct data *data = sol->data;
	uint32_t n_byte = sizeof(struct data);
	n_byte += data->sch->n_byte(data->sch);
	n_byte += data->out->n_byte(data->out);
	return n_byte;
}

static struct sd_sol *sd_sol_copy(struct sd_sol *sol)
{
    struct data *data = sol->data;
    struct sd_sch *sch = data->sch;
    return sd_sol_new_default(
        sch->get_time(sch),
        sch->get_state(sch),
        sch,
        data->out
    );
}

static enum sd_stat cont(struct sd_sol *sol)
{
	clock_t tic = clock();
	struct data *data = sol->data;
	struct sd_out *out = data->out;
    struct sd_sch *sch = data->sch;
	data->cont = SD_CONT;
	do {
		if (sch->apply(sch)!=SD_OK)
		{
			sd_err("scheme application failed.");
			return SD_ERR;
		}
		data->cont = out->apply(out, sch->sample(sch));
    } while (data->cont == SD_CONT);
	clock_t toc = clock();
	double walltime = (double) (toc - tic) / CLOCKS_PER_SEC;
	sd_log_debug("continuation required %.3f s walltime", walltime);
	return SD_OK;
}

struct sd_sch *get_scheme(struct sd_sol *sol)
{
    struct data *data = sol->data;
    return data->sch;    
}

struct sd_out *get_out(struct sd_sol *sol)
{
    struct data *data = sol->data;
    return data->out;    
}

double get_time(struct sd_sol *sol)
{
    struct data *data = sol->data;
    return data->sch->get_time(data->sch);
}

static struct sd_sol sd_sol_defaults = {
    sd_declare_tag_vtable(sd_sol),
    .get_scheme = &get_scheme,
    .get_out = &get_out,
    .cont = &cont,
    .get_time = &get_time
};

struct sd_sol *
sd_sol_new_default(double init_time, double *init_state,
		   struct sd_sch *sch, struct sd_out *out)
{
	struct data *data;
	if ((data = sd_malloc(sizeof(struct data))) == NULL)
	{
		sd_err("failed to alloc solver");
		return NULL;
	}
    data->cont = SD_CONT;
    data->out = out;
    data->sch = sch;
    data->sol = sd_sol_defaults;
    data->sol.data = data;
    return &data->sol;
}
