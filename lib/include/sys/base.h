/* copyright 2016 Apache 2 sddekit authors */

#include "../sddekit.h"

/*! Input argument structure for a system definition. */
struct sd_sys_in
{ 
	uint32_t id, n_dim, n_in, n_out;
	double time, *state, *input; 
	struct sd_hist *hist;
	struct sd_rng *rng;
};

/*! Output argument structure for a system definition. */
struct sd_sys_out
{ 
	double *drift, *diffusion, *output; 
};

/*! Interface for a system definition. */
struct sd_sys
{

	sd_declare_common_members(sd_sys);

	/*! Get the dimension of the system's state space. */
	uint32_t (*get_n_dim)(struct sd_sys *sys);

	/*! Get the number of delayed coupling terms used in the system definition. */
	uint32_t (*get_n_in)(struct sd_sys *sys);

	/*! Get the number of observable terms defined by system. */
	uint32_t (*get_n_out)(struct sd_sys *sys);

	/*! Get the number of real valued parameters used by system. */
	uint32_t (*get_n_rpar)(struct sd_sys *sys);

	/*! Get the number of integer valued parameters used by system. */
	uint32_t (*get_n_ipar)(struct sd_sys *sys);

	/**
	 * Apply system definition to state and input, calculating drift,
	 * diffusion and observable terms.
	 *
	 * \return SD_OK if calculation succeeds, SD_ERR if error occurs.
	 */
	enum sd_stat (*apply)(struct sd_sys *sys, 
		struct sd_sys_in *in, struct sd_sys_out *out);
};

/*! Create new system based on user provided data & callback. */
SD_API struct sd_sys *
sd_sys_new_cb(
	uint32_t n_dim, uint32_t n_in, uint32_t n_out, 
	uint32_t n_rpar, uint32_t n_ipar,
	void *user_data,
	enum sd_stat (*user_apply)(void *, struct sd_sys_in*, struct sd_sys_out*));
    
/*! Create sys which averages its inputs. */
SD_API struct sd_sys *
sd_sys_new_mean(uint32_t n_in);