/* copyright 2016 Apache 2 libtvb authors */

#include "libtvb.h"

/**
 * Random number generator (RNG) interface.
 *
 * TODO get/set full state as bytestring
 */
struct tvb_rng
{
	tvb_declare_common_members(tvb_rng);

	/*! Seed the RNG. */
	void (*seed)(struct tvb_rng*, uint32_t seed);

	/*! Generate a single sample from N(0, 1). */
	double (*norm)(struct tvb_rng*);

        /*! Generate a single sample on U(0, 1). */
        double (*uniform)(struct tvb_rng*);

	/*! Generate and fill an array with samples from N(0, 1). */
	void (*fill_norm)(struct tvb_rng*, uint32_t n, double *x);
};

/*! Construct a new Mersenne Twister RNG. */
TVB_API struct tvb_rng *
tvb_rng_new_mt(uint32_t seed);