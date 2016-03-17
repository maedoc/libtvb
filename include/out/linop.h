/* copyright 2016 Apache 2 sddekit authors */

#include "../sddekit.h"

/*! Interface for linear operator output. */
struct sd_out_linop
{
	sd_declare_common_members(sd_out_linop);

	/*! Get out interface for this instance. */
	struct sd_out *(*as_out)(struct sd_out_linop *linop);

	/*! True if linop applies to state vector, otherwise false. */
	bool (*get_on_state)(struct sd_out_linop *linop);

	/*! Get number of rows in linear operator matrix. */
	uint32_t (*get_n_row)(struct sd_out_linop *linop);

	/*! Get number of columns in linear operator matrix. */
	uint32_t (*get_n_col)(struct sd_out_linop *linop);

	/*! Get elements of linear operator matrix. */
	double *(*get_matrix)(struct sd_out_linop *linop);

	/*! Get output callback of spatial filter output. */
	struct sd_out *(*get_receiver)(struct sd_out_linop *linop);
};

/**
 * Create instance of linear operator (matrix) output, which applies
 * either to states or outputs.
 *
 * Let L be filled from elements in the matrix array, and v the 
 * selected vector of state or output. This computes L' * v
 * in MATLAB syntax and L.dot(v) in NumPy syntax. In other words,
 * the matrix is addressed in row-major order and left-multiplies
 * the vector.
 *
 * If on_states is true, then matrix is applied to the state vector,
 * and the output vector is ignored and the receiver sees n_out = 0
 * and output = NULL. If on_states is false, the inverse holds.
 *
 * \note An internal copy of matrix is made during the constructor.
 *
 * TODO variant with stride or index on state/output vector.
 */
SD_API struct sd_out_linop *
sd_out_linop_new(
	bool on_state,
	uint32_t n_row,
	uint32_t n_col,
	double *matrix,
	struct sd_out *receiver
	);