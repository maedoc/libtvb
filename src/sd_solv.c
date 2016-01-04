/* copyright 2016 Apache 2 sddekit authors */

#include "sddekit.h"

typedef struct sol_data {
	uint32_t nx, nca, nce;
	sd_stat cont;
	sd_sys *sys;
	sd_sch *sch;
	sd_out *out;
	sd_hfill *hf;
	sd_hist *hist; /* nd==nca, ci, cd */
	sd_rng *rng; /* TODO mv to scheme? */
	double t, dt, *x, *c, *x0;
} sol_data;

static void sol_free(sd_sol *sol)
{
	sol_data *s = sol->ptr;
	s->rng->free(s->rng);
	sd_free(s->x);
	sd_free(s->x0);
	if (s->c != NULL) {
		sd_free(s->c);
		s->hist->free(s->hist);
	}
	sd_free(s);
	sd_free(sol);
}

static sd_stat cont(sd_sol *sol)
{
	sol_data *s = sol->ptr;
	sd_hist *h;

	h = s->nca ? s->hist : NULL;
	s->cont = SD_CONT;
	do {
		if (s->sch->apply(s->sch, h, s->rng, s->sys, s->t, s->dt, s->nx, s->x, s->nce, s->c)!=SD_OK) 
		{
			sd_err("scheme failure.");
			return SD_ERR;
		}
		s->t += s->dt;
		s->cont = s->out->apply(s->out, s->t, s->nx, s->x, s->nce, s->c);
	} while (s->cont == SD_CONT);

	return SD_OK;
}

static uint32_t  get_nx(sd_sol *s) { return ((sol_data*)s->ptr)->nx; }
static uint32_t get_nce(sd_sol *s) { return ((sol_data*)s->ptr)->nce; }
static uint32_t get_nca(sd_sol *s) { return ((sol_data*)s->ptr)->nca; }

static  sd_hist *get_hist(sd_sol *s) { return ((sol_data*)s->ptr)->hist; }
static sd_rng  *get_rng (sd_sol *s) { return ((sol_data*)s->ptr)->rng ; }

static double *get_c(sd_sol *s) { return ((sol_data*)s->ptr)->c; }
static double *get_x(sd_sol *s) { return ((sol_data*)s->ptr)->x; }
static double  get_t(sd_sol *s) { return ((sol_data*)s->ptr)->t; }

static sd_sol sol_default = {
	.ptr = NULL,
	.free = &sol_free,
	.cont = &cont,
	.get_nx = &get_nx,
	.get_nce = &get_nce,
	.get_nca = &get_nca,
	.get_hist = &get_hist,
	.get_rng  = &get_rng ,
	.get_c = &get_c,
	.get_x = &get_x,
	.get_t = &get_t,
};

sd_sol *
sd_sol_new_default(
	sd_sys *sys, sd_sch *scheme, sd_out *out, sd_hfill *hf,
	uint32_t seed, uint32_t nx, double * restrict x0, uint32_t nce,
	uint32_t nca, uint32_t * restrict vi, double * restrict vd,
	double t0, double dt
	)
{
	char *errmsg;
	sd_sol *sol = NULL;
	/* error handling */
#define FAILIF(cond, msg)\
       	if (cond) { \
		errmsg = msg;\
		goto uhoh;\
	}
	/* allocate & zero sol interface & data */
	{
		sol_data zdat = { 0 };
		FAILIF((sol = sd_malloc(sizeof(sd_sol)))==NULL, "allocating solver failed.");
		*sol = sol_default;
		FAILIF((sol->ptr = sd_malloc(sizeof(sol_data)))==NULL, "allocating solver data failed.");
		*((sol_data*) sol->ptr) = zdat;
		/* TODO fill interface table */
	}
	FAILIF(sys == NULL || scheme == NULL || hf == NULL || out == NULL,
		"cannot initialize solver with NULL system, scheme, out or history function.")
	/* copy arguments */
	{
		sol_data *s = (sol_data*)sol->ptr;
		s->nx = nx;
		s->nce = nce;
		s->nca = nca;
		s->cont = 1;
		s->sys = sys;
		s->sch = scheme;
		s->out = out;
		s->hf = hf;
	}
	/* setup coupling */
	{
		sol_data *s = (sol_data*)sol->ptr;
		if (nca > 0 && vi!=NULL && vd!=NULL) 
			{
				size_t cn;
				FAILIF((s->hist = sd_hist_new_default(nca, vi, vd, t0, dt)) == NULL, "failed to create history.")
				FAILIF(s->hist->fill(s->hist, hf)!=SD_OK, "history fill failed.")
				/* s->c big enough to accomate aff or eff */
				cn = nca > nce ? nca : nce;
				FAILIF((s->c = sd_malloc(sizeof(double) * cn)) == NULL, "alloc coupling array failed.")
		} else {
			s->nca = 0;
			s->c = NULL;
		}
	}
	/* initial conditions */
	{
		sol_data *s = (sol_data*)sol->ptr;
		FAILIF((s->rng = sd_rng_new_default())==NULL,
			"couldn't create a new rng");
		s->rng->seed(s->rng, seed);
		FAILIF((s->x = sd_malloc (sizeof(double) * nx))==NULL, 
				"failed to alloc solver x")
		FAILIF((s->x0 = sd_malloc (sizeof(double) * nx))==NULL, 
			"failed to alloc solver x0")
		memcpy(s->x, x0, sizeof(double) * s->nx);
		memcpy(s->x0, x0, sizeof(double) * s->nx);
		s->t = t0;
		s->dt = dt;
	}
	return sol;
uhoh:
	/* clean up */
	{
		if (sol != NULL && sol->ptr != NULL)
		{
			sol_data *s = sol->ptr;
			if (s->x!=NULL) sd_free(s->x);
			if (s->x0!=NULL) sd_free(s->x0);
			if (s->c!=NULL) sd_free(s->c);
			if (s->hist!=NULL) s->hist->free(s->hist);
		}
		if (sol != NULL)
			sd_free(sol);
	}
	sd_err(errmsg);
	return NULL;
}
