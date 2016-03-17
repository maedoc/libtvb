/* copyright 2016 Apache 2 sddekit authors */

#include "sddekit.h"

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
	struct sd_conn sd_conn;
};

#ifdef __cplusplus
}; /* extern "C" */
#endif