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

/* help with n byte, counts ONLY pointer n bytes */
static inline uint32_t
sch_base_pointers_n_byte(struct sch_base *base)
{
	uint32_t byte_count = 0;
	byte_count += base->sys->n_byte(base->sys);
	byte_count += base->hist->n_byte(base->hist);
	byte_count += base->rng->n_byte(base->rng);
	byte_count += sizeof(double) * (base->n_dim + base->n_in + base->n_out);
	return byte_count;
}


/* Sets base fields + sch getters */
static inline void
sch_base_init(struct sch_base *base,
	uint32_t n_dim, uint32_t n_in, uint32_t n_out,
	double dt,
	struct sd_sys *sys,
	struct sd_hist *hist,
	struct sd_rng *rng,
	uint32_t (*n_byte)(struct sd_sch*),
	void (*free)(struct sd_sch*),
	struct sd_sch*(*copy)(struct sd_sch*),
	enum sd_stat(*apply)(struct sd_sch*, double *, double *, double *)
)
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
	sch->free = free;
	sch->n_byte = n_byte;
	sch->copy = copy;
	sch->apply = apply;
}
