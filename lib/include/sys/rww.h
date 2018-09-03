/* copyright 2016 Apache 2 libtvb authors */

#include "../libtvb.h"

/*! Interface for the Reduced Wong-Wang model. */
struct tvb_sys_rww
{
	tvb_declare_common_members(tvb_sys_rww);

	/*! Get system interface for this instance. */
	struct tvb_sys *(*as_sys)(struct tvb_sys_rww *rww);

#define PAR(n, v)\
	double (*get_##n)(struct tvb_sys_rww *rww);\
	void   (*set_##n)(struct tvb_sys_rww *rww, double);
#define LPAR(n, v) PAR(n, v)
#include "rww_pars.h"
#undef PAR
#undef LPAR

};

TVB_API struct tvb_sys_rww *
tvb_sys_rww_new();
