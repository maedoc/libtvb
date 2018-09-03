/* copyright 2016 Apache 2 libtvb authors */

#include "../libtvb.h"

/*! Input argument structure for a system definition. */
struct tvb_sys_in
{ 
	uint32_t id, n_dim, n_in, n_out;
	double time, *state, *input; 
	struct tvb_hist *hist;
	struct tvb_rng *rng;
};

/*! Output argument structure for a system definition. */
struct tvb_sys_out
{ 
	double *drift, *diffusion, *output; 
};

/*! Interface for a system definition. */
struct tvb_sys
{

	tvb_declare_common_members(tvb_sys);

	/*! Get the dimension of the system's state space. */
	uint32_t (*get_n_dim)(struct tvb_sys *sys);

	/*! Get the number of delayed coupling terms used in the system definition. */
	uint32_t (*get_n_in)(struct tvb_sys *sys);

	/*! Get the number of observable terms defined by system. */
	uint32_t (*get_n_out)(struct tvb_sys *sys);

	/*! Get the number of real valued parameters used by system. */
	uint32_t (*get_n_rpar)(struct tvb_sys *sys);

	/*! Get the number of integer valued parameters used by system. */
	uint32_t (*get_n_ipar)(struct tvb_sys *sys);

	/**
	 * Apply system definition to state and input, calculating drift,
	 * diffusion and observable terms.
	 *
	 * \return TVB_OK if calculation succeeds, TVB_ERR if error occurs.
	 */
	enum tvb_stat (*apply)(struct tvb_sys *sys, 
		struct tvb_sys_in *in, struct tvb_sys_out *out);
};

/*! Create new system based on user provided data & callback. */
TVB_API struct tvb_sys *
tvb_sys_new_cb(
	uint32_t n_dim, uint32_t n_in, uint32_t n_out, 
	uint32_t n_rpar, uint32_t n_ipar,
	void *user_data,
	enum tvb_stat (*user_apply)(void *, struct tvb_sys_in*, struct tvb_sys_out*));
    
/*! Create sys which averages its inputs. */
TVB_API struct tvb_sys *
tvb_sys_new_mean(uint32_t n_in);