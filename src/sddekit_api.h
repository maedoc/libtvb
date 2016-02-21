/* copyright 2016 Apache 2 sddekit authors */

/**  SDDEKit API header, containing only definitions
 * of SDDEKit's API, usually for use by including in some
 * other header like sddekit.h or a simplified one for binding.
 */

#ifndef SDDEKIT_H
#include "prelude.h"
#endif

/* sddekit verion numbers */
uint32_t sd_ver_major();
uint32_t sd_ver_minor();

/**
 * Status codes used by various functions.
 */
typedef enum sd_stat {
	/*! Function call succeeded */
	SD_OK,
	/*! An error occurred during the function call or one of the functions it called. */
	SD_ERR,
	/*! Returned by output object to indicate solver should continue */
	SD_CONT,
	/*! Returned by output object to indicate solver should stop */
	SD_STOP,
	/*! Returned by function it dosen't know */
	SD_UNKNOWN
    } sd_stat;

/* utilities {{{ */

SD_API double
sd_arith_sum0(uint32_t n, double *x);

SD_API double
sd_arith_sum1(uint32_t n, double *x);

/**
 * Read a square matrix from file in ascii format into w.
 * \note w must be freed by user.
 * \param[in] fname string containing filename to readable file.
 * \param[out] n number of rows & cols.
 * \param[out] w matrix of weights.
 * \return SD_OK if succeeds, SD_ERR if error occurs..
 */
SD_API sd_stat 
sd_util_read_square_matrix(const char *fname, uint32_t *n, double **w);

/**
 * Obtain unique sorted integers.
 * \note Caller must free uints when done.
 * \param n number of elements
 * \param ints array of at least n integers.
 * \param[out] nuniq address of number of unique integers.
 * \param[out] uints address of array of unique integers.
 * \return Returns SD_OK if call succeeds, SD_ERR if error occurs.
 */
SD_API sd_stat 
sd_util_uniqi(uint32_t n,
	      uint32_t * restrict ints, 
	      uint32_t * restrict nuniq, 
	      uint32_t **uints);

/* util }}} */

/* rng {{{ */

/* Forward declare interface type for explicit use in signatures. */
typedef struct sd_rng sd_rng;

/**
 * Random number generator (RNG) interface.
 *
 * TODO save to file.
 */
struct sd_rng {
	void *ptr;
	/**
	 * Seed the RNG.
	 */
	void (*seed)(sd_rng*, uint32_t seed);
	/**
	 * Generate a single sample from N(0, 1).
	 */
	double (*norm)(sd_rng*);
        /**
         * Generate a single sample on U(0, 1).
         */
        double (*uniform)(sd_rng*);
	/**
	 * Generate and fill an array with samples from N(0, 1).
	 */
	void (*fill_norm)(sd_rng*, uint32_t n, double *x);
	/**
	 * Number of bytes used by this object.
	 */
	uint32_t (*nbytes)(sd_rng*);
	/**
	 * Free memory allocated for this RNG.
	 */
	void (*free)(sd_rng*);
};

/**
 * Construct a new RNG from default implementation.
 */
SD_API sd_rng *
sd_rng_new_default();

/* rng }}} */

/* hfill {{{ */

/* Forward declare interface type for explicit use in signatures. */
typedef struct sd_hfill sd_hfill;

/**
 * Interface for function to fill history buffer.
 */
struct sd_hfill {
	void *ptr;
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
	sd_stat (*apply)(sd_hfill*, uint32_t n, double * restrict t, uint32_t *indices,
		double * restrict buf);
	/**
	 * Free memory allocated for this sd_hfill instance.
	 */
	void (*free)(sd_hfill*);
};

/**
 * An sd_hfill instance which sets all elements of the history buffer
 * to a given value.
 */
SD_API sd_hfill *
sd_hfill_new_val(double val);

/* hfill }}} */

/* history {{{ */

/* Forward declare interface type for explicit use in signatures. */
typedef struct sd_hist sd_hist;

struct sd_hist {
	void *ptr;

	/**
	* Get the largest delayed variable index in history
	*
	* \param h initialized history instance.
	*/
	uint32_t(*get_maxvi)(sd_hist*);

	/**
	* Map a delayed variable index to its compact index.
	*
	* \param h initialized history instance.
	* \param vi index of variable
	* \return index of vi in unique(vi array).
	*/
	uint32_t(*get_vi2i)(sd_hist*, uint32_t vi);

        /**
         * Get vector of vi2i values.
         */
        uint32_t *(*get_vi2i_vec)(sd_hist *h);

	/**
	* Get the number of (unique) delayed variable indices.
	*
	* \param h initialized history instance.
	*/
	uint32_t(*get_nu)(sd_hist *h);

	/**
	* Free memory allocated for history instance.
	*
	* \param h allocated history instance.
	*/
	void (*free)(sd_hist *h);

	/**
	* Fill history buffer with some user defined function of time.
	*
	* \param h initialized history instance.
	* \param filler history filler.
	* \return SD_OK if fill succeeds, SD_ERR if error occurred.
	*/
	sd_stat (*fill)(sd_hist *h, sd_hfill *filler);

	/**
	* Get delayed data from history buffer.
	*
	* If a and e denote afferent and efferent coupling terms, then
	* this compute a[i] = e[vi[i]](t - vd[i]).
	*
	* \note len(aff) == nd
	*
	* \param[in,out] h history instance; if NULL, call is no-op.
	* \param[in] t current time.
	* \param[out] aff vector of afferent coupling terms, determined by vi/vd.
	*/
	void (*get)(sd_hist *h, double t, double *aff);

