/* copyright 2016 Apache 2 sddekit authors */


/**  SDDEKit API header, containing only definitions
 * of SDDEKit's API, usually for use by including in some
 * other header like sddekit.h or a simplified one for binding.
 *
 */

#ifndef SDDEKIT_H
#include "prelude.h"
#define SDDEKIT_H
#endif

/*! Status codes returned by various functions. {{{ */
enum sd_stat
{
	/*! Function call succeeded */
	SD_OK,
	/*! An error occurred during the function call or one of the functions it called. */
	SD_ERR,
	/*! Returned by output object to indicate solver should continue */
	SD_CONT,
	/*! Returned by output object to indicate solver should stop */
	SD_STOP,
	/*! Returned by function it doesn't know */
	SD_UNKNOWN,
	/*! Returned to indicate zero value in sparse matrix */
	SD_ZERO,
	/*! Returned to indicate non zero value in sparse matrix */
	SD_NON_ZERO,
	/*! Returned to indicate an out-of-bounds condition */
	SD_OUT_OF_BOUNDS
};
/* }}} */

/* function-oriented API {{{ */

/* version numbers {{{ */

/*! Get major version number. */
uint32_t sd_ver_major();

/*! Get minor version number. */
uint32_t sd_ver_minor();

/* }}} */

/* memory allocators {{{ */

typedef void*(*sd_malloc_t)(size_t size);
typedef void*(*sd_realloc_t)(void *ptr, size_t size);
typedef void(*sd_free_t)(void *ptr);

/**
 * Set custom allocators to be used whenever sd_ calls require allocating or freeing 
 * memory.
 */
SD_API void
sd_malloc_set_allocators(sd_malloc_t malloc, sd_realloc_t realloc, sd_free_t free);

/**
 * Set allocators to stdlib functions (malloc, realloc, free)
 */
SD_API void
sd_malloc_set_stdlib_allocators();

/**
 * Allocate memory using current allocator.
 */
SD_API void *
sd_malloc(size_t size);

/**
 * Allocate memory using current allocator.
 */
SD_API void *
sd_realloc(void *ptr, size_t size);

/**
 * Initialize & finalize register of memory allocated by sd_malloc
 */
SD_API void
sd_malloc_reg_init();

SD_API void
sd_malloc_reg_stop();

/**
 * return SD_OK if valid pointer, SD_ERR if invalid, SD_UNKNOWN if we dont' know
 * (because register inactive for example) 
 */
SD_API sd_stat
sd_malloc_reg_query(void *);

/**
 * Free memory using current allocator.
 */

SD_API void
sd_free(void *ptr);

/* mem }}} */

/* utilities {{{ */

/* TODO organize a performance primitive section, e.g. sd_pp_* */

/**
 * Obtain unique sorted integers.
 * \note Caller must free uints when done.
 * \param n number of elements
 * \param ints array of at least n integers.
 * \param[out] nuniq address of number of unique integers.
 * \param[out] uints address of array of unique integers.
 * \return Returns SD_OK if call succeeds, SD_ERR if error occurs.
 */
SD_API enum sd_stat 
sd_util_uniqi(uint32_t n,
	      uint32_t * restrict ints, 
	      uint32_t * restrict nuniq, 
	      uint32_t **uints);

/**
 * Create CSR format sparse matrix from dense matrix, possibly thresholding.
 *
 * Caller responsible for freeing Or, Ic, sA when done.
 *
 * \param[in] m number of rows.
 * \param[in] n number of cols.
 * \param[in] dA elements of dense matrix.
 * \param[in] dB elements of second dense matrix (can be null).
 * \param[in] eps absolute threshold to consider element non-zero (can be 0.0 for no .
 * thresholding).
 * \param[out] nnz number of non-zeros.
 * \param[out] Or row offsets.
 * \param[out] Ic column indices.
 * \param[out] sA non-zeros elements of dA.
 * \param[out] sB non-zeros elements of dB. (is dB is null, this is unused).
 * \return SD_OK if conversion succeeds, SD_ERR if error occurred.
 */
