/* copyright 2016 Apache 2 libtvb authors */

#include "libtvb.h"

struct tvb_conn
{
	tvb_declare_common_members(tvb_conn);

	/*! Row-wise weighted sum w/ non-zeros of other sparse * mat w/ sparsity structure. */
	void (*row_wise_weighted_sum)(struct tvb_conn *conn, double *values, double *sums);

	/*! Get the number of non-zero elements in weights. */
	uint32_t (*get_n_nonzero)(struct tvb_conn *);
    
    /*! Get indices of non-zero elements. */
    uint32_t *(*get_nonzero_indices)(struct tvb_conn *tvb_conn);

	/*! Get vector of non-zero weights. */
	double *(*get_weights)(struct tvb_conn *);

	/*! Get vector of delays corresponding to non-zero weights. */
	double *(*get_delays)(struct tvb_conn *);

	/*! Get the current scale of the delays*/
	double (*get_delay_scale)(struct tvb_conn *);

	/*! Set the current scale of the delays*/
	enum tvb_stat (*set_delay_scale)(struct tvb_conn *, double);

	/*! Get the number of rows or targets in this connectivity. */
	uint32_t (*get_n_row)(struct tvb_conn *conn);

	/*! Get the number of rows or targets in this connectivity. */
	uint32_t (*get_n_col)(struct tvb_conn *conn);
};

/*! Construct a new connectivity from the given sparse data & structure. */
TVB_API struct tvb_conn *
tvb_conn_new_sparse(
	uint32_t n_row, uint32_t n_col, uint32_t n_nonzero,
	uint32_t *row_offsets, uint32_t *col_indices,
	double *weights, double *delays
);

/*! Construct a new connectivity from dense data set. */
TVB_API struct tvb_conn *
tvb_conn_new_dense(uint32_t n_row, uint32_t n_col, double * weights, double * delays);