	/**
	* Update history buffer with new data.
	*
	* \note len(eff) == max(vi)
	*
	* \param[in,out] h history instance; if NULL, call is no-op.
	* \param[in] t current time.
	* \param[in] eff vector of efferent coupling terms, determined by system.
	*/
	void (*set)(sd_hist *h, double t, double *eff);

	/**
	 * \return number of bytes used by this history buffer.
	 */
	uint32_t (*nbytes)(sd_hist *h);

	/**
	* Get element of history buffer by linear index
	*
	* \param h history instance.
	* \param index linear index in buffer.
	*/
	double (*get_buf_lin)(sd_hist *h, uint32_t index);

	/**
	* Get number of delays in history.
	*/
	uint32_t (*get_nd)(sd_hist *h);

	/**
	* Get current time in history.
	*
	* \param h history instance.
	*/
	double (*get_t)(sd_hist *h);

	/**
	* Get time step of history buffer.
	*
	* \param h history instance.
	*/
	double (*get_dt)(sd_hist *h);

	/**
	* Get limit of variable storage in buffer.
	*
	* \param h history instance.
	* \param i index of limit.
	*/
	uint32_t (*get_lim)(sd_hist *h, uint32_t i);

	/**
	* Get length of variable storage in buffer.
	*
	* \param h history instance.
	* \param i index of limit.
	*/
	uint32_t (*get_len)(sd_hist *h, uint32_t i);

	/**
	* Get the current pos of delayed variable in buffer.
	*
	* \param h history instance.
	* \param i index of variable.
	*/
	uint32_t (*get_pos)(sd_hist *h, uint32_t i);

	/**
	* Get unique variable index.
	*
	* \param h history instance.
	* \param i index of variable.
	*/
	uint32_t (*get_uvi)(sd_hist *h, uint32_t i);

	/**
	* Get max delay for variable.
	*
	* \param h history instance.
	* \param i index of variable.
	*/
	double (*get_maxd)(sd_hist *h, uint32_t i);

	/**
	* Get variable index.
	*
	* \param h history instance.
	* \param i index of variable.
	*/
	uint32_t (*get_vi)(sd_hist *h, uint32_t i);

	/**
	* Get variable delay.
	*
	* \param h history instance.
	* \param i index of variable.
	*/
	double (*get_vd)(sd_hist *h, uint32_t i);

	/**
	* Get status of delay buffer.
	*
	* \note provided for unit tests, not generally useful.
	*
	* \param h history instance.
	*/
	bool (*buf_is_null)(sd_hist *h);

};

/**
 * Initialize an history instance.
 *
 * \param h an allocated history instance.
 * \param nd number of delayed coupling terms.
 * \param vi efferent index of each delayed coupling term.
 * \param vd delay of each delayed coupling term.
 * \param t0 starting time.
 * \param dt time-step to use in history buffer (need not equal solution dt).
 * \return initialized history instance or NULL if error occurs.
 */
SD_API sd_hist *
sd_hist_new_default(uint32_t nd, uint32_t *vi, 
		    double *vd, double t0, double dt);

/**
 * Initialize a history instance which ignores the given delays, but otherwise
 * conforms to the history interface.
 */ 
SD_API struct sd_hist *
sd_hist_new_no_delays(uint32_t nd, uint32_t *vi, double *vd, double t0, double dt);

/* history }}} */

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
 * return total bytes allocated by sd_malloc after register init.
 * return 0 if register not inititalized or no memory allocated after init.
 */

SD_API uint32_t
sd_malloc_total_nbytes();

/**
 * Free memory using current allocator.
 */

SD_API void
sd_free(void *ptr);

/* mem }}} */

/* system {{{ */

/* Structs used to simplify system interface
 *
 * Previous docs on system definition callback:
 *
 * The coupling term array has two uses. On entry to system callback,
 * the array contains elements for every delayed term defined using the
 * nc/vi/vd arguments to sd_sol_init, which are used to define the delayed
 * coupling structure of the system. On exit, the array should contain
 * values to be used/stored for delayed coupling. The array vi determines
 * the mapping from efferent coupling terms to afferent terms.
 *
 * \note The partial derivative terms F, G, Cf, Cg should only be set if
 * the scheme requires them; they will be NULL otherwise. F & G have a dense
 * nx x nx row-major matrix layout whereas Cf & Cg have the same sparse layout
 * as provided to the solver.
 *
 * \param data user data passed to system for defining e.g. parameters of the system.
 * \param hist history of system.
 * \param t current time in solution.
 * \param i index of system (relevant for composite systems).
 * \param nx number of state variables of system.
 * \param x vector of current state variable values.
 * \param f vector of drift terms per state variable.
 * \param f vector of diffusion terms per state variable.
 * \param F partial derivatives of drift terms with respect to x.
 * \param G partial derivatives of diffusion terms with respect to x.
 * \param nc number of coupling terms.
 * \param c vector of coupling terms.
 * \param Cf partial derivatives of drift terms with respect to c.
 * \param Cg partial derivatives of diffusion terms with respect to c.
 * \return 0 if system evaluation succeeded, 1 if error occurred.
 */
typedef struct sd_sys_in { 
	uint32_t nx, nc, id;
	double t, *x, *i; 
	sd_hist *hist;
	sd_rng *rng;
} sd_sys_in;

typedef struct sd_sys_out { 
	double *f, *g, *o; 
} sd_sys_out;

/* Forward declare interface type for explicit use in signatures. */
typedef struct sd_sys sd_sys;

/**
 * Interface for a system definition.
 */
struct sd_sys {

	/**
	 * Get the dimension of the system's state space.
	 */
	uint32_t (*ndim)(sd_sys*);

