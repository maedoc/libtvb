/* copyright 2016 Apache 2 sddekit authors */

#include "../sddekit.h"

/*! Interface for fork output {{{ */
struct sd_out_fork
{
	sd_declare_common_members(sd_out_fork);
    
	/*! Get out interface for this instance. */
	struct sd_out *(*as_out)(struct sd_out_fork *fork);
    
	/*! Get number of receivers. */
	uint32_t (*get_n_receiver)(struct sd_out_fork *fork);
    
	/*! Get i'th receiver. */
	struct sd_out *(*get_receiver)(struct sd_out_fork *fork, uint32_t i);
};

/*! Create instance of output splitter. */
SD_API struct sd_out_fork *
sd_out_fork_new(uint32_t n_receiver, struct sd_out **receivers);