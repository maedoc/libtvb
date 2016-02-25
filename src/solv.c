/* copyright 2016 Apache 2 sddekit authors */

#include "sddekit.h"
#include <time.h>

struct sol_data {
	uint32_t nx, nc;
	enum sd_stat cont;
	struct sd_sch *sch;
	struct sd_out *out;
	double t, *x, *c, *x0;
	struct sd_sol sol;
};

typedef struct sol_data sol_data;

static void sol_free(struct sd_sol *sol)
{
	sol_data *s = sol->ptr;
	sd_free(s->x);
	sd_free(s->x0);
	sd_free(s->c);
	sd_free(s);
	sd_free(sol);
}

static enum sd_stat cont(struct sd_sol *sol)
{
	clock_t tic = clock();
	struct sol_data *s = sol->ptr;
	s->cont = SD_CONT;
	do {
		if (s->sch->apply(s->sch, &s->t, s->x, s->c)!=SD_OK) 
		{
			sd_err("scheme application failed.");
			return SD_ERR;
		}
		s->cont = s->out->apply(s->out, s->t, s->nx, s->x, s->nc, s->c);
	} while (s->cont == SD_CONT);
	clock_t toc = clock();
	double walltime = (double) (toc - tic) / CLOCKS_PER_SEC;
	sd_log_debug("continuation required %.3f s walltime", walltime);
	return SD_OK;
}

static uint32_t  get_nx(sd_sol *s) { return ((sol_data*)s->ptr)->nx; }
static uint32_t get_nc(sd_sol *s) { return ((sol_data*)s->ptr)->nc; }
static double *get_c(sd_sol *s) { return ((sol_data*)s->ptr)->c; }
static double *get_x(sd_sol *s) { return ((sol_data*)s->ptr)->x; }
static double  get_t(sd_sol *s) { return ((sol_data*)s->ptr)->t; }

static sd_sol sol_default = {
	.ptr = NULL,
	.free = &sol_free,
	.cont = &cont,
	.get_nx = &get_nx,
	.get_nc = &get_nc,
	.get_c = &get_c,
	.get_x = &get_x,
	.get_t = &get_t,
};

sd_sol *
sd_sol_new_default(
	double t0,
	uint32_t nx, uint32_t nc, /* TODO should these from scheme->sys->ndim */
	struct sd_sch *scheme,
	struct sd_out *out,
	double * x0
)
{
	sol_data *s;
	if ((s = sd_malloc(sizeof(struct sol_data))) == NULL
	 || (s->x = sd_malloc(sizeof(double) * nx)) == NULL

	 /* TODO nc v. ndc v nobs not the same, schemes are aliasing c as i & o */
	 || (s->c = sd_malloc(sizeof(double) * nc)) == NULL
	 || (s->x0 = sd_malloc(sizeof(double) * nx)) == NULL
	)
	{
		if (s->x != NULL)
			sd_free(s->x);
		if (s->c != NULL)
			sd_free(s->c);
		if (s != NULL)
			sd_free(s);
		sd_err("failed to alloc solver");
		return NULL;
	}
	{
		sol_data z = { 0 };
		*s = z;
	}
	s->sol = sol_default;
	s->nx = nx;
	s->nc = nc;
	s->cont = 1;
	s->sch = scheme;
	s->out = out;
	memcpy(s->x, x0, sizeof(double) * s->nx);
	memcpy(s->x0, x0, sizeof(double) * s->nx);
	for (uint32_t i=0; i<nc; i++)
		s->c[i] = 0.0;
	s->t = t0;
	return &(s->sol);
}
