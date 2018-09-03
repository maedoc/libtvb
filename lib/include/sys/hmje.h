/* copyright 2016 Apache 2 libtvb authors */

#include "../libtvb.h"

/**
 * Interface for the Hindmarsh-Rose-Jirsa Epileptor model.
 *
 *  Jirsa, V. K.; Stacey, W. C.; Quilichini, P. P.; Ivanov, A. I.; Bernard, C.
 *  On the nature of seizure dynamics. Brain, 2014.
 */
struct tvb_sys_hmje
{
	tvb_declare_common_members(tvb_sys_hmje);

	/*! Get system interface for this instance. */
	struct tvb_sys *(*as_sys)(struct tvb_sys_hmje *);

#define PAR(n, v)\
	double (*get_##n)(struct tvb_sys_hmje *hmje);\
	void   (*set_##n)(struct tvb_sys_hmje *hmje, double);
#define LPAR(n, v) PAR(n, v)
#include "hmje_pars.h"
#undef PAR
#undef LPAR

};

TVB_API struct tvb_sys_hmje *
tvb_sys_hmje_new();
