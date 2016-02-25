/* copyright 2016 Apache 2 sddekit authors */

#include "sddekit.h"

struct conn
{
	uint32_t nnz, nrow, ncol
	       , * restrict row_offsets
	       , * restrict col_indices;
	double * restrict weights
	     , * restrict delays
	     , delay_scale;
	struct sd_conn sd_conn;
};

/* TODO this is likely target for optimization */
void row_wise_weighted_sum(struct sd_conn *sd_conn, double * restrict values, double * restrict sums)
{
	struct conn *conn = sd_conn->ptr;
	for (uint32_t i=0; i<conn->nrow; i++)
	{
		double sum = 0.0;
		for (uint32_t j=conn->row_offsets[i]; j<conn->row_offsets[i+1]; j++)
			sum += conn->weights[j] * values[j];
		sums[i] = sum;
	}
}

double get_delay_scale(struct sd_conn *sd_conn)
{
	return ((struct conn*) sd_conn->ptr)->delay_scale;
}

enum sd_stat set_delay_scale(
		struct sd_conn *sd_conn, double new_delay_scale)
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

static enum sd_stat get_el(
	struct sd_conn *sd_conn, 
	uint32_t i_row, uint32_t i_col, 
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

/* TODO if possible this is one of those primitives to target for
 * optimization
 */
double weighted_sum(
	struct sd_conn *sd_conn,
	double *x
	)
{
	const struct conn * const conn = sd_conn->ptr;
	double sum = 0.0;
	const double *wi = conn->weights;
	for (uint32_t i=0; i<conn->nnz; i++, wi++, x++)
		sum += *wi * *x;
	return sum;
}

double * get_weights(
	struct sd_conn *c)
{
	return ((struct conn*) c->ptr)->weights;
}

double * get_delays(
	struct sd_conn *c)
{
	return ((struct conn*) c->ptr)->delays;
}

uint32_t get_n_nonzeros(struct sd_conn *sd_conn)
{
	return ((struct conn*) sd_conn->ptr)->nnz;
}

void free_conn(struct sd_conn *sd_conn)
{
	struct conn *conn = sd_conn->ptr;
	sd_free(conn->weights);
	sd_free(conn->delays);
	sd_free(conn->row_offsets);
	sd_free(conn->col_indices);
	sd_free((void*) conn);
}
	
struct sd_conn * sd_conn_new_sparse(
	uint32_t n_rows,
	uint32_t n_cols,
	uint32_t n_nonzeros,
	uint32_t *row_offsets,
	uint32_t *col_indices,
	double *weights,
	double *delays
)
{
	struct conn *conn;
	if ((conn = malloc(sizeof(struct conn))) == NULL)
	{
		sd_err("alloc conn data failed.");
		return NULL;
	}
	conn->nrow = n_rows;
	conn->ncol = n_cols;
	conn->nnz = n_nonzeros;
	conn->row_offsets = row_offsets;
	conn->col_indices = col_indices;
	conn->weights = weights;
	conn->delays = delays;
	conn->delay_scale = 1.0;
	struct sd_conn c = {
		.ptr = conn,
		.row_wise_weighted_sum = &row_wise_weighted_sum,
		.get_weights = &get_weights,
		.get_delays = &get_delays,
		.get_delay_scale = &get_delay_scale,
		.set_delay_scale = &set_delay_scale,
		.get_n_nonzeros = &get_n_nonzeros,
		.free = &free_conn,
	};
	memcpy(&(conn->sd_conn), &c, sizeof(struct sd_conn));
	return &(conn->sd_conn);
}

struct sd_conn * sd_conn_new_dense(
	uint32_t n_rows,
	uint32_t n_cols,
	double *weights,
	double *delays
)
{
	enum sd_stat stat;
	uint32_t n_nonzeros, *row_offsets, *col_indices;
	double *sparse_weights, *sparse_delays;
	stat = sd_sparse_from_dense(
		n_rows, n_cols, weights, delays, 0.0,
		&n_nonzeros, &row_offsets, &col_indices,
		&sparse_weights, &sparse_delays);
	if (stat != SD_OK)
	{
		sd_err("unable to convert dense connectivity to sparse");
		return NULL;
	}
	return sd_conn_new_sparse(n_rows, n_cols, n_nonzeros,
		row_offsets, col_indices, 
		sparse_weights, sparse_delays);
}