	/**
	 * Get the number of delayed coupling terms used in the system definition.
	 */
	uint32_t (*ndc)(sd_sys*);

	/**
	 * Get the number of observable terms defined by system.
	 */
	uint32_t (*nobs)(sd_sys*);

	/**
	 * Get the number of real valued parameters used by system.
	 */
	uint32_t (*nrpar)(sd_sys*);

	/**
	 * Get the number of integer valued parameters used by system.
	 */
	uint32_t (*nipar)(sd_sys*);

	/**
	 * Apply system definition to state and input, calculating drift,
	 * diffusion and observable terms.
	 *
	 * \return SD_OK if calculation succeeds, SD_ERR if error occurs.
	 */
	sd_stat (*apply)(sd_sys*, sd_sys_in*, sd_sys_out*);

	/**
	 * \return number of bytes used by this system instance.
	 */
	uint32_t (*nbytes)(sd_sys*);

	/**
	 * Free memory allocated for this system instance.
	 */
	void (*free)(sd_sys*);

	void *ptr;
};

/**
 * Create new system based on user provided data & callback.
 */
SD_API sd_sys *
sd_sys_new_cb(uint32_t ndim, uint32_t ndc, uint32_t nobs, 
	uint32_t nrpar, uint32_t nipar,
	void *user_data,
	sd_stat (*user_apply)(void *, sd_sys_in*, sd_sys_out*));


/* system }}} */

/* exc {{{ */

/* Forward declare interface type for explicit use in signatures. */
typedef struct sd_sys_exc sd_sys_exc;

/**
 * Interface for the Excitator system.
 */
struct sd_sys_exc {

	void *ptr;

	/**
	 * Get system definition for an Excitator instance.
	 */
	sd_sys *(*sys)(sd_sys_exc*);

	/**
	 * Get the a parameter value.
	 *
	 * \param d Excitator system instance.
	 */
	double (*get_a)(sd_sys_exc *d);

	/**
	 * Set the a parameter value.
	 *
	 * \param d Excitator system instance.
	 * \param new_a new value of a.
	 */
	void (*set_a)(sd_sys_exc *d, double new_a);

	/**
	 * Get the tau parameter value.
	 *
	 * \param d Excitator system instance.
	 */
	double (*get_tau)(sd_sys_exc *d);

	/**
	 * Set the tau parameter value.
	 *
	 * \param d Excitator system instance.
	 * \param new_tau new value of tau.
	 */
	void (*set_tau)(sd_sys_exc *d, double new_tau);

	/**
	 * Get the D parameter value.
	 *
	 * \param d Excitator system instance.
	 */
	double (*get_D)(sd_sys_exc *d);

	/**
	 * Set the D parameter value.
	 *
	 * \param d Excitator system instance.
	 * \param new_D new value of D.
	 */
	void (*set_D)(sd_sys_exc *d, double new_D);

	/**
	 * Get the k parameter value.
	 *
	 * \param d Excitator system instance.
	 */
	double (*get_k)(sd_sys_exc *d);

	/**
	 * Set the k parameter value.
	 *
	 * \param d Excitator system instance.
	 * \param new_k new value of k.
	 */
	void (*set_k)(sd_sys_exc *d, double new_k);

};

/**
 * Create new instance of the Excitator system.
 */
SD_API sd_sys_exc *
sd_sys_exc_new();

/* exc }}} */

#include "gen2d.h"
#include "rww.h"
#include "hmje.h"

/* net {{{ */

/* network
 * \brief sd_net provides a sd_sys which adapts another sd_sys into a network.
 *
 * The solver & scheme sees the network as just another 
 * system to solve, and the network structure is handled here, not in the
 * solver.
 *
 * We consider in general n nodes and m mass models. The i'th node has model 
 * M[i], with Ms[i] state variables and Me[i] efferent variables. ns = 
 * sum(Ms[i],i,1,n) is the total number of state variables, and ne = 
 * sum(Me[i],i,1,n) respectively efferent variables. x in R^ns is the 
 * state of the network, and ce in R^ne the efferent activity.
 *
 * Connectivity in the network is a sparse R^ne x R^ne matrix, where
 * w in R^nnz is the non-zero weights and d in R^nnz
 * the delays. The non-zero elements are located by Or in N^(n+1) row 
 * offsets and Ic in N^nnz column indices, in so-called CSR format.
 * 
 * The historian requires Ic in N^nnz indices on ce, and 
 * d in R^nnz delay vector, also passed for initializing a network.
 *
 * Computing net afferent cna in R^ne from sys aff ca in R^nnz following
 * the sparse connectivity.
 * 
 * scheme provides ca from history, expects ce, we need to map these
 * sparse needs n, row offsets col indices and data
 *
 */

/* Forward declare interface type for explicit use in signatures. */
typedef struct sd_net sd_net;

/**
 * Network interface.
 */
struct sd_net {
	void *ptr;

	/**
	 * Get system interface for this network.
	 */
	sd_sys * ( * sys)(sd_net *d);

	/**
	 * \return number of bytes used by this network.
	 */
	uint32_t (*nbytes)(sd_net *d);

	/**
	 * Free memory allocated for this network.
	 *
	 * \note assumes each of the node data themselves have been freed.
	 *
	 * \param d network data.
	 */
	void (*free)(sd_net *d);

	/**
	 * Get number of nodes in network.
	 *
	 * \param net network instance.
	 */
	uint32_t (*get_n)(sd_net *net);

	/**
	 * Get number of models in network.
	 *
	 * \param net network instance.
	 */
	uint32_t (*get_m)(sd_net *net);

