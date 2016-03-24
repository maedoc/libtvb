/* Random kit 1.3 */

/*
 * Copyright (c) 2003-2005, Jean-Sebastien Roy (js@jeannot.org)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

/* @(#) $Jeannot: randomkit.h,v 1.24 2005/07/21 22:14:09 js Exp $ */

/*
 * Typical use:
 *
 * {
 *  sd_rng_mt_state state;
 *  unsigned long seed = 1, random_value;
 *
 *  sd_rng_mt_seed(seed, &state); // Initialize the RNG
 *  ...
 *  random_value = sd_rng_mt_random(&state); // Generate random values in [0..RK_MAX]
 * }
 *
 * Instead of sd_rng_mt_seed, you can use sd_rng_mt_randomseed which will get a random seed
 * from /dev/urandom (or the clock, if /dev/urandom is unavailable):
 *
 * {
 *  sd_rng_mt_state state;
 *  unsigned long random_value;
 *
 *  sd_rng_mt_randomseed(&state); // Initialize the RNG with a random seed
 *  ...
 *  random_value = sd_rng_mt_random(&state); // Generate random values in [0..RK_MAX]
 * }
 */

/*
 * Useful macro:
 *  RK_DEV_RANDOM: the device used for random seeding.
 *                 defaults to "/dev/urandom"
 */

#include <stddef.h>

#ifndef _RANDOMKIT_
#define _RANDOMKIT_

#define RK_STATE_LEN 624

typedef struct sd_rng_mt_state_
{
    unsigned long key[RK_STATE_LEN];
    int pos;
    int has_gauss; /* !=0: gauss contains a gaussian deviate */
    double gauss;

    /* The sd_rng_mt_state structure has been extended to store the following
     * information for the binomial generator. If the input values of n or p
     * are different than nsave and psave, then the other parameters will be.
     * recomputed. RTK 2005-09-02 */

    int has_binomial; /* !=0: following parameters initialized for.
                              binomial */
    double psave;
    long nsave;
    double r;
    double q;
    double fm;
    long m;
    double p1;
    double xm;
    double xl;
    double xr;
    double c;
    double laml;
    double lamr;
    double p2;
    double p3;
    double p4;

}
sd_rng_mt_state;

typedef enum {
    RK_NOERR = 0, /* no error */
    RK_ENODEV = 1, /* no RK_DEV_RANDOM device */
    RK_ERR_MAX = 2
} sd_rng_mt_error;

/* error strings */
extern char *sd_rng_mt_strerror[RK_ERR_MAX];

/* Maximum generated random value */
#define RK_MAX 0xFFFFFFFFUL

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Initialize the RNG state using the given seed.
 */
extern void sd_rng_mt_seed(unsigned long seed, sd_rng_mt_state *state);

/*
 * Initialize the RNG state using a random seed.
 * Uses /dev/random or, when unavailable, the clock (see randomkit.c).
 * Returns RK_NOERR when no errors occurs.
 * Returns RK_ENODEV when the use of RK_DEV_RANDOM failed (for example because
 * there is no such device). In this case, the RNG was initialized using the
 * clock.
 */
extern sd_rng_mt_error sd_rng_mt_randomseed(sd_rng_mt_state *state);

/*
 * Returns a random unsigned long between 0 and RK_MAX inclusive
 */
extern unsigned long sd_rng_mt_random(sd_rng_mt_state *state);

/*
 * Returns a random long between 0 and LONG_MAX inclusive
 */
extern long sd_rng_mt_long(sd_rng_mt_state *state);

/*
 * Returns a random unsigned long between 0 and ULONG_MAX inclusive
 */
extern unsigned long sd_rng_mt_ulong(sd_rng_mt_state *state);

/*
 * Returns a random unsigned long between 0 and max inclusive.
 */
extern unsigned long sd_rng_mt_interval(unsigned long max, sd_rng_mt_state *state);

/**
 * Returns a random double between 0.0 and 1.0, 1.0 excluded.
 */
extern double sd_rng_mt_double(sd_rng_mt_state *state);

/*
 * fill the buffer with size random bytes
 */
extern void sd_rng_mt_fill(void *buffer, size_t size, sd_rng_mt_state *state);

/*
 * fill the buffer with randombytes from the random device
 * Returns RK_ENODEV if the device is unavailable, or RK_NOERR if it is
 * On Unix, if strong is defined, RK_DEV_RANDOM is used. If not, RK_DEV_URANDOM
 * is used instead. This parameter has no effect on Windows.
 * Warning: on most unixes RK_DEV_RANDOM will wait for enough entropy to answer
 * which can take a very long time on quiet systems.
 */
extern sd_rng_mt_error sd_rng_mt_devfill(void *buffer, size_t size, int strong);

/*
 * fill the buffer using sd_rng_mt_devfill if the random device is available and using
 * sd_rng_mt_fill if is is not
 * parameters have the same meaning as sd_rng_mt_fill and sd_rng_mt_devfill.
 * Returns RK_ENODEV if the device is unavailable, or RK_NOERR if it is
 */
extern sd_rng_mt_error sd_rng_mt_altfill(void *buffer, size_t size, int strong,
                            sd_rng_mt_state *state);

/**
 * return a random gaussian deviate with variance unity and zero mean.
 */
extern double sd_rng_mt_gauss(sd_rng_mt_state *state);

/**
 * fill a double buffer with gaussian numbers
 */
extern void sd_rng_mt_gauss_fill(sd_rng_mt_state *state, int nx, double *x);

#ifdef __cplusplus
}
#endif

#endif /* _RANDOMKIT_ */
