/* copyright 2016 Apache 2 libtvb authors */

#include "../libtvb.h"

/*! Interface for auto-allocating array output. {{{ */
struct tvb_out_mem
{
	tvb_declare_common_members(tvb_out_mem);
    
	/*! Get interface for output. */
	struct tvb_out *(*as_out)(struct tvb_out_mem *mem);
    
	/*! Get number of samples in memory buffer. */
	uint32_t (*get_n_sample)(struct tvb_out_mem *mem);
    
	/*! Get state variable buffer. */
	double *(*get_states)(struct tvb_out_mem *mem);
    
	/*! Get coupling variable buffer. */
	double *(*get_outputs)(struct tvb_out_mem *mem);
};

/*! Create new output memory buffer. */
TVB_API struct tvb_out_mem *
tvb_out_mem_new();