	/**
	 * Get number of non-zero weights and delays in network.
	 *
	 * \param net network instance.
	 */
	uint32_t (*get_nnz)(sd_net *net);

	/**
	 * Get non-zero row offset vector.
	 *
	 * \param net network instance.
	 */
	uint32_t *(*get_or)(sd_net *net);

	/**
	 * Get i'th non-zero row offset.
	 *
	 * \param net network instance.
	 * \param i index.
	 */
	uint32_t (*get_or_i)(sd_net *net, uint32_t i);

	/**
	 * Get non-zero column index vector.
	 *
	 * \param net network instance.
	 */
	uint32_t *(*get_ic)(sd_net *net);

	/**
	 * Get i'th non-zero column index.
	 *
	 * \param net network instance.
	 * \param i index.
	 */
	uint32_t (*get_ic_i)(sd_net *net, uint32_t i);

	/**
	 * Get non-zero weight vector.
	 *
	 * \param net network instance.
	 */
	double *(*get_w)(sd_net *net);

	/**
	 * Get the i'th non-zero weight.
	 *
	 * \param net network instance.
	 */
	double (*get_w_i)(sd_net *net, uint32_t i);

	/**
	 * Get non-zero delay vector.
	 *
	 * \param net network instance.
	 */
	double *(*get_d)(sd_net *net);

	/**
	 * Get the i'th non-zero delay.
	 *
	 * \param net network instance.
	 */
	double (*get_d_i)(sd_net *net, uint32_t i);

	/**
	 * Get total number of state variables in network.
	 *
	 * \param net network instance.
	 */
	uint32_t (*get_ns)(sd_net *net);

	/**
	 * Get total number of efferent variables in network.
	 *
	 * \param net network instance.
	 */
	uint32_t (*get_ne)(sd_net *net);

	/**
	 * Get NULL status of cn
	 * \note provided for unit testing.
	 * \param net network instance.
	 */
	bool (*cn_is_null)(sd_net *net);

	/**
	 * Get number of state variables fot the i'th model.
	 *
	 * \param net network instance.
	 * \param i index.
	 */
	uint32_t (*get_Ms_i)(sd_net *net, uint32_t i);

	/**
	 * Get number of afferent variables fot the i'th model.
	 *
	 * \param net network instance.
	 * \param i index.
	 */
	uint32_t (*get_Ma_i)(sd_net *net, uint32_t i);

	/**
	 * Get number of efferent variables fot the i'th model.
	 *
	 * \param net network instance.
	 * \param i index.
	 */
	uint32_t (*get_Me_i)(sd_net *net, uint32_t i);

	/**
	 * Get model index for i'th node.
	 *
	 * \param net network instance.
	 * \param i index.
	 */
	uint32_t (*get_M_i)(sd_net *net, uint32_t i);

	/**
	 * Get i'th model.
	 *
	 * \param net network instance.
	 * \param i index.
	 */
	sd_sys * (*get_models_i)(sd_net *net, uint32_t i);

	bool (*get__init1)(sd_net *net);

};

/**
 * Create new instance of default network implementation.
 *
 * Init network for general case of heterogeneous network of nm different models
 *
 * \note Further use requires filling data structures.
 *
 * \param d network to initialize.
 * \param n number of nodes in network.
 * \param m number of models used in network.
 * \param nnz number of non-zero elements in weights matrix.
 * \param w array of non-zero elements of weights matrix.
 * \param d array of delays per non-zero weight.
 * \return 0 on success, 1 if error occurred.
 */
SD_API sd_net*
sd_net_new_het(uint32_t n, uint32_t m, uint32_t * restrict M, uint32_t * restrict Ms, 
	       uint32_t * restrict Ma, uint32_t * restrict Me, 
	       sd_sys **models,
	       uint32_t nnz, uint32_t * restrict Or, uint32_t * restrict Ic, 
		   double * restrict w, double * restrict d);

/**
 * Init network for homogeneous model case where m==1, simplifying setup.
 *
 * \param n number of nodes in network.
 * \param sys model system to use.
 * \param ns number of state variables for system.
 * \param na number of afferent terms for system.
 * \param ne number of efferent terms for system.
 * \param nnz number of non-zero elements in weights matrix.
 * \param Or array of row offsets in non-zero arrays.
 * \param Ic array of column indices in non-zero arrays.
 * \param w array of non-zero elements of weights matrix.
 * \param d array of delays per non-zero weight.
 */
SD_API sd_net *
sd_net_new_hom(uint32_t n, sd_sys *sys,
	uint32_t ns, uint32_t na, uint32_t ne, uint32_t nnz, 
	uint32_t * restrict Or,
	uint32_t * restrict Ic, 
	double * restrict w,
	double * restrict d);

/* net }}} */

/**
 * Create new instance of default region mapping / regions of interest.
 */
SD_API sd_sys *
sd_roi_new_default(uint32_t n, uint32_t *map);

/* output {{{ */

/* Forward declare interface type for explicit use in signatures. */
typedef struct sd_out sd_out;

/**
 * Interface for outputs.
 */
struct sd_out {

	void *ptr;

	/**
	 * Free memory allocated for this output instance.
	 */
	void (*free)(sd_out *);

	/**
	 * \return number of bytes used by this output instance.
	 */
	uint32_t (*nbytes)(sd_out *);

	/**
	 * Apply output to current state.
	 * \param data user data for output function such as simulation length.
	 * \param t current time.
	 * \param nx number of state variables.
	 * \param x state variable vector.
	 * \param nc number of coupling terms.
	 * \param c coupling term vector.
	 * \return SD_OK if the solver should continue, SD_ERR if 
	 * error occurred, and SD_STOP if solution should stop.
	 */
	sd_stat (*apply)(sd_out *, double t, 
			     uint32_t nx, double * restrict x,
			     uint32_t nc, double * restrict c);

};

