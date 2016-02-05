/* copyright 2016 Apache 2 sddekit authors */

#include "sddekit.h"

typedef struct regmapd {
	//TODO, variables should be more or not, have to understand
	sd_sys sys;
	uint32_t i, *n;  /* n=1 for sum instead of averaging */
} regmapd;

static sd_stat apply(sd_sys *sys, sd_sys_in *in, sd_sys_out *out)
{
	uint32_t l;
	regmapd *d = sys->ptr;
	out->f[0] = 0.0;
	out->g[0] = 0.0;
	in->x[0] = 0.0;
	for (l=0; l<in->nc; l++)
		in->x[0] += in->i[l];
	out->o[0] = in->x[0] / d->n[d->i];
	return SD_OK;
}

static void sys_free(sd_sys *sys) {
	sd_free(sys->ptr); 
}

static	uint32_t sys_ndim(sd_sys *sys) {
	//TODO 
	//return ((regmapd*) sys->ptr)->ndim;
	//regmap dosen't have the required variables, have to understand what are we/regmap doing, so dummy return
	return 0;
}

static	uint32_t sys_ndc(sd_sys *sys)  {
	//TODO
	//return ((regmapd*) sys->ptr)->ndc;
	//regmap dosen't have the required variables, have to understand what are we/regmap doing, so dummy return
	return 0;
}

static	uint32_t sys_nobs(sd_sys *sys) {
	//TODO
	//return ((regmapd*) sys->ptr)->obs;
	//regmap dosen't have the required variables, have to understand what are we/regmap doing, so dummy return
	return 0;
}

static	uint32_t sys_nrpar(sd_sys *sys){
	//TODO
	//return ((regmapd*) sys->ptr)->nrpar;
	//regmap dosen't have the required variables, have to understand what are we/regmap doing, so dummy return
	return 0;
}

static	uint32_t sys_nipar(sd_sys *sys){
	//TODO
	//This seems to work, but have to understand what are we/regmap doing
	return ((regmapd*) sys->ptr)->i;
}

static sd_sys defaults = {
	.ndim = &sys_ndim,
	.ndc = &sys_ndc,
	.nobs = &sys_nobs,
	.nrpar = &sys_nrpar,
	.nipar = &sys_nipar,
	.apply = &apply,
	.free = &sys_free,
	.ptr = NULL
};

sd_sys *
sd_regmap_new()
{
	regmapd z={0}, *d = sd_malloc(sizeof(regmapd));
	if (d == NULL)
	{
		sd_err("alloc regmapd failed.");
		return NULL;
	}
	*d = z;
	d->sys = defaults;
	d->sys.ptr = d;
	return &(d->sys);
}
