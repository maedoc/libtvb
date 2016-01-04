/* copyright 2016 Apache 2 sddekit authors */

#include "wps.h"

_(rk_state, alloc,
	rk_state *rng;
	rng = sd_malloc(sizeof(rk_state));
	mexMakeMemoryPersistent(rng);
	pl[0] = mx_of_voidp(rng);
)

_(rk_state,  seed, rk_seed((int) mxGetScalar(pr[1]),voidp_of_mx(pr[0])); )
_(rk_state, gauss, pl[0] = mxCreateDoubleScalar(rk_gauss(voidp_of_mx(pr[0]))); )
_(rk_state,  free, sd_free(voidp_of_mx(pr[0])); )
