/* copyright 2016 Apache 2 libtvb authors */

#include "../libtvb.h"

/**
 * Interface to time-stepping schemes.
 *
 * \note Schemes create internal data structures which are cleaned
 * up during a call to the free method, however, the history, 
 * rng and sys structures are considered external and will not
 * be freed when the scheme is freed.
 */
struct tvb_sch
{
	tvb_declare_common_members(tvb_sch);

	/*! Get the length of the state vector of this scheme. */
	uint32_t (*get_n_dim)(struct tvb_sch *sch);

	/*! Get the length of the input vector of this scheme. */
	uint32_t (*get_n_in)(struct tvb_sch *sch);

	/*! Get the length of the output vector of this scheme. */
	uint32_t (*get_n_out)(struct tvb_sch *sch);

	/*! Get the time step of this scheme. */
	double (*get_dt)(struct tvb_sch *sch);

	/*! Get current time. */
	double (*get_time)(struct tvb_sch *sch);

	/*! Get current state vector. */
	double *(*get_state)(struct tvb_sch *sch);

	/*! Get current input vector. */
	double *(*get_input)(struct tvb_sch *sch);

	/*! Get current output vector. */
	double *(*get_output)(struct tvb_sch *sch);
    
    /*! Sample current state. */
    struct tvb_out_sample (*sample)(struct tvb_sch *sch);

	/*! Get this scheme's hist instance. */
	struct tvb_hist *(*get_hist)(struct tvb_sch *);

	/*! Get this scheme's rng instance. */
	struct tvb_rng *(*get_rng)(struct tvb_sch *);

	/*! Get this scheme's sys instance. */
	struct tvb_sys *(*get_sys)(struct tvb_sch *);

	/*! Apply scheme. */
	enum tvb_stat (*apply)(struct tvb_sch *scheme);
};