SD_API enum sd_stat 
sd_util_sparse_from_dense(
	uint32_t m, uint32_t n, 
	double *dA, double *dB, double eps,
	uint32_t *nnz, uint32_t **Or, uint32_t **Ic, 
	double **sA, double **sB);

/* util }}} */

/* log / err  {{{ */

enum sd_log_level { SD_LOG_ERROR, SD_LOG_INFO, SD_LOG_DEBUG };

/*! Callback handler log messages */
typedef void (*sd_log_handler)(enum sd_log_level level, char *message);

/*! Set log message handler pointer used by sd_log_handle. */
SD_API void sd_log_set_handler(sd_log_handler new_handler);

/*! Get log message handler pointer used by sd_log_handle. */
SD_API sd_log_handler sd_log_get_handler();

/*! Handle log message; low-level: prefer macros below. */
SD_API void sd_log_handle(enum sd_log_level level, char *format, ...);

/* Macros that user should use & library MUST use. {{{ */

#ifdef _MSC_VER /* MSVC silently drops final comma when appropriate */

/* insert file, line, function name & new line*/
#define _sd_log_handle(level, fmt, ...) \
       	sd_log_handle(level, "%s:%d (%s) " fmt, __FILE__, \
		      __LINE__, __FUNCTION__, __VA_ARGS__)

#define sd_log_info(fmt, ...)  _sd_log_handle(SD_LOG_INFO,  fmt, __VA_ARGS__)
#define sd_log_debug(fmt, ...) _sd_log_handle(SD_LOG_DEBUG, fmt, __VA_ARGS__)
#define sd_log_fail(fmt, ...)  _sd_log_handle(SD_LOG_ERROR, fmt, __VA_ARGS__)
#define sd_err(fmt, ...)       _sd_log_handle(SD_LOG_ERROR, fmt, __VA_ARGS__)

#else /* need GCC double hash to eat final comma */

