/* copyright 2016 Apache 2 libtvb authors */

#include "../libtvb.h"

/*! Temporal convolution output. */

struct tvb_out_conv
{
	tvb_declare_common_members(tvb_out_conv);

	/*! Get interface for output. */
	struct tvb_out *(*as_out)(struct tvb_out_conv *conv);

	/*! Get current position in buffers. */
	uint32_t (*get_position)(struct tvb_out_conv *conv);

	/*! Get length of filter / kernel. */
	uint32_t (*get_length)(struct tvb_out_conv *conv);

	/*! Get subsampling factor. */
	uint32_t (*get_n_skip)(struct tvb_out_conv *conv);

	/*! Get tvb_out instance to which samples are passed. */
	struct tvb_out *(*get_receiver)(struct tvb_out_conv *conv);
};

/**
 * Create instance of temporal convolution output.
 *
 * \param len length of filter
 * \param filt coefficients of filter
 * \param out output to pass convolution samples to.
 * \return instance of tvb_out_conv or NULL if error occurred.
 */
TVB_API struct tvb_out_conv *
tvb_out_conv_new(uint32_t length, double *kernel, 
		uint32_t n_skip, struct tvb_out *receiver);

/* Various convolution kernels */

/*! Flat window (for e.g. temporal averaging). */
TVB_API void tvb_conv_kern_flat(uint32_t n, double *kernel);

/*! Hanning window (for e.g. spectral analysis). */
TVB_API void tvb_conv_kern_hanning(uint32_t n, double *kernel);

/**
 * Glover 1999 double-gamma HRF kernel, based on NiPy.
 *
 * \param[in] n number of time points
 * \param[in] dt time step between HRF samples.
 * \param[out] x values of HRF at time points in t.
 */
TVB_API void tvb_conv_kern_hrf_glover(uint32_t n, double dt, double *hrf);

/**
 * First-order Volterra HRF kernel, based on TVB.
 *
 * \param[in] n number of time points.
 * \param[in] dt time step between HRF samples.
 * \param[out] x values of HRF at time points in t.
 */
TVB_API void tvb_conv_kern_hrf_volt1(uint32_t n, double dt, double *hrf);