/* copyright 2016 Apache 2 sddekit authors */

#include "../sddekit.h"

/*! Interface for the Reduced Wong-Wang model. */
struct sd_sys_wc
{
	sd_declare_common_members(sd_sys_wc);

	/*! Get system interface for this instance. */
	struct sd_sys *(*as_sys)(struct sd_sys_wc *wc);

#define PAR(n, v)\
	double (*get_##n)(struct sd_sys_wc *wc);\
	void   (*set_##n)(struct sd_sys_wc *wc, double);
#define LPAR(n, v) PAR(n, v)
#include "wc_pars.h"
#undef PAR
#undef LPAR

};

SD_API struct sd_sys_wc *
sd_sys_wc_new();
