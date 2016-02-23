/* copyright 2016 Apache 2 sddekit authors */

#ifndef SD_SYS_HMJE_H
#define SD_SYS_HMJE_H

#include "sddekit.h"

/**
 * Interface for the Hindmarsh-Rose-Jirsa Epileptor model.
 *
 *  Jirsa, V. K.; Stacey, W. C.; Quilichini, P. P.; Ivanov, A. I.; Bernard, C.
 *  On the nature of seizure dynamics. Brain, 2014.
 */
struct sd_sys_hmje
{
	void *ptr;

	/**
	 * Free memory allocated for this instance.
	 */
	void (*free)(struct sd_sys_hmje *);

	/**
	 * Get system interface for this instance.
	 */
	struct sd_sys *(*sys)(struct sd_sys_hmje *);

#define PAR(n, v)\
	double (*get_##n)(struct sd_sys_hmje *);\
	void   (*set_##n)(struct sd_sys_hmje *, double);
#define LPAR(n, v) PAR(n, v)
#include "sys_hmje_pars.h"
#undef PAR
#undef LPAR

};

SD_API struct sd_sys_hmje *
sd_sys_hmje_new();

#endif
