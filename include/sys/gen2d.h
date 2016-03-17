/* copyright 2016 Apache 2 sddekit authors */

#include "../sddekit.h"

/*! Interface for the generic 2D oscillator system. */
struct sd_sys_gen2d
{
	sd_declare_common_members(sd_sys_gen2d);

	/**
	 * Get system interface for this oscillator.
	 */
	struct sd_sys *(*as_sys)(struct sd_sys_gen2d *gen2d);

#define PAR(n, v) \
	double (*get_##n)(struct sd_sys_gen2d *gen2d);\
	void (*set_##n)(struct sd_sys_gen2d *gen2d, double);
#define LASTPAR(n, v) PAR(n, v)
#include "gen2d_pars.h"
#undef PAR
#undef LASTPAR
};

/**
 * Create new instance of the Excitator system.
 */
SD_API struct sd_sys_gen2d *
sd_sys_gen2d_new();