/**
 * Create new out based on user provided data & callback.
 */
SD_API sd_out *
sd_out_new_cb(void *user_data,
	sd_stat (*user_apply)(void *, double t, 
	     uint32_t nx, double * restrict x,
	     uint32_t nc, double * restrict c));

/* Forward declare interface type for explicit use in signatures. */
typedef struct sd_out_file sd_out_file;

/**
 * Interface for file-based outputs.
 */
struct sd_out_file {

	void *ptr;

	/**
	 * Get interface for output.
	 */
	sd_out * ( * out)(sd_out_file *);

	/**
	 * Query whether file output is on stdout stderr.
	 *
	 * \param d file output instance
	 * \return 1 if is stdout or stderr, 0 if normal file or d is NULL.
	 */
	bool (*is_std)(sd_out_file *d);

	/**
	 * Get file pointer.
	 *
	 * \param d file output instance.
	 * \return file stream or NULL.
	 */
	FILE *(*get_fd)(sd_out_file *d);

};

/**
 * Create a new file output for file name.
 *
 * \param d file output instance.
 * \param fname path to file with write permissions.
 */
SD_API sd_out_file *
sd_out_file_new_from_name(char *fname);

/**
 * Initialize file output from stdout or stderr.
 *
 * \param d file output instance.
 * \param std stdout or stderr.
 */
SD_API sd_out_file *
sd_out_file_new_from_std(FILE *std);

/* Forward declare interface type for explicit use in signatures. */
typedef struct sd_out_mem sd_out_mem;

/**
 * Interface for auto-allocating array output.
 */
struct sd_out_mem {

	void *ptr;

	/**
	 * Get interface for output.
	 */
	sd_out * ( * out)(sd_out_mem *);

	/**
	 * Get number of state variables in memory buffer.
	 *
	 * \param d memory output instance.
	 * \return number of state variables.
	 */
	uint32_t (*get_nx)(sd_out_mem *d);

	/**
	 * Get number of coupling variables in memory buffer.
	 *
	 * \param d memory output instance.
	 * \return number of coupling variables.
	 */
	uint32_t (*get_nc)(sd_out_mem *d);

	/**
	 * Get number of samples in memory buffer.
	 *
	 * \param d memory output instance.
	 * \return number of samples.
	 */
	uint32_t (*get_n_sample)(sd_out_mem *d);

	/**
	 * Get capacity in number of samples in memory buffer.
	 *
	 * \param d memory output instance.
	 * \return capacity of buffer.
	 */
	uint32_t (*get_capacity)(sd_out_mem *d);

	/**
	 * Get state variable buffer.
	 *
	 * \param d memory output instance.
	 * \return pointer to buffer, not to be modified or free'd by user.
	 */
	double *(*get_xs)(sd_out_mem *d);

	/**
	 * Get coupling variable buffer.
	 *
	 * \param d memory output instance.
	 * \return pointer to buffer, not to be modified or free'd by user.
	 */
	double *(*get_cs)(sd_out_mem *d);

};

/**
 * Create new output memory buffer.
 */
SD_API sd_out_mem *
sd_out_mem_new();

/* Forward declare interface type for explicit use in signatures. */
typedef struct sd_out_tee sd_out_tee;

/**
 * Interface for splitter output
 */
struct sd_out_tee {

	void *ptr;

	/**
	 * Get out interface for this instance.
	 */
	sd_out * ( * out)(sd_out_tee *);

	/**
	 * Get number of outputs for splitter.
	 *
	 * \param d splitter output instance.
	 * \return number of outputs.
	 */
	uint32_t (*get_nout)(sd_out_tee *);

	/**
	 * Get NULL status of out callback array.
	 *
	 * \param d splitter output instance.
	 * \return 1 if output callback array is NULL.
	 */
	bool (*outs_is_null)(sd_out_tee *);

	/**
	 * Set i'th output of splitter.
	 *
	 * \param d splitter instance.
	 * \param i output index.
	 * \param out i'th output callback.
	 * \param data i'th output user data.
	 * \return 0 if success, 1 if error occurs.
	 */
	sd_stat (*set_out)(sd_out_tee *, uint32_t i, sd_out *out);

	/**
	 * Get i'th output callback.
	 *
	 * \param d splitter instance.
	 * \param i output index.
	 * \return i'th output callback, or NULL if i out of bounds.
	 */
	sd_out *(*get_out)(sd_out_tee *, uint32_t i);

};

/**
 * Create instance of output splitter.
 *
 * \param nout number of outputs to distribute to.
 */
SD_API sd_out_tee *
sd_out_tee_new(uint32_t nout);

/**
 * Interface for temporal average out.
 */
/* Forward declare interface type for explicit use in signatures. */
typedef struct sd_out_tavg sd_out_tavg;

struct sd_out_tavg {

	void *ptr;

	/**
	 * Get interface for output.
	 */
	sd_out * ( * out)(sd_out_tavg *);

	/**
	 * Get number of samples used for temporal average output.
	 */
	uint32_t (*get_len)(sd_out_tavg *d);

	/**
	 * Get current positon in buffer of temporal average output.
	 */
	uint32_t (*get_pos)(sd_out_tavg *d);

	/**
	 * Get current time in buffer of temporal average output.
	 */
	double (*get_t)(sd_out_tavg *d);

