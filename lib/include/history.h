/* copyright 2016 Apache 2 sddekit authors */

#include "sddekit.h"

/**
 * Interface for function to fill history buffer.
 */
struct sd_hfill
{
	sd_declare_common_members(sd_hfill);

	/**
	 * Apply history filling function to buffer.
	 *
	 * \param[in] hf instance of history filler.
	 * \param[in] n number of elements in the history buffer.
	 * \param[in] t vector of time for each element in history buffer.
	 * \param[in] indices variable index for each element in history buffer.
	 * \param[out] buf history buffer to fill .
	 * \return SD_OK if filler succeeds, SD_ERR if error occurs.
	 */
	enum sd_stat (*apply)(struct sd_hfill *,
			 uint32_t  n, 
			 double   *times, 
			 uint32_t *indices,
			 double   *buf);
};

/**
 * An sd_hfill instance which sets all elements of the history buffer
 * to a given value.
 */
SD_API struct sd_hfill *
sd_hfill_new_val(double val);

/* hfill }}} */

/* history {{{ */

struct sd_hist
{
	sd_declare_common_members(sd_hist);

	/*! Get number of delays in history. */
	uint32_t (*get_n_delay)(struct sd_hist *h);

	/*! Get current time in history. */
	double (*get_time)(struct sd_hist *h);

	/*! Get time step of history buffer. */
	double (*get_time_step)(struct sd_hist *h);

	/*! Get i'th variable index. */
	double (*get_var_idx)(struct sd_hist *h, uint32_t i);

	/*! Get i'th variable delay. */
	double (*get_var_del)(struct sd_hist *h, uint32_t i);

	/*! Fill history buffer with some user defined function of time. */
	enum sd_stat (*fill)(struct sd_hist *h, struct sd_hfill *filler);

	/*! Get aff[i] = eff[vi[i]](t - vd[i]). */
	void (*query)(struct sd_hist *h, double t, double *aff);

	/*! Update history buffer with new data. */
	void (*update)(struct sd_hist *h, double t, double *eff);
};

/**
 * Construct a history object which uses linear interpolation.
 *
 * \note The discretization of time used internally for the history
 * object does not need to be the same as that of the simulation.
 *
 * \param h an allocated history instance.
 * \param nd number of delayed coupling terms.
 * \param vi efferent index of each delayed coupling term.
 * \param vd delay of each delayed coupling term.
 * \param t0 starting time.
 * \param dt time-step to use in history buffer (need not equal solution dt).
 * \return initialized history instance or NULL if error occurs.
 */
SD_API struct sd_hist *
sd_hist_new_linterp(
	uint32_t n_delay,
	uint32_t *var_idx, 
	double *var_del, 
	double init_time, double time_step);

/** 
 * Construct a history object uses nearest interpolation.
 *
 * \note Nearest interpolation can introduce artifacts unless
 * the quantization error due to rounding is near zero.
 *
 * \note The current implementation is for compatibility with
 * other software and does not optimize for this case. Delay
 * values are rounded to nearest integer multiple of time step.
 */
SD_API struct sd_hist *
sd_hist_new_nearest(
	uint32_t n_delay,
	uint32_t *var_idx, 
	double *var_del, 
	double init_time, double time_step);

/**
 * Construct a history object which conforms to the history interface
 * but ignores the vd argument, using a delay of zero for all specified
 * delay coupled terms.
 */ 
SD_API struct sd_hist *
sd_hist_new_no_delays(
	uint32_t n_delay,
	uint32_t *var_idx, 
	double *var_del, 
	double init_time, double time_step);