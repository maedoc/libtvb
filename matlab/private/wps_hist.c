/* copyright 2016 Apache 2 sddekit authors */

#include <stdint.h>
#include "wps.h"

_(sd_hist, alloc,
	sd_hist *hist = sd_hist_alloc();
	mexMakeMemoryPersistent(hist);
	pl[0] = mx_of_voidp(hist);
 )

_(sd_hist, init, /* h, vi, vd, t0, dt */
	int stat, *vi_i;
	size_t i, nd;
    uint64_t *vi64;
    int *vi;
	if (nr != 5)
		sd_err("init requires 5 arguments (h, vi, vd, t0, dt)");
	nd = mxGetM(pr[1]);
    /* convert vi to plat-dep int */
    vi64 = mxGetData(pr[1]);
    vi = sd_malloc(sizeof(int) * nd);
	for (i=0; i<nd; i++)
		vi[i] = vi64[i] - 1;
    /* do init */
	stat = sd_hist_init(voidp_of_mx(pr[0]), nd, vi,
			mxGetPr(pr[2]), mxGetScalar(pr[3]), mxGetScalar(pr[4]));
	if (stat)
		sd_err("failed to initialize history.");
)

_(sd_hist, get_maxvi,
    pl[0] = mxCreateDoubleScalar(sd_hist_get_maxvi(voidp_of_mx(pr[0])) + 1);
 )
 
_(sd_hist, get_vi2i,
    int i;
    sd_hist *h = voidp_of_mx(pr[0]);
    i = mxGetScalar(pr[1]);
    if (i < 1 || i > sd_hist_get_nu(h))
        sd_err("index must be in range [1, nu].");
    pl[0] = mxCreateDoubleScalar(sd_hist_get_vi2i(h, i - 1) + 1);
 )
 
_(sd_hist, get_nu,
    pl[0] = mxCreateDoubleScalar(sd_hist_get_nu(voidp_of_mx(pr[0])));
 )
 
_(sd_hist, fill,
		{
			int stat;
			stat = sd_hist_fill(voidp_of_mx(pr[0]), 
					sd_hist_hfill_matlab, pr[1]);
			if (stat)
				sd_err("filling history failed.");
		}
 )
_(sd_hist, get,
		{
			sd_hist *h = voidp_of_mx(pr[0]);
			pl[0] = mxCreateDoubleMatrix(sd_hist_get_nd(h), 1, mxREAL);
			sd_hist_get(h, mxGetScalar(pr[1]), mxGetPr(pl[0]));
		}
 )
_(sd_hist, set,
		{
			sd_hist *h = voidp_of_mx(pr[0]);
			sd_hist_set(h, mxGetScalar(pr[1]), mxGetPr(pr[2]));
		}
 )


_(sd_hist, get_nd, 
    pl[0] = mxCreateDoubleScalar(sd_hist_get_nd(voidp_of_mx(pr[0])));)

_(sd_hist, get_t, 
    pl[0] = mxCreateDoubleScalar(sd_hist_get_t(voidp_of_mx(pr[0])));)

_(sd_hist, get_dt, 
    pl[0] = mxCreateDoubleScalar(sd_hist_get_dt(voidp_of_mx(pr[0])));)

#define retdi(f, ra) \
	pl[0] = mxCreateDoubleScalar(f(voidp_of_mx(pr[0]), mxGetScalar(pr[1]) - 1) + ra);

_(sd_hist, get_buf_lin,
	sd_hist *h = voidp_of_mx(pr[0]);
	int i = mxGetScalar(pr[1]);
	if (i < 1 || i > sd_hist_get_lim(h, sd_hist_get_nu(h)))
		sd_err("index must be in range [1, lim(nu)]");
	pl[0] = mxCreateDoubleScalar(sd_hist_get_buf_lin(h, i - 1));
)

_(sd_hist, get_lim,
	sd_hist *h = voidp_of_mx(pr[0]);
	int i = mxGetScalar(pr[1]);
	if (i < 1 || i > (sd_hist_get_nu(h) + 1))
		sd_err("index must be in range [1, nu+1]");
	pl[0] = mxCreateDoubleScalar(sd_hist_get_lim(h, i - 1) + 1);
)

_(sd_hist, get_len,
	sd_hist *h = voidp_of_mx(pr[0]);
	int i = mxGetScalar(pr[1]);
	if (i < 1 || i > sd_hist_get_nu(h))
		sd_err("index must be in range [1, nu]");
	pl[0] = mxCreateDoubleScalar(sd_hist_get_len(h, i - 1) + 1);
)

_(sd_hist, get_pos,
	sd_hist *h = voidp_of_mx(pr[0]);
	int i = mxGetScalar(pr[1]);
	if (i < 1 || i > sd_hist_get_nu(h))
		sd_err("index must be in range [1, nu]");
	pl[0] = mxCreateDoubleScalar(sd_hist_get_pos(h, i - 1) + 1);
)

_(sd_hist, get_uvi,
	sd_hist *h = voidp_of_mx(pr[0]);
	int i = mxGetScalar(pr[1]);
	if (i < 1 || i > sd_hist_get_nu(h))
		sd_err("index must be in range [1, nu]");
	pl[0] = mxCreateDoubleScalar(sd_hist_get_uvi(h, i - 1) + 1);
)

_(sd_hist, get_maxd,
	sd_hist *h = voidp_of_mx(pr[0]);
	int i = mxGetScalar(pr[1]);
	if (i < 1 || i > sd_hist_get_nu(h))
		sd_err("index must be in range [1, nu]");
	pl[0] = mxCreateDoubleScalar(sd_hist_get_maxd(h, i - 1));
)

_(sd_hist, get_vi,
	sd_hist *h = voidp_of_mx(pr[0]);
	int i = mxGetScalar(pr[1]);
	if (i < 1 || i > sd_hist_get_nd(h))
		sd_err("index must be in range [1, nd]");
	pl[0] = mxCreateDoubleScalar(sd_hist_get_vi(h, i - 1) + 1);
)

_(sd_hist, get_vd,
	sd_hist *h = voidp_of_mx(pr[0]);
	int i = mxGetScalar(pr[1]);
	if (i < 1 || i > sd_hist_get_nd(h))
		sd_err("index must be in range [1, nd]");
	pl[0] = mxCreateDoubleScalar(sd_hist_get_vd(h, i - 1));
)

_(sd_hist, free, sd_hist_free(voidp_of_mx(pr[0]));)
