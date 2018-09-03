/* copyright 2016 Apache 2 libtvb authors */

#include "../libtvb.h"

/*! Data structure passed to an output apply function.
 *
 * \param time current time.
 * \param n_dim number of state variables.
 * \param n_out number of coupling terms.
 * \param state state variable vector.
 * \param output efferent / output vector.
 */
struct tvb_out_sample
{
	double time;
	uint32_t n_dim;
	uint32_t n_out;
	double *state;
	double *output;
};