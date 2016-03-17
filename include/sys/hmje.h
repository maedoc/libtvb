/* copyright 2016 Apache 2 sddekit authors */

#include "../sddekit.h"

/**
 * Interface for the Hindmarsh-Rose-Jirsa Epileptor model.
 *
 *  Jirsa, V. K.; Stacey, W. C.; Quilichini, P. P.; Ivanov, A. I.; Bernard, C.
 *  On the nature of seizure dynamics. Brain, 2014.
 */
struct sd_sys_hmje
{
	sd_declare_common_members(sd_sys_hmje);

	/*! Get system interface for this instance. */
	struct sd_sys *(*as_sys)(struct sd_sys_hmje *);

#define PAR(n, v)\
	double (*get_##n)(struct sd_sys_hmje *hmje);\
	void   (*set_##n)(struct sd_sys_hmje *hmje, double);
#define LPAR(n, v) PAR(n, v)
#include "hmje_pars.h"
#undef PAR
#undef LPAR

};

SD_API struct sd_sys_hmje *
sd_sys_hmje_new();