	/**
	 * Get output to which temporal average will be passed.
	 */
	sd_out * (*get_out)(sd_out_tavg *d);

	/**
	 * Get average state variables of temporal average output.
	 */
	double *(*get_x)(sd_out_tavg *d);

	/**
	 * Get average coupling variables of temporal average output.
	 */
	double *(*get_c)(sd_out_tavg *d);

};

/**
 * Create instance of temporal average output.
 *
 * \param len number of samples used for averagíng.
 * \param out output to pass averaged data to.
 */
SD_API sd_out_tavg *
sd_out_tavg_new(uint32_t len, sd_out *out);

/* Forward declare interface type for explicit use in signatures. */
typedef struct sd_out_conv sd_out_conv;

struct sd_out_conv {
    void *ptr;

    /**
     * Get interface for output.
     */
    sd_out *(*out)(sd_out_conv *);

    /**
     * Free memory allocated for this object.
     */
    void (*free)(sd_out_conv*);

    /**
     * Get current position in buffers.
     */
    uint32_t (*get_pos)(sd_out_conv *);

    /**
     * Get length of filter / kernel.
     */
    uint32_t (*get_len)(sd_out_conv *);

    /**
     * Get subsampling factor.
     */
    uint32_t (*get_ds)(sd_out_conv *);

    /**
     * Get number of samples consumed before next sample produced.
     */
    uint32_t (*get_ds_count)(sd_out_conv *);

    /**
     * Get sd_out instance to which samples are passed.
     */
    sd_out * (*get_next_out)(sd_out_conv *);

    /* TODO consider the following for sd_out interface */

    /**
     * Get number of elements in state vector.
     */
    uint32_t (*get_nx)(sd_out_conv *);

    /**
     * Get number of elements in coupling vector.
     */
    uint32_t (*get_nc)(sd_out_conv *);

};

/**
 * Create instance of temporal convolution output.
 *
 * \param len length of filter
 * \param filt coefficients of filter
 * \param out output to pass convolution samples to.
 * \return instance of sd_out_conv or NULL if error occurred.
 */
SD_API sd_out_conv *
sd_out_conv_new(uint32_t len, double *filt, sd_out *out);

/* Various convolution kernels */

/**
 * Glover 1999 double-gamma HRF kernel, based on NiPy.
 *
 * \param[in] n number of time points
 * \param[in] dt time step between HRF samples.
 * \param[out] x values of HRF at time points in t.
 */
SD_API void sd_hrf_glover(uint32_t n, double dt, double *x);

/**
 * First-order Volterra HRF kernel, based on TVB.
 *
 * \param[in] n number of time points.
 * \param[in] dt time step between HRF samples.
 * \param[out] x values of HRF at time points in t.
 */
SD_API void sd_hrf_volt1(uint32_t n, double dt, double *x);

/* Forward declare interface type for explicit use in signatures. */
typedef struct sd_out_sfilt sd_out_sfilt;

/**
 * Interface for spatial filter bank output.
 */
struct sd_out_sfilt {

	void *ptr;

	/**
	 * Get out interface for this instance.
	 */
	sd_out * ( * out)(sd_out_sfilt *);

	/**
	 * Get number of filters of spatial filter output.
	 */
	uint32_t (*get_nfilt)(sd_out_sfilt *d);

	/**
	 * Get length of filters of spatial filter output.
	 */
	uint32_t (*get_filtlen)(sd_out_sfilt *d);

	/**
	 * Get coefficients of state variable filter of spatial filter output.
	 */
	double *(*get_xfilts)(sd_out_sfilt *d);

	/**
	 * Get coupling variable filter of spatial filter output.
	 */
	double *(*get_cfilts)(sd_out_sfilt *d);

	/**
	 * Get current values of spatially filtered state variables  of spatial filter output.
	 */
	double *(*get_x)(sd_out_sfilt *d);

	/**
	 * Get current values of spatially filtered coupling variables of spatial filter output.
	 */
	double *(*get_c)(sd_out_sfilt *d);

	/**
	 * Get output callback of spatial filter output.
	 */
	sd_out *(*get_out)(sd_out_sfilt *d);

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
SD_API sd_out_sfilt *
sd_out_sfilt_new(uint32_t nfilt, uint32_t filtlen, 
	double * restrict xfilts, double * restrict cfilts, 
	sd_out *out);

/**
 * Create new out for stopping after certain time.
 */
SD_API sd_out *
sd_out_new_until(double time);

/**
 * Create new out for ignoring x or c.
 */
SD_API sd_out *
sd_out_new_ign(bool ignore_x, bool ignore_c, struct sd_out *next);

/* out }}} */

/* sch {{{ */

/* Forward declare sd_sch so signatures may reference the type explicitly. */
typedef struct sd_sch sd_sch;

/**
 * Interface to time-stepping schemes.
 */
struct sd_sch {

	void *ptr;

	/**
	 * Get the number of state variables for which this scheme has memory
	 * allocated.
	 *
	 * \param d scheme instance.
	 * \return number of state variables
	 */
	uint32_t (*get_nx)(sd_sch *);

	/**
	 * Apply scheme.
	 *
	 * \param data user data for scheme such as storage for intermediate steps.
	 * \param hist history instance.
	 * \param rng random number generator state.
	 * \param sys system being solved.
	 * \param sysd user data for system.
	 * \param t current time.
	 * \param dt current time step to use.
	 * \param nx number of state variables.
	 * \param x state variable vector.
	 * \param nc number of coupling variables.
	 * \param c coupling variable vector.
	 * \return SD_OK if scheme succeeded, SD_ERR if error occurred.
	 */
	sd_stat (*apply)(sd_sch *, sd_hist *, sd_rng *, sd_sys *,
		double t, double dt, 
		uint32_t nx, double * restrict x,
		uint32_t nc, double * restrict c);

