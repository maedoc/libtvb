/* copyright 2016 Apache 2 sddekit authors */

#include "sddekit.h"

/*! Interface for the Excitator system. */
struct sd_sys_exc {

	sd_declare_common_members(sd_sys_exc);

	/*! Get system definition for an Excitator instance. */
	struct sd_sys *(*as_sys)(struct sd_sys_exc*);

	/*! Get the a parameter value. */
	double (*get_a)(struct sd_sys_exc *d);

	/*! Set the a parameter value. */
	void (*set_a)(struct sd_sys_exc *d, double new_a);

	/*! Get the tau parameter value. */
	double (*get_tau)(struct sd_sys_exc *d);

	/*! Set the tau parameter value. */
	void (*set_tau)(struct sd_sys_exc *d, double new_tau);

	/*! Get the D parameter value. */
	double (*get_D)(struct sd_sys_exc *d);

	/*! Set the D parameter value. */
	void (*set_D)(struct sd_sys_exc *d, double new_D);

	/*! Get the k parameter value. */
	double (*get_k)(struct sd_sys_exc *d);

	/*! Set the k parameter value. */
	void (*set_k)(struct sd_sys_exc *d, double new_k);

};

/**
 * Create new instance of the Excitator system.
 */
SD_API struct sd_sys_exc *
sd_sys_exc_new();

