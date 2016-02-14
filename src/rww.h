/* copyright 2016 Apache 2 sddekit authors */

#include "sddekit.h"

/**
 * Interface for the Reduced Wong-Wang model.
 */
struct sd_sys_rww
{
	void *ptr;

	/**
	 * Free memory allocated for this instance.
	 */
	void (*free)(struct sd_sys_rww *);

	/**
	 * Get system interface for this instance.
	 */
	struct sd_sys *(*sys)(struct sd_sys_rww *);

#define PAR(n, v)\
	double (*get_##n)(struct sd_sys_rww *);\
	void   (*set_##n)(struct sd_sys_rww *, double);
#define LPAR(n, v) PAR(n, v)
#include "rww_pars.h"
#undef PAR
#undef LPAR

};
