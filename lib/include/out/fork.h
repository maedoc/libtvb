/* copyright 2016 Apache 2 libtvb authors */

#include "../libtvb.h"

/*! Interface for fork output {{{ */
struct tvb_out_fork
{
	tvb_declare_common_members(tvb_out_fork);
    
	/*! Get out interface for this instance. */
	struct tvb_out *(*as_out)(struct tvb_out_fork *fork);
    
	/*! Get number of receivers. */
	uint32_t (*get_n_receiver)(struct tvb_out_fork *fork);
    
	/*! Get i'th receiver. */
	struct tvb_out *(*get_receiver)(struct tvb_out_fork *fork, uint32_t i);
};

/*! Create instance of output splitter. */
TVB_API struct tvb_out_fork *
tvb_out_fork_new(uint32_t n_receiver, struct tvb_out **receivers);