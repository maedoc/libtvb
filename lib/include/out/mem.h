/* copyright 2016 Apache 2 sddekit authors */

#include "../sddekit.h"

/*! Interface for auto-allocating array output. {{{ */
struct sd_out_mem
{
	sd_declare_common_members(sd_out_mem);
    
	/*! Get interface for output. */
	struct sd_out *(*as_out)(struct sd_out_mem *mem);
    
	/*! Get number of samples in memory buffer. */
	uint32_t (*get_n_sample)(struct sd_out_mem *mem);
    
	/*! Get state variable buffer. */
	double *(*get_states)(struct sd_out_mem *mem);
    
	/*! Get coupling variable buffer. */
	double *(*get_outputs)(struct sd_out_mem *mem);
};

/*! Create new output memory buffer. */
SD_API struct sd_out_mem *
sd_out_mem_new();