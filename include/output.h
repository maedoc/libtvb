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

	/**
	 * Apply output to current state.
	 * \param data user data for output function such as simulation length.
	 * \return SD_OK if the solver should continue, SD_ERR if 
	 * error occurred, and SD_STOP if solution should stop.
	 */
	enum sd_stat (*apply)(struct sd_out *out, struct sd_out_sample *sample);
};

/* }}} */

/*! Create new out based on user provided data & callback. */
SD_API struct sd_out *
sd_out_new_cb(void *user_data,
	enum sd_stat (*user_apply)(
		void *user_data,
		struct sd_out_sample *sample));

/*! Interface for auto-allocating array output. {{{ */
struct sd_out_mem
{
	sd_declare_common_members(sd_out_mem);

	/*! Get interface for output. */
	struct sd_out *(*as_out)(struct sd_out_mem *mem);

	/*! Get number of state variables in memory buffer. */
	uint32_t (*get_n_dim)(struct sd_out_mem *mem);

	/*! Get number of coupling variables in memory buffer. */
	uint32_t (*get_n_out)(struct sd_out_mem *mem);

	/*! Get number of samples in memory buffer. */
	uint32_t (*get_n_sample)(struct sd_out_mem *mem);

	/*! Get state variable buffer. */
	double *(*get_state)(struct sd_out_mem *mem);

	/*! Get coupling variable buffer. */
	double *(*get_output)(struct sd_out_mem *mem);
};

/*! Create new output memory buffer. */
SD_API struct sd_out_mem *
sd_out_mem_new();

/* }}} */

/*! Interface for splitter output {{{ */
struct sd_out_tee
{
	sd_declare_common_members(sd_out_tee);

	/*! Get out interface for this instance. */
	struct sd_out *(*as_out)(struct sd_out_tee *tee);

	/*! Get number of outputs for splitter. */
	uint32_t (*get_n_out)(struct sd_out_tee *tee);

	/*! Get i'th output callback. */
	struct sd_out *(*get_out_i)(struct sd_out_tee *, uint32_t i);
};

/*! Create instance of output splitter. */
SD_API struct sd_out_tee *
sd_out_tee_new(uint32_t n_out, struct sd_out **outs);

/* }}} */

/*! Interface for temporal average out. {{{ */
struct sd_out_tavg
{
	sd_declare_common_members(sd_out_tavg);

	/*! Get interface for output. */
	struct sd_out *(*as_out)(struct sd_out_tavg *tavg);

	/*! Get number of samples used for temporal average output. */
	uint32_t (*get_len)(struct sd_out_tavg *tavg);

	/*! Get current positon in buffer of temporal average output. */
	uint32_t (*get_pos)(struct sd_out_tavg *tavg);

	/*! Get current time in buffer of temporal average output. */
	double (*get_t)(struct sd_out_tavg *tavg);

	/*! Get out which receives this temporal average. */
	struct sd_out * (*get_receiver)(struct sd_out_tavg *tavg);

	/*! Get average state variables of temporal average output. */
	double *(*get_x)(struct sd_out_tavg *tavg);

	/*! Get average coupling variables of temporal average output. */
	double *(*get_c)(struct sd_out_tavg *tavg);
};

/*! Create instance of temporal average output. */
SD_API struct sd_out_tavg *
sd_out_tavg_new(uint32_t len, struct sd_out *receiver);

/* TODO Hanning window tavg, improved freq accuracy */

/* }}} */

/*! Temporal convolution output. {{{ */
struct sd_out_conv
{
	sd_declare_common_members(sd_out_conv);

	/*! Get interface for output. */
	struct sd_out *(*as_out)(struct sd_out_conv *conv);

	/*! Get current position in buffers. */
	uint32_t (*get_pos)(struct sd_out_conv *conv);

	/*! Get length of filter / kernel. */
	uint32_t (*get_len)(struct sd_out_conv *conv);

	/*! Get subsampling factor. */
	uint32_t (*get_skip)(struct sd_out_conv *conv);

	/*! Get number of samples consumed before next sample produced. */
	uint32_t (*get_skip_count)(struct sd_out_conv *conv);

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
sd_out_conv_new(uint32_t len, double *filt, 
		uint32_t skip, struct sd_out *receiver);

/* Various convolution kernels */

/**
 * Glover 1999 double-gamma HRF kernel, based on NiPy.
 *
 * \param[in] n number of time points
 * \param[in] dt time step between HRF samples.
 * \param[out] x values of HRF at time points in t.
 */
SD_API void sd_hrf_glover(uint32_t n, double dt, double *hrf);

/**
 * First-order Volterra HRF kernel, based on TVB.
 *
 * \param[in] n number of time points.
 * \param[in] dt time step between HRF samples.
 * \param[out] x values of HRF at time points in t.
 */
SD_API void sd_hrf_volt1(uint32_t n, double dt, double *hrf);

/* }}} */

/*! Interface for spatial filter bank output. {{{ */
struct sd_out_sfilt
{
	sd_declare_common_members(sd_out_sfilt);

	/*! Get out interface for this instance. */
	struct sd_out *(*as_out)(struct sd_out_sfilt *sfilt);

	/*! Get number of filters of spatial filter output. */
	uint32_t (*get_n_filter)(struct sd_out_sfilt *sfilt);

	/*! Get length of filters of spatial filter output. */
	uint32_t (*get_filter_length)(struct sd_out_sfilt *sfilt);

	/*! Get coefficients of state vector filters. */
	double *(*get_state_filters)(struct sd_out_sfilt *sfilt);

	/*! Get coefficients of output vector filters. */
	double *(*get_output_filters)(struct sd_out_sfilt *sfilt);

	/*! Get output callback of spatial filter output. */
	struct sd_out *(*get_receiver)(struct sd_out_sfilt *sfilt);
};

/**
 * Create instance of spatial filter output.
 *
 * \param nfilt number of spatial filters
 * \param filtlen length of filter coefficients.
 * \param xfilts filter coefficients for state variablex.
 * \param cfilts filter coefficients for coupling variables.
 * \param out output callback to pass filtered data to.
 */
SD_API struct sd_out_sfilt *
sd_out_sfilt_new(
	uint32_t n_filter, uint32_t filter_length, 
	double *state_filters, double *output_filters, 
	struct sd_out *receiver);

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
