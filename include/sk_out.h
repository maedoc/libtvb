/* Apache 2.0 INS-AMU 2015 */

#ifndef SK_OUT_H
#define SK_OUT_H

#include <stdio.h>

#include "sk_util.h"

#ifdef __cplusplus
extern "C" {
#endif

/** SK_DEFOUT aids in creating a new output definition.
 * See ::sk_out for details of the generated output callback signature.
 *
 * \param name name of output callback being defined.
 */
#define SK_DEFOUT(name) int name(void * restrict data,\
		double t,\
		int nx, double * restrict x,\
		int nc, double * restrict c)

/**
 * Callback signature expected by solver framework for output callbacks.
 * Use #SK_DEFOUT to declare or define a new output callback.
 *
 * \param data user data for output function such as simulation length.
 * \param t current time.
 * \param nx number of state variables.
 * \param x state variable vector.
 * \param nc number of coupling terms.
 * \param c coupling term vector.
 * \return 1 if the solver should continue, 0 to stop solver.
 */
typedef SK_DEFOUT((*sk_out));

typedef struct sk_out_file_data sk_out_file_data;

/**
 * Allocate memory for file output.
 */
sk_out_file_data *sk_out_file_alloc();

/**
 * Initialize file output from a file name.
 */
int sk_out_file_from_fname(sk_out_file_data *d, char *fname);

/**
 * Initialize file output from stdout or stderr.
 */
int sk_out_file_from_std(sk_out_file_data *d, FILE *std);

/**
 * Query whether file output is on stdout stderr.
 */
int sk_out_file_is_std(sk_out_file_data *d);

/**
 * Get file pointer.
 */
FILE *sk_out_file_get_fd(sk_out_file_data *d);

/**
 * Free memory allocated for file output.
 */
void sk_out_file_free(sk_out_file_data *d);

/**
 * Callback implementing file output.
 */
SK_DEFOUT(sk_out_file);

/* auto-allocating array */
typedef struct sk_out_mem_data sk_out_mem_data;

/**
 * Get number of state variables in memory buffer.
 */
int sk_out_mem_get_nx(sk_out_mem_data *d);

/**
 * Get number of coupling variables in memory buffer.
 */
int sk_out_mem_get_nc(sk_out_mem_data *d);

/**
 * Get number of samples in memory buffer.
 */
int sk_out_mem_get_n_sample(sk_out_mem_data *d);

/**
 * Get capacity in number of samples in memory buffer.
 */
int sk_out_mem_get_capacity(sk_out_mem_data *d);

/**
 * Get state variable buffer.
 */
double *sk_out_mem_get_xs(sk_out_mem_data *d);

/**
 * Get coupling variable buffer.
 */
double *sk_out_mem_get_cs(sk_out_mem_data *d);

/**
 * Allocate memory for output memory buffer.
 */
sk_out_mem_data *sk_out_mem_alloc();

/**
 * Initialize output memory buffer.
 */
int sk_out_mem_init(sk_out_mem_data *d);

/**
 * Free memory allocated to output memory buffer.
 */
void sk_out_mem_free(sk_out_mem_data *d);

/**
 * Callback implementing output memory buffer.
 */
SK_DEFOUT(sk_out_mem);

/* split n-ways */
typedef struct sk_out_tee_data sk_out_tee_data;

/**
 * Allocate output splitter.
 */
sk_out_tee_data *sk_out_tee_alloc();

/**
 * Initialize output splitter.
 *
 * \param d splitter instance
 * \param nout number of outputs to distribute to
 */
int sk_out_tee_init(sk_out_tee_data *d, int nout);

/**
 * Get number of outputs for splitter.
 */
int sk_out_tee_get_nout(sk_out_tee_data *d);

/**
 * Get NULL status of out data array.
 */
int sk_out_tee_outd_is_null();

/**
 * Get NULL status of out callback array.
 */
int sk_out_tee_outs_is_null();

/**
 * Set i'th output of splitter.
 *
 * \param d splitter instance
 * \param i output index
 * \param out i'th output callback
 * \param data i'th output user data
 */
