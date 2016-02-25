/* copyright 2016 Apache 2 sddekit authors */

/* private header for common scheme data & impl, for inclusion
 * in a scheme's implementation (.c) file.
 */

#include "sddekit.h"

struct sch_base
{
	struct sd_sch sch;
#define FIELD(type, name) type name;
#include "sch_base_fields.h"
#undef FIELD
};

/* make getters for each field */
#define FIELD(type, name) \
static type get_ ## name(struct sd_sch *sch) \
{ \
	struct sch_base *base = sch->ptr; \
	return base->name; \
}
#include "sch_base_fields.h"
#undef FIELD

/* Sets base fields + sch getters */
static inline void
sch_base_init(struct sch_base *base,
	uint32_t n_dim, uint32_t n_in, uint32_t n_out,
	double dt,
	struct sd_sys *sys,
	struct sd_hist *hist,
	struct sd_rng *rng)
{
	base->n_dim = n_dim;
	base->n_in = n_in;
	base->n_out = n_out;
	base->dt = dt;
	base->sys = sys;
	base->hist = hist;
	base->rng = rng;
	struct sd_sch *sch = &(base->sch);
	/* set getter function pointers */
#define FIELD(type, name) sch->get_ ## name = &get_ ## name;
#include "sch_base_fields.h"
#undef FIELD
}
