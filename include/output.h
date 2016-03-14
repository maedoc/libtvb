/* copyright 2016 Apache 2 sddekit authors */

#include "sddekit.h"

/*! Data structure passed to an output apply function.  {{{
 *
 * \param time current time.
 * \param n_dim number of state variables.
 * \param n_out number of coupling terms.
 * \param state state variable vector.
 * \param output efferent / output vector.
 */
struct sd_out_sample
{
	double time;
	uint32_t n_dim;
	uint32_t n_out;
	double *state;
	double *output;
};

/* }}} */

/* base out interface {{{ */

/*! Interface for outputs. */
struct sd_out
{
	sd_declare_common_members(sd_out);
	/*! Get length of state vector handled by this output. */
	uint32_t (*get_n_dim)(struct sd_out *out);
	/*! Get length of output vector handled by this output. */
	uint32_t (*get_n_out)(struct sd_out *out);
	/**
	 * Apply output to current state.
	 * \param data user data for output function such as simulation length.
	 * \return SD_OK if the solver should continue, SD_ERR if 
	 * error occurred, and SD_STOP if solution should stop.
	 */
	enum sd_stat (*apply)(struct sd_out *out, struct sd_out_sample *sample);
};

/* }}} */

/* callback out {{{ */
/**
 * Create new out based on user provided data & callback.
 *
 * \note The n_byte & copy methods cannot be aware of the contents of
 * user_data and so operate superficially.
 */
SD_API struct sd_out *
sd_out_new_cb(void *user_data,
	enum sd_stat (*user_apply)(
		void *user_data,
		struct sd_out_sample *sample));

/* }}} */

/*! Interface for auto-allocating array output. {{{ */
struct sd_out_mem
{
	sd_declare_common_members(sd_out_mem);
	/*! Get interface for output. */
	struct sd_out *(*as_out)(struct sd_out_mem *mem);
	/*! Get number of samples in memory buffer. */
	uint32_t (*get_n_sample)(struct sd_out_mem *mem);
	/*! Get state variable buffer. */
	double *(*get_states)(struct sd_out_mem *mem);
	/*! Get coupling variable buffer. */
	double *(*get_outputs)(struct sd_out_mem *mem);
};

/*! Create new output memory buffer. */
SD_API struct sd_out_mem *
sd_out_mem_new();

/* }}} */

/*! Interface for fork output {{{ */
struct sd_out_fork
{
	sd_declare_common_members(sd_out_fork);
	/*! Get out interface for this instance. */
	struct sd_out *(*as_out)(struct sd_out_fork *fork);
	/*! Get number of receivers. */
	uint32_t (*get_n_receiver)(struct sd_out_fork *fork);
	/*! Get i'th receiver. */
	struct sd_out *(*get_receiver)(struct sd_out_fork *fork, uint32_t i);
};

/*! Create instance of output splitter. */
SD_API struct sd_out_fork *
sd_out_fork_new(uint32_t n_receiver, struct sd_out **receivers);

/* }}} */

/*! Temporal convolution output. {{{ */

struct sd_out_conv
{
	sd_declare_common_members(sd_out_conv);

	/*! Get interface for output. */
	struct sd_out *(*as_out)(struct sd_out_conv *conv);

	/*! Get current position in buffers. */
	uint32_t (*get_position)(struct sd_out_conv *conv);

	/*! Get length of filter / kernel. */
	uint32_t (*get_length)(struct sd_out_conv *conv);

	/*! Get subsampling factor. */
	uint32_t (*get_n_skip)(struct sd_out_conv *conv);

	/*! Get sd_out instance to which samples are passed. */
	struct sd_out *(*get_receiver)(struct sd_out_conv *conv);
};

/**
 * Create instance of temporal convolution output.
 *
 * \param len length of filter
 * \param filt coefficients of filter
 * \param out output to pass convolution samples to.
 * \return instance of sd_out_conv or NULL if error occurred.
 */
SD_API struct sd_out_conv *
sd_out_conv_new(uint32_t length, double *kernel, 
		uint32_t n_skip, struct sd_out *receiver);

/* Various convolution kernels */

/*! Flat window (for e.g. temporal averaging). */
SD_API void sd_conv_kern_flat(uint32_t n, double *kernel);

/*! Hanning window (for e.g. spectral analysis). */
SD_API void sd_conv_kern_hanning(uint32_t n, double *kernel);

/**
 * Glover 1999 double-gamma HRF kernel, based on NiPy.
 *
 * \param[in] n number of time points
 * \param[in] dt time step between HRF samples.
 * \param[out] x values of HRF at time points in t.
 */
SD_API void sd_conv_kern_hrf_glover(uint32_t n, double dt, double *hrf);

/**
 * First-order Volterra HRF kernel, based on TVB.
 *
 * \param[in] n number of time points.
 * \param[in] dt time step between HRF samples.
 * \param[out] x values of HRF at time points in t.
 */
SD_API void sd_conv_kern_hrf_volt1(uint32_t n, double dt, double *hrf);

/* }}} */

/*! Interface for linear operator output. {{{ */
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

/* }}} */

/*! Create new out for stopping after certain time. */
SD_API struct sd_out *
sd_out_new_until(double time);

/*! Create new out for ignoring state or output vectors. */
SD_API struct sd_out *
sd_out_new_ign(bool ignore_x, bool ignore_c,
	       struct sd_out *next);

/* vim: foldmethod=marker filetype=c
 */
