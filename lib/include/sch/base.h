/* copyright 2016 Apache 2 sddekit authors */

/* private header for common scheme data & impl, for inclusion
 * in a scheme's implementation (.c) file.
 */

#include "../sddekit.h"

struct sch_base
{
	struct sd_sch sch;
#define FIELD(type, name) type name;
#include "sch/base_fields.h"
#undef FIELD
};

/* make getters for each field {{{ */
#define FIELD(type, name) \
static type get_ ## name(struct sd_sch *sch) \
{ \
	struct sch_base *base = sch->data; \
	return base->name; \
}
#include "sch/base_fields.h"
#undef FIELD
/* }}} */

/* obj common impl copy n byte, counts ONLY pointer n bytes {{{ */
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

static void
sch_base_pointers_copy(struct sch_base *base, struct sch_base *copy)
{
	memcpy(copy->state, base->state, sizeof(double) * copy->n_dim);
	memcpy(copy->input, base->input, sizeof(double) * copy->n_dim);
	memcpy(copy->output, base->output, sizeof(double) * copy->n_dim);
}

static void
sch_base_pointers_free(struct sch_base *base)
{
    sd_free(base->state);
    sd_free(base->input);
    sd_free(base->output);
}

/* }}} */

/* common set up for sys in out {{{ */
static inline struct sd_sys_in
sch_base_sys_in(struct sch_base *b, double time)
{
	struct sd_sys_in in = {
		.id=0, .n_dim=b->n_dim, .n_in=b->n_in, .n_out=b->n_out,
		.time=time, .state=b->state, .input=b->input,
		.hist=b->hist, .rng=b->rng
	};
	return in;
}

static inline struct sd_sys_out
sch_base_sys_out(struct sch_base *b, double *drift, double *diffusion)
{
	struct sd_sys_out out = {
		.drift=drift, .diffusion=diffusion,
		.output=b->output
	};
	return out;
}

static inline struct sd_out_sample
sch_base_sample(struct sch_base *b)
{
    struct sd_out_sample sample = {
        .time = b->time,
        .n_dim = b->n_dim,
        .n_out = b->n_out,
        .state = b->state,
        .output = b->output
    };
    return sample;
}


/* common init sets base fields + sch getters  {{{ */
static inline enum sd_stat
sch_base_init(struct sch_base *base,
	double time, double dt,
	uint32_t n_dim, uint32_t n_in, uint32_t n_out,
	struct sd_sys *sys,
	struct sd_hist *hist,
	struct sd_rng *rng,
	uint32_t (*n_byte)(struct sd_sch*),
	void (*free)(struct sd_sch*),
	struct sd_sch*(*copy)(struct sd_sch*),
	enum sd_stat(*apply)(struct sd_sch*),
    struct sd_out_sample(*sample)(struct sd_sch*)
)
{
	base->n_dim = n_dim;
	base->n_in = n_in;
	base->n_out = n_out;
	base->dt = dt;
	base->time = time;
    base->state = base->input = NULL;
    if ((base->state = sd_malloc(sizeof(double) * n_dim)) == NULL
     || (base->input = sd_malloc(sizeof(double) * n_in)) == NULL
     || (base->output = sd_malloc(sizeof(double) * n_out)) == NULL
    )
    {
        if (base->state) sd_free(base->state);
        if (base->input) sd_free(base->input);
        sd_err("alloc sch base failed.");
        return SD_OK;
    }
	base->sys = sys;
	base->hist = hist;
	base->rng = rng;
	struct sd_sch *sch = &(base->sch);
	/* set getter function pointers */
#define FIELD(type, name) sch->get_ ## name = &get_ ## name;
#include "sch/base_fields.h"
#undef FIELD
	sch->free = free;
	sch->n_byte = n_byte;
	sch->copy = copy;
	sch->apply = apply;
    sch->sample = sample;
    return SD_OK;
}