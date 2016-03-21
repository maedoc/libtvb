/* copyright 2016 Apache 2 sddekit authors */

#include "../sddekit.h"

/* TODO to be useful, sch_cb needs a callback which is passed all the
 * data required to perform a step, basically contents of sch_base.
 */

/*! Create new scheme based on user-provided data & callback. */
SD_API struct sd_sch *
sd_sch_new_cb(double time, double dt,
	struct sd_sys *sys, struct sd_hist *hist, struct sd_rng *rng,
	void *user_data,
	enum sd_stat (*user_apply)(void *user_data));

/*! Create instance of the identity scheme, for difference equations. */
SD_API struct sd_sch *
sd_sch_new_id(double time,
	struct sd_sys *sys, struct sd_hist *hist, struct sd_rng *rng);

/*! Create instance of Euler-Maruyama O(1) general purpose scheme. */
SD_API struct sd_sch *
sd_sch_new_em(double time, double dt,
	struct sd_sys *sys, struct sd_hist *hist, struct sd_rng *rng);

/* Create instance of Euler-Maruyama O(1), specialized for colored noise,
 * derived from Fox 1998. Only for use with systems driven by additive noise.
 *
 * \param lam damping factor determining color; cf Fox et al 98.
 */
SD_API struct sd_sch * 
sd_sch_new_emc(double time, double dt, double lam,
	struct sd_sys *sys, struct sd_hist *hist, struct sd_rng *rng);

/*! Create instance of Heun scheme, Manella 2002, additive noise. */
SD_API struct sd_sch *
sd_sch_new_heun(double time, double dt,
	struct sd_sys *sys, struct sd_hist *hist, struct sd_rng *rng);

/* TODO http://arxiv.org/pdf/1506.05708v1.pdf LL for mult noise  */

/* TODO Kuechler & Platen semi-implicit Milstein for SDDEs */