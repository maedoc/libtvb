/* copyright 2016 Apache 2 libtvb authors */

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
FIELD(double , time)
FIELD(double *, state)
FIELD(double *, input)
FIELD(double *, output)
FIELD(struct tvb_sys *, sys)
FIELD(struct tvb_hist *, hist)
FIELD(struct tvb_rng *, rng)
