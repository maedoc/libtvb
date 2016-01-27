/* copyright 2016 Apache 2 sddekit authors */

#include "sddekit.h"

typedef struct { 
	char *name_s, *f_ex_s, *g_ex_s; 
	te_expr *f_ex, *g_ex;
} svar;

void free_svar(svar *s)
{
	sd_free(name_s);
	sd_free(f_ex_s);
	sd_free(g_ex_s);
	te_free(f_ex);
	te_free(g_ex);
	sd_free(s);
}

typedef struct { 
	char *name, *ex_s; 
	te_expr *ex;
} ivar;

void free_ivar(ivar *s)
{
	sd_free(name);
	sd_free(ex_s);
	te_free(ex);
	sd_free(s);
}

typedef struct {
    char *ex_s;
	uint32_t index; 
	te_expr *ex;
} ovar;

void free_ovar(ovar *s)
{
	sd_free(ex_s);
	te_free(ex);
	sd_free(s);
}

typedef struct data {
	sd_sys sys;
	sd_sys_ex ex;
	uint32_t ndim, ndc, nobs, nrpar, nipar;
	uint32_t ns, ni, no;
	sd_sys_in in;
	sd_sys_in out;
	svar *svars;
	ivar *ivars;
	ovar *ovars;
} data;

static uint32_t ndim(sd_sys *sys) { return ((data*) sys->ptr)->ndim; }
static uint32_t ndc(sd_sys *sys) { return ((data*) sys->ptr)->ndc; }
static uint32_t nobs(sd_sys *sys) { return ((data*) sys->ptr)->nobs; }
static uint32_t nrpar(sd_sys *sys) { return ((data*) sys->ptr)->nrpar; }
static uint32_t nipar(sd_sys *sys) { return ((data*) sys->ptr)->nipar; }

static void cb_free(sd_sys *sys)
{
	uint32_t i;
	data *d = sys->ptr;
	for (i=0; i<d->ns; i++) free_svar(d->svars[i]); sd_free(d->svars);
	for (i=0; i<d->ni; i++) free_ivar(d->ivars[i]); sd_free(d->ivars);
	for (i=0; i<d->no; i++) free_ovar(d->ovars[i]); sd_free(d->ovars);
	/* TODO handle d->{in,out} */
	sd_free(d);
}

static sd_stat apply(sd_sys *sys, sd_sys_in *in, sd_sys_out *out)
{
	data *d = sys->ptr;
	/* Will need to copy data from in into an in which is stable
	 * memory location because tinyex doesn't expect pointers to
	 * move. This is an acceptable inefficiency, since, well, the
	 * expressions should be written in C.
	 */
}

static sd_sys defaults = {
	.ndim = &ndim,
	.ndc = &ndc,
	.nobs = &nobs,
	.nrpar = &nrpar,
	.nipar = &nipar,
	.apply = &apply,
	.free = &cb_free,
	.ptr = NULL
};

sd_sys_ex *
sd_sys_new_ex()
{
	data *d;
        if ((d = sd_malloc(sizeof(data))) == NULL)
	{
		sd_err("alloc sys cb failed.");
		return NULL;
	}
	d->ndim = ndim;
	d->ndc = ndc;
	d->nobs = nobs;
	d->nrpar = nrpar;
	d->nipar = nipar;
	d->sys = defaults;
	d->sys.ptr = d;
	/* TODO alloc expr stuff */
	return &(d->ex);
}
