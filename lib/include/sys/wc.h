/* copyright 2016 Apache 2 libtvb authors */

#include "../libtvb.h"

/*! Interface for the Reduced Wong-Wang model. */
struct tvb_sys_wc
{
	tvb_declare_common_members(tvb_sys_wc);

	/*! Get system interface for this instance. */
	struct tvb_sys *(*as_sys)(struct tvb_sys_wc *wc);

#define PAR(n, v)\
	double (*get_##n)(struct tvb_sys_wc *wc);\
	void   (*set_##n)(struct tvb_sys_wc *wc, double);
#define LPAR(n, v) PAR(n, v)
#include "wc_pars.h"
#undef PAR
#undef LPAR

};

TVB_API struct tvb_sys_wc *
tvb_sys_wc_new();
