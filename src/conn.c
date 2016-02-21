/* copyright 2016 Apache 2 sddekit authors */

#include "sddekit.h"

struct sd_conn
{
	const void *ptr;
	enum sd_nnz
	(*get_el)(const struct sd_conn *sd_conn, 
		const uint32_t i_row, const uint32_t i_col, 
		double *weight, double *delay
	);
	double (* const weighted_sum)(
		const struct sd_conn *,
		const double * restrict
		);
	const double *(*get_weights)(const struct sd_conn *);
	const double *(*get_delays)(const struct sd_conn *);
	double (*get_delay_scale)(const struct sd_conn *);
	enum sd_stat (*set_delay_scale)(const struct sd_conn *, double);
};

struct conn
{
	uint32_t nnz, nrow, ncol
	       , * restrict row_offsets
	       , * restrict col_indices;
	double * restrict weights
	     , * restrict delays
	     , delay_scale;
};

double get_delay_scale(const struct sd_conn *sd_conn)
{
	return ((struct conn*) sd_conn->ptr)->delay_scale;
}

enum sd_stat set_delay_scale(const struct sd_conn *sd_conn, double new_delay_scale)
{
	if (new_delay_scale <= 0.0)
	{
		sd_err("delay_scale <= 0");
		return SD_ERR;
	}
	struct conn *conn = (struct conn*) sd_conn->ptr; 
	double rescaler = conn->delay_scale / new_delay_scale;
	for (uint32_t i=0; i<conn->nnz; i++)
		conn->delays[i] *= rescaler;
	conn->delay_scale = new_delay_scale;
	return SD_OK;
}

enum sd_nnz { SD_ZERO, SD_NON_ZERO, SD_OUT_OF_BOUNDS };

static enum sd_nnz
get_el(const struct sd_conn *sd_conn, 
	const uint32_t i_row, const uint32_t i_col, 
	double *weight, double *delay)
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
			*weight = c->weights[j];
			*delay = c->delays[j];
			return SD_NON_ZERO;
		}
	}

non_zero:
	*weight = 0.0;
	*delay = 0.0;
	return SD_ZERO;
}

double weighted_sum(
	const struct sd_conn *sd_conn,
	const double * restrict x
	)
{
	const struct conn * const conn = sd_conn->ptr;
	double sum = 0.0;
	const double *wi = conn->weights;
	for (uint32_t i=0; i<conn->nnz; i++, wi++, x++)
		sum += *wi * *x;
	return sum;
}

struct sd_conn *
sd_conn_new_sparse(
	uint32_t n_rows,
	uint32_t n_cols,
	uint32_t n_nonzeros,
	uint32_t * restrict row_offsets,
	uint32_t * restrict col_indices,
	double * restrict weights,
	double * restrict delays
);

struct sd_conn * sd_conn_new_dense(
	uint32_t n_rows,
	uint32_t n_cols,
	double * restrict weights,
	double * restrict delays
);

struct sd_conn *
sd_conn_new_files(
	const char *weights_filename,
	const char *delays_filename
);
