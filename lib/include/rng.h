/* copyright 2016 Apache 2 sddekit authors */

#include "sddekit.h"

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