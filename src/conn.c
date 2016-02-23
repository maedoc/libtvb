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

static enum sd_stat get_el(
	const struct sd_conn *sd_conn, 
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

const double * get_weights(
	const struct sd_conn *c)
{
	return ((struct conn*) c->ptr)->weights;
}

const double * get_delays(
	const struct sd_conn *c)
{
	return ((struct conn*) c->ptr)->delays;
}

uint32_t get_n_nonzeros(const struct sd_conn *sd_conn)
{
	return ((struct conn*) sd_conn->ptr)->nnz;
}

void free_conn(const struct sd_conn *sd_conn)
{
	const struct conn *conn = sd_conn->ptr;
	sd_free(conn->weights);
	sd_free(conn->delays);
	sd_free(conn->row_offsets);
	sd_free(conn->col_indices);
	sd_free((void*) conn);
}
	
const struct sd_conn * sd_conn_new_sparse(
	uint32_t n_rows,
	uint32_t n_cols,
	uint32_t n_nonzeros,
	uint32_t * restrict row_offsets,
	uint32_t * restrict col_indices,
	double * restrict weights,
	double * restrict delays
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
		.get_el = &get_el,
		.weighted_sum = &weighted_sum,
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

const struct sd_conn * sd_conn_new_dense(
	uint32_t n_rows,
	uint32_t n_cols,
	double * restrict weights,
	double * restrict delays
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

const struct sd_conn * sd_conn_new_files(
	const char *weights_filename,
	const char *delays_filename
)
{
	enum sd_stat stat;
	uint32_t n;
	double *weights, *delays;
	stat = sd_util_read_square_matrix(weights_filename, &n, &weights);
	if (stat != SD_OK)
	{
		sd_err("failed to read weights matrix");
		return NULL;
	}
	stat = sd_util_read_square_matrix(delays_filename, &n, &delays);
	if (stat != SD_OK)
	{
		sd_err("failed to read delays matrix");
		sd_free(weights);
		return NULL;
	}
	const struct sd_conn *sd_conn = sd_conn_new_dense(n, n, weights, delays);
	sd_free(weights);
	sd_free(delays);
	return sd_conn;
}
