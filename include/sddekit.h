/* copyright 2016 Apache 2 sddekit authors */

/** \mainpage SDDEKit
 *
 * A library for stochastic delay differential equations implementing published
 * numerical schemes, utilities for constructing network models and handling
 * simulation results, as well as bindings for MATLAB, Python.  Our intent
 * is to make it possible to use and benchmark available schemes on your
 * favorite model, not invent new numerical schemes, so we have attempted to
 * follow published results, documenting caveats, assumptions etc. Care is taken to handle calculation of partial erivatives,
 * to enable higher order schemes, optimization
 * and inversion techniques.
 *
 * \section mp_s_intro Introduction
 *
 * \section mp_s_ex Example
 *
 * \section mp_s_conv Conventions
 *
 * \subsection mp_ss_retcode Return codes & values
 *
 * Three conventions are used when returning from function calls:
 *
 * - *_alloc functions return NULL iff the underlying memory allocation fails, otherwise a valid, non-NULL pointer is returned.
 * - output callbacks return 1 to continue simulation, or 0 to stop simulation
 * - all other functions return 0 to indicate success, 1 to indicate failure.
 *
 * When an error occurs, a description will have passed to the error handler before the call returns. By default, this will appear on stderr, but the user can install a custom handler in order to e.g. abort the process or continue in specific cases. Bindings translate errors to language specific construct such as an error in MATLAB or exception in Python.
 *
 * \section mp_s_ref References
 *
 *
 */

#ifndef SDDEKIT_H
#define SDDEKIT_H

#ifdef __cplusplus
extern "C" {
#endif

#include "sk_dat.h"
#include "sk_hist.h"
#include "sk_malloc.h"
#include "sk_net.h"
#include "sk_out.h"
#include "sk_scheme.h"
#include "sk_solv.h"
#include "sk_sparse.h"
#include "sk_sys.h"
#include "sk_test.h"
#include "sk_util.h"
#include "sk_test.h"
#include "sk_log.h"
#include "sk_err.h"

#ifdef __cplusplus
}; /* extern "C" */
#endif

#endif
