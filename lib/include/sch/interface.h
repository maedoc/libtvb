/* copyright 2016 Apache 2 sddekit authors */

#include "../sddekit.h"

/**
 * Interface to time-stepping schemes.
 *
 * \note Schemes create internal data structures which are cleaned
 * up during a call to the free method, however, the history, 
 * rng and sys structures are considered external and will not
 * be freed when the scheme is freed.
 */
struct sd_sch
{
	sd_declare_common_members(sd_sch);

	/*! Get the length of the state vector of this scheme. */
	uint32_t (*get_n_dim)(struct sd_sch *sch);

	/*! Get the length of the input vector of this scheme. */
	uint32_t (*get_n_in)(struct sd_sch *sch);

	/*! Get the length of the output vector of this scheme. */
	uint32_t (*get_n_out)(struct sd_sch *sch);

	/*! Get the time step of this scheme. */
	double (*get_dt)(struct sd_sch *sch);

	/*! Get current time. */
	double (*get_time)(struct sd_sch *sch);

	/*! Get current state vector. */
	double *(*get_state)(struct sd_sch *sch);

	/*! Get current input vector. */
	double *(*get_input)(struct sd_sch *sch);

	/*! Get current output vector. */
	double *(*get_output)(struct sd_sch *sch);
    
    /*! Sample current state. */
    struct sd_out_sample (*sample)(struct sd_sch *sch);

	/*! Get this scheme's hist instance. */
	struct sd_hist *(*get_hist)(struct sd_sch *);

	/*! Get this scheme's rng instance. */
	struct sd_rng *(*get_rng)(struct sd_sch *);

	/*! Get this scheme's sys instance. */
	struct sd_sys *(*get_sys)(struct sd_sch *);

	/*! Apply scheme. */
	enum sd_stat (*apply)(struct sd_sch *scheme);
};
