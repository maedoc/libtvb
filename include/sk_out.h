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

/* could be stdout, err, FILE("foo") */
typedef struct {
	FILE *fd;
	int isstd;
} sk_out_file_data;

int sk_out_file_from_fname(sk_out_file_data *d, char *fname);

int sk_out_file_from_std(sk_out_file_data *d, FILE *std);

void sk_out_file_free(sk_out_file_data *d);

SK_DEFOUT(sk_out_file);

/* auto-allocating array */
typedef struct {
	int n_sample, capacity;
	double *xs, *cs;
} sk_out_mem_data;

int sk_out_mem_init(sk_out_mem_data *d);

void sk_out_mem_free(sk_out_mem_data *d);

SK_DEFOUT(sk_out_mem);

/* split n-ways */
typedef struct {
	int nout;
	sk_out *outs;
	void **outd;
} sk_out_tee_data;

int sk_out_tee_init(sk_out_tee_data *d, int nout);

int sk_out_tee_set_out(sk_out_tee_data *d, int i, sk_out out, void *data);

void sk_out_tee_free(sk_out_tee_data *d);

SK_DEFOUT(sk_out_tee);

/* TODO general temporal filter */

/* temporal average */
typedef struct {
	int pos, len;
	double *x, *c, t;
	sk_out out;
	void *outd;
} sk_out_tavg_data;

int sk_out_tavg_init(sk_out_tavg_data *d, int len, sk_out out, void *outd);

void sk_out_tavg_free(sk_out_tavg_data *d);

SK_DEFOUT(sk_out_tavg);

/* spatial filter (bank) */
typedef struct {
	int nfilt, filtlen;
	double *xfilts, *cfilts, *x, *c;
	sk_out out;
	void *outd;
} sk_out_sfilt_data;

int sk_out_sfilt_init(sk_out_sfilt_data *d, int nfilt, int filtlen, 
		double *xfilts, double *cfilts, sk_out out, void *outd);

void sk_out_sfilt_free(sk_out_sfilt_data *d);

SK_DEFOUT(sk_out_sfilt);


#ifdef __cplusplus
}; /* extern "C" */
#endif

#endif
