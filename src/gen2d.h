/* copyright 2016 Apache 2 sddekit authors */

#include "sddekit.h"

/* Forward declare interface type for explicit use in signatures. */
typedef struct sd_sys_gen2d sd_sys_gen2d;

/**
 * Interface for the generic 2D oscillator system.
 */
struct sd_sys_gen2d {

	void *ptr;

	/**
	 * Get system interface for this oscillator.
	 */
	sd_sys *(*sys)(sd_sys_gen2d*);

	/**
	 * Free memory allocated for this oscillator.
	 */
	void (*free)(sd_sys_gen2d *);

#define PAR(n, v) \
	double (*get_##n)(sd_sys_gen2d *);\
	void (*set_##n)(sd_sys_gen2d *, double);
#define LASTPAR(n, v) PAR(n, v)
#include "gen2d_pars.h"
#undef PAR
#undef LASTPAR

};

/**
 * Create new instance of the Excitator system.
 */
SD_API sd_sys_gen2d *
sd_sys_gen2d_new();