int sk_out_tee_set_out(sk_out_tee_data *d, int i, sk_out out, void *data);

/**
 * Get i'th output callback.
 */
sk_out sk_out_tee_get_out_i(sk_out_tee_data *d, int i);

/**
 * Get i'th output user data.
 */
void *sk_out_tee_get_outd_i(sk_out_tee_data *d, int i);

/**
 * Free memory allocated to splitter output.
 */
void sk_out_tee_free(sk_out_tee_data *d);

/**
 * Callback implementing output splitter.
 */
SK_DEFOUT(sk_out_tee);

/* TODO general temporal filter */

/* temporal average */
typedef struct sk_out_tavg_data sk_out_tavg_data;

/**
 * Allocate memory for temporal average output.
 */
sk_out_tavg_data *sk_out_tavg_alloc();

/**
 * Initialize temporal average output.
 */
int sk_out_tavg_init(sk_out_tavg_data *d, int len, sk_out out, void *outd);

/**
 * Get len of temporal average output.
 */
int sk_out_tavg_get_len(sk_out_tavg_data *d);

/**
 * Get pos of temporal average output.
 */
int sk_out_tavg_get_pos(sk_out_tavg_data *d);

/**
 * Get t of temporal average output.
 */
double sk_out_tavg_get_t(sk_out_tavg_data *d);

/**
 * Get out of temporal average output.
 */
sk_out sk_out_tavg_get_out(sk_out_tavg_data *d);

/**
 * Get outd of temporal average output.
 */
void *sk_out_tavg_get_outd(sk_out_tavg_data *d);

/**
 * Get x of temporal average output.
 */
double *sk_out_tavg_get_x(sk_out_tavg_data *d);

/**
 * Get c of temporal average output.
 */
double *sk_out_tavg_get_c(sk_out_tavg_data *d);

/**
 * Free memory allocated to temporal average output.
 */
void sk_out_tavg_free(sk_out_tavg_data *d);

/**
 * Callback implementing temporal average output.
 */
SK_DEFOUT(sk_out_tavg);

/* spatial filter (bank) */
typedef struct sk_out_sfilt_data sk_out_sfilt_data;

/**
 * Allocate memory for spatial filter output.
 */
sk_out_sfilt_data *sk_out_sfilt_alloc();

/**
 * Initialize spatial filter output.
 */
int sk_out_sfilt_init(sk_out_sfilt_data *d, int nfilt, int filtlen, 
		double *xfilts, double *cfilts, sk_out out, void *outd);

/**
 * Get nfilt of spatial filter output.
 */
int sk_out_sfilt_get_nfilt(sk_out_sfilt_data *d);

/**
 * Get filtlen of spatial filter output.
 */
int sk_out_sfilt_get_filtlen(sk_out_sfilt_data *d);

/**
 * Get xfilts of spatial filter output.
 */
double *sk_out_sfilt_get_xfilts(sk_out_sfilt_data *d);

/**
 * Get cfilts of spatial filter output.
 */
double *sk_out_sfilt_get_cfilts(sk_out_sfilt_data *d);

/**
 * Get x of spatial filter output.
 */
double *sk_out_sfilt_get_x(sk_out_sfilt_data *d);

/**
 * Get c of spatial filter output.
 */
double *sk_out_sfilt_get_c(sk_out_sfilt_data *d);

/**
 * Get out of spatial filter output.
 */
sk_out sk_out_sfilt_get_out(sk_out_sfilt_data *d);

/**
 * Get outd of spatial filter output.
 */
void *sk_out_sfilt_get_outd(sk_out_sfilt_data *d);

/**
 * Free memory allocated to spatial filter output.
 */
void sk_out_sfilt_free(sk_out_sfilt_data *d);

/**
 * Callback implementing spatial filter monitor.
 */
SK_DEFOUT(sk_out_sfilt);

#ifdef __cplusplus
}; /* extern "C" */
#endif

#endif
