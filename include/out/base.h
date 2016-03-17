/* copyright 2016 Apache 2 sddekit authors */

#include "../sddekit.h"

/**
 * Interface for outputs or monitors of state & output data.
 */
struct sd_out
{
	sd_declare_common_members(sd_out);
    
	/*! Get length of state vector handled by this output. */
	uint32_t (*get_n_dim)(struct sd_out *out);
    
	/*! Get length of output vector handled by this output. */
	uint32_t (*get_n_out)(struct sd_out *out);
    
	/**
	 * Apply output to current state.
	 * \param data user data for output function such as simulation length.
	 * \return SD_OK if the solver should continue, SD_ERR if 
	 * error occurred, and SD_STOP if solution should stop.
	 */
	enum sd_stat (*apply)(struct sd_out *out, struct sd_out_sample *sample);
};

/**
 * Create new out based on user provided data & callback.
 *
 * \note The n_byte & copy methods cannot be aware of the contents of
 * user_data and so operate superficially.
 */
SD_API struct sd_out *
sd_out_new_cb(void *user_data,
	enum sd_stat (*user_apply)(
		void *user_data,
		struct sd_out_sample *sample));
        
/*! Create new out for stopping after certain time. */
SD_API struct sd_out *
sd_out_new_until(double time);

/*! Create new out for ignoring state or output vectors. */
SD_API struct sd_out *
sd_out_new_ign(bool ignore_x, bool ignore_c,
	       struct sd_out *next);
