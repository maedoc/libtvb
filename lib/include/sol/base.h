/* copyright 2016 Apache 2 libtvb authors */

#include "../libtvb.h"

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
struct tvb_sol
{
	tvb_declare_common_members(tvb_sol);

	/*! Get associated scheme object. */
	struct tvb_sch * (*get_scheme)(struct tvb_sol *sol);

	/*! Get associated out object */
	struct tvb_out * (*get_out)(struct tvb_sol *sol);

	/*! Continue stepping in time. */
	enum tvb_stat (*cont)(struct tvb_sol *sol);

	/*! Get current time in solution. */
	double (*get_time)(struct tvb_sol *sol);
};

/* TODO initial conditions would more consistently specified through
 * the initial history function.
 */

/**
 * Create a new default solver instance.
 *
 * Initial time & state used to initialize the scheme's data.
 */
TVB_API struct tvb_sol *
tvb_sol_new_default(double init_time, double *init_state,
		   struct tvb_sch *scheme, struct tvb_out *out);