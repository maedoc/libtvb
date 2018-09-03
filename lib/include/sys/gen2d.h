/* copyright 2016 Apache 2 libtvb authors */

#include "../libtvb.h"

/*! Interface for the generic 2D oscillator system. */
struct tvb_sys_gen2d
{
	tvb_declare_common_members(tvb_sys_gen2d);

	/**
	 * Get system interface for this oscillator.
	 */
	struct tvb_sys *(*as_sys)(struct tvb_sys_gen2d *gen2d);

#define PAR(n, v) \
	double (*get_##n)(struct tvb_sys_gen2d *gen2d);\
	void (*set_##n)(struct tvb_sys_gen2d *gen2d, double);
#define LASTPAR(n, v) PAR(n, v)
#include "gen2d_pars.h"
#undef PAR
#undef LASTPAR
};

/**
 * Create new instance of the Excitator system.
 */
TVB_API struct tvb_sys_gen2d *
tvb_sys_gen2d_new();