	/**
	 * \return number of bytes used for this scheme.
	 */
	uint32_t (*nbytes)(sd_sch *);

	/**
	 * Free memory allocated for this scheme.
	 */
	void (*free)(sd_sch *);
};


/**
 * Create new scheme based on user-provided data & callback.
 */
SD_API sd_sch *
sd_sch_new_cb(uint32_t nx, void *user_data,
	sd_stat (*user_apply)(void *, sd_hist *, sd_rng *, sd_sys *,
		double t, double dt, 
		uint32_t nx, double * restrict x,
		uint32_t nc, double * restrict c)
	);

/**
 * Create instance of the identity scheme
 *
 * The identity schemes updates the state following f & g directly, i.e.
 *
 * x_{t+1} = f(x_t) + g(x_t) * z
 *
 * This is useful for difference equations, for example.
 *
 * \param d allocated scheme instance.
 * \param nx number of state variables.
 */
SD_API sd_sch *
sd_sch_new_id(uint32_t nx);

/* Create instance of Euler-Maruyama O(1) general purpose scheme.
 *
 * \param nx number of state variables.
 */
SD_API sd_sch *
sd_sch_new_em(uint32_t nx);

/* Create instance of Euler-Maruyama O(1), specialized for colored noise,
 * derived from Fox 1998. Only for use with systems driven by additive noise.
 *
 * \param nx number of state variables.  
 * \param lam damping factor determining color; cf Fox et al 98.
 */
SD_API sd_sch * 
sd_sch_new_emc(uint32_t nx, double lam);

/**
 * Get the current value of lambda, the characteristic decorrelation time.
 *
 * \note Argument sch MUST be an instance of sd_sch created by sd_sch_new_emc.
 *
 * \param sch scheme instance.
 * \return current value of lambda.
 */
double sd_sch_emcolor_get_lam(sd_sch *sch);

/* Create instance of Heun scheme, due to Manella 2002, only for use
 * with systems driven by additive noise.
 *
 * \param nx number of state variables.
 */
SD_API sd_sch *
sd_sch_new_heun(uint32_t nx);

/* TODO http://arxiv.org/pdf/1506.05708v1.pdf LL for mult noise  */

/* TODO Kuechler & Platen semi-implicit Milstein for SDDEs */

/* sch }}} */

/* sol {{{ */

/* Forward declare sd_sol so signatures may reference the type explicitly. */
typedef struct sd_sol sd_sol;

/**
 * Interface to solver.
 */
struct sd_sol {

	void *ptr;

	/**
	 * Frees memory occupied by solver instance.
	 *
	 * \param s allocated solver instance.
	 */
	void (*free)(sd_sol *s);

	/**
	 * \return number of bytes used by this solver instance.
	 */
	uint32_t (*nbytes)(sd_sol *s);

	/**
	 * Continue stepping in time until one or more outputs returns 0 to stop.
	 *
	 * \note An error during execution of output callback is not currently distinct
	 * from an indication by the output callback to stop the solution.
	 *
	 * \param s initialized solver instance.
	 * \return SD_OK if continuation succeeds, SD_ERR if error occurs.
	 */
	sd_stat (*cont)(sd_sol *s);

	/**
	 * Get number of state variables.
	 *
	 * \param s solver instance.
	 */
	uint32_t (*get_nx)(sd_sol *s);

	/**
	 * Get number of coupling variables emit by system.
	 *
	 * \param s solver instance.
	 */
	uint32_t (*get_nce)(sd_sol *s);

	/**
	 * Get number of coupling variables accepted by system.
	 *
	 * \param s solver instance.
	 */
	uint32_t (*get_nca)(sd_sol *s);

	/**
	 * Get history instance or NULL if no delayed terms in solution.
	 *
	 * \param s solver instance.
	 */
	sd_hist *(*get_hist)(sd_sol *s);

	/**
	 * Get rng instance.
	 *
	 * \param s solver instance.
	 */
	sd_rng *(*get_rng)(sd_sol *s);

	/**
	 * Get current time in solution.
	 *
	 * \param s solver instance.
	 */
	double (*get_t)(sd_sol *s);

	/**
	 * Get current state vector in solution.
	 *
	 * \param s solver instance.
	 */
	double *(*get_x)(sd_sol *s);

