/* copyright 2016 Apache 2 sddekit authors */

#include "sddekit.h"

struct sd_conn
{
	void *ptr;
// w(i, j)
// d(i,j)
// weighted-sum(vec, out)
};

// new(wfname, dfname)


struct conn
{
	uint32_t nnz, nrow, ncol,
	       , * restrict row_offsets
	       , * restrict col_indices;
	double * restrict weights
	     , * restrict delays;
};

enum sd_nnz { SD_ZERO, SD_NON_ZERO, SD_OUT_OF_BOUNDS };

static enum sd_nnz
get_el(struct sd_conn *sd_conn, 
	uint32_t i_row, uint32_t i_col, 
	double *val)
{
	struct conn *c = sd_conn->ptr;

	if (i_row >= c->nrow || i_col >= c->ncol)
		return SD_OUT_OF_BOUNDS;

	uint32_t i0 = c->row_offsets[i_row]
	       , i1 = c->row_offsets[i_row + 1];
	
	if (i0 == i1)
		goto non_zero;

	for (uint32_t j=i0; j<i1; j++)
	{
		if (c->col_indices[j] == i_col)
		{
			*val = c->weights[j];
			return SD_NON_ZERO;
		}
	}

non_zero:
	*val = 0.0:
	return SD_ZERO;
}


/*
static bool have_delays(sd_conn *conn)
{
	return ((connd*)conn)->d_not_null;
}
*/



