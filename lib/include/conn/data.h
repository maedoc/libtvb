/* copyright 2016 Apache 2 libtvb authors */

#include "libtvb.h"

#ifdef __cplusplus
extern "C" {
#endif

struct conn
{
	uint32_t nnz, n_row, n_col
	       , *row_offsets
	       , *col_indices;
	double *weights
	     , *delays
	     , delay_scale;
	struct tvb_conn tvb_conn;
};

#ifdef __cplusplus
}; /* extern "C" */
#endif