/* insert file, line, function name & new line*/
#define _sd_log_handle(level, fmt, ...) \
       	sd_log_handle(level, "%s:%d (%s) " fmt, __FILE__, \
		      __LINE__, __FUNCTION__, ## __VA_ARGS__)

#define sd_log_info(fmt, ...)  _sd_log_handle(SD_LOG_INFO,  fmt, ## __VA_ARGS__)
#define sd_log_debug(fmt, ...) _sd_log_handle(SD_LOG_DEBUG, fmt, ## __VA_ARGS__)
#define sd_log_fail(fmt, ...)  _sd_log_handle(SD_LOG_ERROR, fmt, ## __VA_ARGS__)
#define sd_err(fmt, ...)       _sd_log_handle(SD_LOG_ERROR, fmt, ## __VA_ARGS__)

#endif

/* macros }}} */

/* log / err }}} */

/* func api }}} */

/* interface/object-oriented API {{{ */

/* Common interface members. {{{ */
#define sd_declare_common_members(tag) \
	void *data; \
	struct tag* (*copy)(struct tag *obj); \
	uint32_t (*n_byte)(struct tag *obj); \
	void (*free)(struct tag *obj)

/* For every interface an object implements,
 * it likely needs to have a single implementation of the actual object
 * methods (free, n_byte, copy) and then forward calls in the different
 * interfaces to these methods.
 *
 * Note that these assume that you've define a struct data & your
 * methods are data_{free,n_byte,copy}.
 */

#define sd_declare_tag_free(tag) \
static void tag ## _free(struct tag *tag) { data_free(tag->data); }

#define sd_declare_tag_n_byte(tag) \
static uint32_t tag ## _n_byte(struct tag *tag) { return data_n_byte(tag->data); }

#define sd_declare_tag_copy(tag) \
static struct tag *tag ## _ ## copy(struct tag *tag) \
{ \
	struct data *data = data_copy(tag->data); \
	return &data->tag; \
}

#define sd_declare_tag_functions(tag) \
sd_declare_tag_free(tag) \
sd_declare_tag_n_byte(tag) \
sd_declare_tag_copy(tag)

#define sd_declare_tag_vtable(tag) \
	.free = &tag ## _free, \
	.n_byte = &tag ## _n_byte, \
	.copy = &tag ## _copy

/* }}} */

/* connectivity {{{ */
struct sd_conn
{
	sd_declare_common_members(sd_conn);

	/*! Row-wise weighted sum w/ non-zeros of other sparse * mat w/ sparsity structure. */
	void (*row_wise_weighted_sum)(struct sd_conn *conn, double *values, double *sums);

	/*! Get the number of non-zero elements in weights. */
	uint32_t (*get_n_nonzero)(struct sd_conn *);

	/*! Get vector of non-zero weights. */
	double *(*get_weights)(struct sd_conn *);

	/*! Get vector of delays corresponding to non-zero weights. */
	double *(*get_delays)(struct sd_conn *);

	/*! Get the current scale of the delays*/
	double (*get_delay_scale)(struct sd_conn *);

	/*! Set the current scale of the delays*/
	enum sd_stat (*set_delay_scale)(struct sd_conn *, double);

	/*! Get the number of rows or targets in this connectivity. */
	uint32_t (*get_n_row)(struct sd_conn *conn);

	/*! Get the number of rows or targets in this connectivity. */
	uint32_t (*get_n_col)(struct sd_conn *conn);
};

/*! Construct a new connectivity from the given sparse data & structure. */
SD_API struct sd_conn *
sd_conn_new_sparse(
	uint32_t n_row, uint32_t n_col, uint32_t n_nonzero,
	uint32_t *row_offsets, uint32_t *col_indices,
	double *weights, double *delays
);

/*! Construct a new connectivity from dense data set. */
SD_API struct sd_conn *
sd_conn_new_dense(uint32_t n_row, uint32_t n_col, double * weights, double * delays);

/* connectivity }}} */

/* rng {{{ */

/**
 * Random number generator (RNG) interface.
 *
 * TODO get/set full state as bytestring
 */
struct sd_rng
{
	sd_declare_common_members(sd_rng);

	/*! Seed the RNG. */
	void (*seed)(struct sd_rng*, uint32_t seed);

	/*! Generate a single sample from N(0, 1). */
	double (*norm)(struct sd_rng*);

        /*! Generate a single sample on U(0, 1). */
        double (*uniform)(struct sd_rng*);

	/*! Generate and fill an array with samples from N(0, 1). */
	void (*fill_norm)(struct sd_rng*, uint32_t n, double *x);
};

/*! Construct a new Mersenne Twister RNG. */
SD_API struct sd_rng *
sd_rng_new_mt(uint32_t seed);

/* rng }}} */

/* hfill {{{ */

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

/* history }}} */

/* system {{{ */

/* TODO */
struct sd_sys_in
{ 
	uint32_t id, n_dim, n_in, n_out;
	double time, *state, *input; 
	struct sd_hist *hist;
	struct sd_rng *rng;
};

struct sd_sys_out
{ 
	double *drift, *diffusion, *output; 
};

/*! Interface for a system definition. */
struct sd_sys
{

	sd_declare_common_members(sd_sys);

	/*! Get the dimension of the system's state space. */
	uint32_t (*get_n_dim)(struct sd_sys *sys);

	/*! Get the number of delayed coupling terms used in the system definition. */
	uint32_t (*get_n_in)(struct sd_sys *sys);

	/*! Get the number of observable terms defined by system. */
	uint32_t (*get_n_out)(struct sd_sys *sys);

	/*! Get the number of real valued parameters used by system. */
	uint32_t (*get_n_rpar)(struct sd_sys *sys);

	/*! Get the number of integer valued parameters used by system. */
	uint32_t (*get_n_ipar)(struct sd_sys *sys);

	/**
	 * Apply system definition to state and input, calculating drift,
	 * diffusion and observable terms.
	 *
	 * \return SD_OK if calculation succeeds, SD_ERR if error occurs.
	 */
	enum sd_stat (*apply)(struct sd_sys *sys, struct sd_sys_in *in, struct sd_sys_out *out);
};

/*! Create new system based on user provided data & callback. */
SD_API struct sd_sys *
sd_sys_new_cb(
	uint32_t n_dim, uint32_t n_in, uint32_t n_out, 
	uint32_t n_rpar, uint32_t n_ipar,
	void *user_data,
	enum sd_stat (*user_apply)(void *, struct sd_sys_in*, struct sd_sys_out*));


/* system }}} */

/* neural mass model definitions {{{ */

#include "sys_exc.h"
#include "sys_gen2d.h"
#include "sys_rww.h"
#include "sys_hmje.h"

/* }}} */

/* net {{{ */

/**
 * Network interface.
 *
 * A network adapts existing system(s) into a network with a connectivity,
 * while also providing a system interface, so that it can be used with a scheme
 * like any other system.
 *
 * The network combines a connectivity with one or more system definitions. For
 * each node in the network, the mapping to/from connectivity entries is determined
 * by the number of coupling & observable terms of the subsystem for each node.
 *
 * For example, a network of 100 nodes, each having a sys with ndc=2 & nobs=3, would
 * have a connectivity size 200 x 300.
 *
 */
struct sd_net
{
	sd_declare_common_members(sd_net);

	/*! Get system interface for this network. */
	struct sd_sys * (*as_sys)(struct sd_net *net);

	/*! Get connectivity for this network. */
	struct sd_conn * (*get_conn)(struct sd_net *net);

	/*! Get number of nodes. */
	uint32_t (*get_n_node)(struct sd_net *net);

	/*! Get number of subsystems. */
	uint32_t (*get_n_subsys)(struct sd_net *net);

	/*! Get i'th subsystem. */
	struct sd_sys * (*get_subsys)(struct sd_net *net, uint32_t i);

	/*! Set i'th subsystem. */
	enum sd_stat (*set_subsys)(struct sd_net *net,
			uint32_t i_sys, struct sd_sys * sys);

	/*! Get subsystem index of i'th node. */
	uint32_t (*get_node_subsys)(struct sd_net *net, uint32_t i_node);

	/*! Set subsystem index of i'th node. */
	enum sd_stat (*set_node_subsys)(struct sd_net *net,
			uint32_t i_node, uint32_t i_sys);
};

/* TODO subsys list helper for bindings? */

/*!  Construct a new network object. */
SD_API struct sd_net *
sd_net_new(uint32_t n_node, uint32_t n_subsys, uint32_t *node_subsys_map, 
	   struct sd_sys **subsys,
	   struct sd_conn *conn);

/*! Create new instance of default region mapping / regions of interest. */
SD_API struct sd_sys *
sd_sys_roi_new(uint32_t n, uint32_t *map);

/* net }}} */

#include "output.h"

/* schemes {{{ */

/**
 * Interface to time-stepping schemes.
 *
 * \note Schemes create internal data structures which are cleaned
 * up during a call to the free method, however, the history, 
 * rng and sys structures are considered external and will not
 * be freed when the scheme is freed.
 */
struct sd_sch
{
	sd_declare_common_members(sd_sch);

	/*! Get the length of the state vector of this scheme. */
	uint32_t (*get_n_dim)(struct sd_sch *sch);

	/*! Get the length of the input vector of this scheme. */
	uint32_t (*get_n_in)(struct sd_sch *sch);

	/*! Get the length of the output vector of this scheme. */
	uint32_t (*get_n_out)(struct sd_sch *sch);

	/*! Get the time step of this scheme. */
	double (*get_dt)(struct sd_sch *sch);

	/*! Get current time. */
	double (*get_time)(struct sd_sch *sch);

	/*! Get current state vector. */
	double *(*get_state)(struct sd_sch *sch);

	/*! Get current input vector. */
	double *(*get_input)(struct sd_sch *sch);

	/*! Get current output vector. */
	double *(*get_output)(struct sd_sch *sch);

	/*! Get this scheme's hist instance. */
	struct sd_hist *(*get_hist)(struct sd_sch *);

	/*! Get this scheme's rng instance. */
	struct sd_rng *(*get_rng)(struct sd_sch *);

	/*! Get this scheme's sys instance. */
	struct sd_sys *(*get_sys)(struct sd_sch *);

	/*! Apply scheme. */
	enum sd_stat (*apply)(struct sd_sch *scheme, double *time,
			      double *state, double *output);
};

/*! Create new scheme based on user-provided data & callback. */
SD_API struct sd_sch *
sd_sch_new_cb(double dt,
	struct sd_sys *sys, struct sd_hist *hist, struct sd_rng *rng,
	void *user_data,
	enum sd_stat (*user_apply)(
		void *user_data, double *time,
		double *state, double *output));

/*! Create instance of the identity scheme, for difference equations. */
SD_API struct sd_sch *
sd_sch_new_id(struct sd_sys *sys, struct sd_hist *hist, struct sd_rng *rng);

/*! Create instance of Euler-Maruyama O(1) general purpose scheme. */
SD_API struct sd_sch *
sd_sch_new_em(double dt,
	struct sd_sys *sys, struct sd_hist *hist, struct sd_rng *rng);

/* Create instance of Euler-Maruyama O(1), specialized for colored noise,
 * derived from Fox 1998. Only for use with systems driven by additive noise.
 *
 * \param lam damping factor determining color; cf Fox et al 98.
 */
SD_API struct sd_sch * 
sd_sch_new_emc(double dt, double lam,
	struct sd_sys *sys, struct sd_hist *hist, struct sd_rng *rng);

/*! Create instance of Heun scheme, Manella 2002, additive noise. */
SD_API struct sd_sch *
sd_sch_new_heun(double dt,
	struct sd_sys *sys, struct sd_hist *hist, struct sd_rng *rng);

/* TODO http://arxiv.org/pdf/1506.05708v1.pdf LL for mult noise  */

/* TODO Kuechler & Platen semi-implicit Milstein for SDDEs */

/* sch }}} */

/* sol {{{ */

/**
 * Solver interface.
 *
 * A solver is responsible for iterating the discretized system,
 * as defined by a scheme instance, passing the results to the output
 * instance, as long as the out indicates the solution should continue.
 * The solver stops when indicated to do so by the return code of the
 * output's apply method, or when an error occurs.
 *
 * The provided solver is primarily a convenience, wrapping the time
 * stepping loop, for the user, but should more control be needed, the
 * individual components can be called in a custom loop.
 */
struct sd_sol
{
	sd_declare_common_members(sd_sol);

	/*! Get associated scheme object. */
	struct sd_sch * (*get_scheme)(struct sd_sol *sol);

	/*! Get associated out object */
	struct sd_out * (*get_out)(struct sd_sol *sol);

	/*! Continue stepping in time. */
	enum sd_stat (*cont)(struct sd_sol *sol);

	/*! Get current time in solution. */
	double (*get_time)(struct sd_sol *sol);
};

/* TODO initial conditions are more consistently specified through
 * the initial history function.
 */

/*! Create a new default solver instance. */
SD_API struct sd_sol *
sd_sol_new_default(double init_time, double *init_state,
		   struct sd_sch *scheme, struct sd_out *out);

/* sol }}} */

/* }}} */

/* vim: foldmethod=marker filetype=c
 */

