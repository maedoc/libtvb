/* copyright 2016 Apache 2 sddekit authors */

#include "../sddekit.h"

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

/* TODO initial conditions would more consistently specified through
 * the initial history function.
 */

/**
 * Create a new default solver instance.
 *
 * Initial time & state used to initialize the scheme's data.
 */
SD_API struct sd_sol *
sd_sol_new_default(double init_time, double *init_state,
		   struct sd_sch *scheme, struct sd_out *out);