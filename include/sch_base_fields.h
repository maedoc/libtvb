/* copyright 2016 Apache 2 sddekit authors */

/* Defines the data fields in the sch_base structure, for
 * use in sch_base.h.
 */

#ifndef FIELD
#define FIELD(type, name)
#endif

FIELD(uint32_t , n_dim)
FIELD(uint32_t , n_in)
FIELD(uint32_t , n_out)
FIELD(double , dt)
FIELD(double *, state)
FIELD(double *, input)
FIELD(double *, output)
FIELD(struct sd_sys *, sys)
FIELD(struct sd_hist *, hist)
FIELD(struct sd_rng *, rng)