	/**
	 * Get current coupling vector in solution.
	 *
	 * \param s solver instance.
	 */
	double *(*get_c)(sd_sol *s);
};

/**
 * Create a new default solver instance.
 *
 * \param sys system to be integrated.
 * \param scheme time-stepping scheme to use for solution.
 * \param out output handler.
 * \param hf history filler.
 * \param seed seed for random number generation.
 * \param nx number of state variables.
 * \param x0 initial state at t = 0.
 * \param nce number of coupling variables emit by system.
 * \param nca number of coupling variables accpted by system.
 * \param vi indices of coupling variables (length nca).
 * \param vd delays of coupling variables (length nca, strictly positive).
 * \param t0 starting time.
 * \param dt time step.
 */
SD_API sd_sol *
sd_sol_new_default(
	sd_sys *sys, sd_sch *scheme, sd_out *out, sd_hfill *hf,
	uint32_t seed, uint32_t nx, double * restrict x0, uint32_t nce,
	uint32_t nca, uint32_t * restrict vi, double * restrict vd, double t0, double dt);

/* sol }}} */

/* sparse {{{ */

/* sparse
 *
 * Provides utilities for sparse structures, such as matrices which are 
 * mostly zero.
 */

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
SD_API sd_stat 
sd_sparse_from_dense(
	uint32_t m, uint32_t n, 
	double *dA, double *dB, double eps,
	uint32_t *nnz, uint32_t **Or, uint32_t **Ic, 
	double **sA, double **sB);

/* sparse }}} */

/* logging  {{{
 *
 * \file sd_log.h implements handlers for information, debugging output
 * and error messages. Messages may be redirected to custom handlers.
 */

/**
 * Type definition for callback handling formatted messages.
 */
typedef int (*sd_log_msg_fp)(const char *fmt, ...);

extern sd_log_msg_fp sd_log_msg;

/**
 * Get function pointer handling messages.
 */
SD_API sd_log_msg_fp sd_log_get_msg();

/**
 * Set function pointer handling messages.
 */
SD_API void sd_log_set_msg(sd_log_msg_fp fp);

/**
 * Get status of quiet flag.
 */
SD_API bool sd_log_is_quiet();

/**
 * Set status of quiet flag.
 */
SD_API void sd_log_set_quiet(bool flag);

/**
 * Get status of verbose flag.
 */
SD_API bool sd_log_is_verbose();

/**
 * Set status of verbose flag.
 */
SD_API void sd_log_set_verbose(bool flag);

/**
 * Define logging macros differently depending on the compiler being used.
 */

/* use color when available */
#define SD_KNRM  "\x1B[0m"
#define SD_KRED  "\x1B[31m"
#define SD_KGRN  "\x1B[32m"
#define SD_KYEL  "\x1B[33m"
#define SD_KBLU  "\x1B[34m"
#define SD_KMAG  "\x1B[35m"
#define SD_KCYN  "\x1B[36m"
#define SD_KWHT  "\x1B[37m"
#define SD_RESET "\033[0m"

#ifdef _MSC_VER
#ifdef mex_h
#define sd_log_info(fmt, ...) if (!sd_log_is_quiet()) \
	sd_log_msg("[INFO] <a href=\"matlab: opentoline('%s', %d)\">%s:%d</a> (%s) " fmt "\n", __FILE__, __LINE__, __FILE__, __LINE__, __FUNCTION__, __VA_ARGS__)
#define sd_log_debug(fmt, ...) if (sd_log_is_verbose()) \
	sd_log_msg("[DEBUG] <a href=\"matlab: opentoline('%s', %d)\">%s:%d</a> (%s) " fmt "\n", __FILE__, __LINE__, __FILE__, __LINE__, __FUNCTION__, __VA_ARGS__)
#define sd_log_fail(fmt, ...) \
	sd_log_msg("[FAIL] <a href=\"matlab: opentoline('%s', %d)\">%s:%d</a> (%s) " fmt "\n", __FILE__, __LINE__, __FILE__, __LINE__, __FUNCTION__, __VA_ARGS__)
#else /* not mex_h */
#define sd_log_info(fmt, ...) if (!sd_log_is_quiet()) \
	sd_log_msg("[INFO] %s:%d (%s) " fmt "\n", __FILE__, __LINE__, __FUNCTION__, __VA_ARGS__)
#define sd_log_debug(fmt, ...) if (sd_log_is_verbose()) \
	sd_log_msg("[DEBUG] %s:%d (%s) " fmt "\n", __FILE__, __LINE__, __FUNCTION__, __VA_ARGS__)
#define sd_log_fail(fmt, ...) \
	sd_log_msg("[FAIL] %s:%d (%s) " fmt "\n", __FILE__, __LINE__, __FUNCTION__, __VA_ARGS__)
#endif /* ifdef mex_h */
#else /* use GCC double hash to eat final comma */
#define sd_log_info(fmt, ...) if (!sd_log_is_quiet()) \
	sd_log_msg(SD_KGRN "[INFO]" SD_KBLU " %s:%d (%s) " SD_RESET fmt "\n", __FILE__, __LINE__, __func__, ## __VA_ARGS__)
#define sd_log_debug(fmt, ...) if (sd_log_is_verbose()) \
	sd_log_msg(SD_KYEL "[DEBUG]" SD_KBLU " %s:%d (%s) " SD_RESET fmt "\n", __FILE__, __LINE__, __func__, ## __VA_ARGS__)
#define sd_log_fail(fmt, ...) \
	sd_log_msg(SD_KRED "[FAIL]" SD_KBLU " %s:%d (%s) " SD_RESET fmt "\n", __FILE__, __LINE__, __func__, ## __VA_ARGS__)
#endif

/* log }}} */

/* error handling {{{ */

/**
 * Typedef for error handler callback.
 *
 * \param err error number.
 * \param file file name where error originates.
 * \param line line number in file where error originates.
 * \param reason description of error.
 */
typedef void (*sd_err_handler_fp)(int err, char *file, int line, char *func, char *reason);

/**
 * The default error handler logs the error in the debug log.
 */
void sd_err_default_handler(int err, char *file, int line, char *func, char *reason);

/**
 * Get the current error handler.
 */
sd_err_handler_fp sd_err_get_handler();

/**
 * Set the current error handler.
 *
 * \param fp new handler. if NULL, errors will be unhandled.
 */
void sd_err_set_handler(sd_err_handler_fp fp);

/**
 * Dispatches error to current error handler.
 */
void sd_err_handler(int err, char *file, int line, char *func, char *reason);

/**
 * Handle an error.
 * 
 * \param reason description of error
 */
#define sd_err(reason) sd_err_handler(SD_ERR, __FILE__, __LINE__, (char *) __func__, reason);

/* err }}} */

/* vim: foldmethod=marker
 */

