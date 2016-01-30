/* copyright 2016 Apache 2 sddekit authors */

/* A reduced version of src/sddekit.h easier for MATLAB's
 * loadlibrary() to parse
 */

#include <stdbool.h>
#include <stdint.h>

#ifndef restrict
#define restrict
#endif

#ifndef SD_API
#define SD_API
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
	SD_STOP
} sd_stat;

typedef struct sd_rng sd_rng;

/**
 * Construct a new RNG from default implementation.
 */
SD_API sd_rng *
sd_rng_new_default();

SD_API void sd_rng_seed(sd_rng*, uint32_t seed);
SD_API double sd_rng_norm(sd_rng*);
SD_API void sd_rng_fill_norm(sd_rng*, uint32_t n, double *x);
SD_API uint32_t sd_rng_nbytes(sd_rng*);
SD_API void sd_rng_free(sd_rng*);