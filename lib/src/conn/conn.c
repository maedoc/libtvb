/* copyright 2016 Apache 2 sddekit authors */

#include "sddekit.h"
#include "conn/data.h"
#include "conn/rwws.h"

static void row_wise_weighted_sum(struct sd_conn *sd_conn, double *values, double *sums)
{
    rwws_pre(sd_conn, values, NULL, sums);
}

/* set / get */

static double get_delay_scale(struct sd_conn *sd_conn) { return ((struct conn*) sd_conn->data)->delay_scale; }

static enum sd_stat set_delay_scale(
	struct sd_conn *sd_conn, double new_delay_scale)
{
	if (new_delay_scale <= 0.0)
	{
		sd_err("delay_scale <= 0");
		return SD_ERR;
	}
	struct conn *conn = (struct conn*) sd_conn->data; 
	double rescaler = conn->delay_scale / new_delay_scale;
	for (uint32_t i=0; i<conn->nnz; i++)
		conn->delays[i] *= rescaler;
	conn->delay_scale = new_delay_scale;
	return SD_OK;
}

static double * get_weights(struct sd_conn *c) { return ((struct conn*) c->data)->weights; }

static double * get_delays(struct sd_conn *c) { return ((struct conn*) c->data)->delays; }

static uint32_t get_n_nonzero(struct sd_conn *sd_conn) { return ((struct conn*) sd_conn->data)->nnz; }

static uint32_t *get_nonzero_indices(struct sd_conn *sd_conn)
{
    return ((struct conn *) sd_conn->data)->col_indices;
}

static uint32_t get_n_row(struct sd_conn *sd_conn) { return ((struct conn*) sd_conn->data)->n_row; }

static uint32_t get_n_col(struct sd_conn *sd_conn) { return ((struct conn*) sd_conn->data)->n_col; }

/* obj */

static struct sd_conn *copy(struct sd_conn *sd_conn)
{
	struct conn *data = sd_conn->data;
	struct sd_conn *sd_conn_copy = sd_conn_new_sparse(
		data->n_row, data->n_col, data->nnz,
		data->row_offsets, data->col_indices,
		data->weights, data->delays);
	if (sd_conn_copy == NULL)
		sd_err("failed to copy sd_conn instance.");
	return sd_conn_copy;
}

static uint32_t n_byte(struct sd_conn *sd_conn)
{
	struct conn *data = sd_conn->data;
	uint32_t byte_count = sizeof(struct conn);
	byte_count += sizeof(uint32_t)*(data->n_row + 1);
	byte_count += sizeof(uint32_t)*data->nnz;
	byte_count += sizeof(uint32_t)*data->nnz;
	byte_count += sizeof(uint32_t)*data->nnz;
	return byte_count;
}

static void conn_free(struct sd_conn *sd_conn)
{
	struct conn *conn = sd_conn->data;
	sd_free(conn->weights);
	sd_free(conn->delays);
	sd_free(conn->row_offsets);
	sd_free(conn->col_indices);
	sd_free((void*) conn);
}

/* }}} */
	
/* constructors {{{ */

static struct sd_conn sd_conn_defaults = {
	.copy = &copy,
	.n_byte = &n_byte,
	.free = &conn_free,
	.row_wise_weighted_sum = &row_wise_weighted_sum,
	.get_n_nonzero = &get_n_nonzero,
    .get_nonzero_indices = &get_nonzero_indices,
	.get_weights = &get_weights,
	.get_delays = &get_delays,
	.get_delay_scale = &get_delay_scale,
	.set_delay_scale = &set_delay_scale,
	.get_n_row = &get_n_row,
	.get_n_col = &get_n_col
};

struct sd_conn * sd_conn_new_sparse(
	uint32_t n_rows,
	uint32_t n_cols,
	uint32_t n_nonzero,
	uint32_t *row_offsets,
	uint32_t *col_indices,
	double *weights,
	double *delays
)
{
	struct conn *conn, zero={0};
	if ((conn = sd_malloc(sizeof(struct conn))) == NULL
	 || (*conn = zero, 0)
	 || (conn->row_offsets = sd_malloc(sizeof(uint32_t)*(n_rows + 1))) == NULL
	 || (conn->col_indices = sd_malloc(sizeof(uint32_t)*n_nonzero)) == NULL
	 || (conn->weights = sd_malloc(sizeof(uint32_t)*n_nonzero)) == NULL
	 || (conn->delays = sd_malloc(sizeof(uint32_t)*n_nonzero)) == NULL
	)
	{
		if (conn->row_offsets!=NULL) sd_free(conn->row_offsets);
		if (conn->col_indices!=NULL) sd_free(conn->col_indices);
		if (conn->weights!=NULL) sd_free(conn->weights);
		if (conn!=NULL) sd_free(conn);
		sd_err("alloc conn data failed.");
		return NULL;
	}
	conn->n_row = n_rows;
	conn->n_col = n_cols;
	conn->nnz = n_nonzero;
	conn->row_offsets = row_offsets;
	conn->col_indices = col_indices;
	conn->weights = weights;
	conn->delays = delays;
	conn->delay_scale = 1.0;
	conn->sd_conn = sd_conn_defaults;
	conn->sd_conn.data = conn;
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
	stat = sd_util_sparse_from_dense(
		n_rows, n_cols, weights, delays, 0.0,
		&n_nonzeros, &row_offsets, &col_indices,
		&sparse_weights, &sparse_delays);
	if (stat != SD_OK)
	{
		sd_err("unable to convert dense connectivity to sparse");
		return NULL;
	}
	struct sd_conn *sparse_conn = sd_conn_new_sparse(
		n_rows, n_cols, n_nonzeros,
		row_offsets, col_indices, 
		sparse_weights, sparse_delays);
	sd_free(row_offsets);
	sd_free(col_indices);
	sd_free(sparse_delays);
	sd_free(sparse_weights);
	if (sparse_conn == NULL)
		sd_err("failed to construct sd_conn from sparse data set.");
	return sparse_conn;
}

/* }}} */

/* vim: foldmethod=marker
 */
