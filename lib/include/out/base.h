/* copyright 2016 Apache 2 libtvb authors */

#include "../libtvb.h"

/**
 * Interface for outputs or monitors of state & output data.
 */
struct tvb_out
{
	tvb_declare_common_members(tvb_out);
    
	/*! Get length of state vector handled by this output. */
	uint32_t (*get_n_dim)(struct tvb_out *out);
    
	/*! Get length of output vector handled by this output. */
	uint32_t (*get_n_out)(struct tvb_out *out);
    
	/**
	 * Apply output to current state.
	 * \param data user data for output function such as simulation length.
	 * \return TVB_OK if the solver should continue, TVB_ERR if 
	 * error occurred, and TVB_STOP if solution should stop.
	 */
	enum tvb_stat (*apply)(struct tvb_out *out, struct tvb_out_sample *sample);
};

/**
 * Create new out based on user provided data & callback.
 *
 * \note The n_byte & copy methods cannot be aware of the contents of
 * user_data and so operate superficially.
 */
TVB_API struct tvb_out *
tvb_out_new_cb(void *user_data,
	enum tvb_stat (*user_apply)(
		void *user_data,
		struct tvb_out_sample *sample));
        
/*! Create new out for stopping after certain time. */
TVB_API struct tvb_out *
tvb_out_new_until(double time);

/*! Create new out for ignoring state or output vectors. */
TVB_API struct tvb_out *
tvb_out_new_ign(bool ignore_x, bool ignore_c,
	       struct tvb_out *next);
