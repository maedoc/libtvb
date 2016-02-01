/* copyright 2016 Apache 2 sddekit authors */

#include "sddekit.h"

sd_stat sd_hfill_apply(sd_hfill*hf, uint32_t n, double * restrict t, uint32_t *indices,
		double * restrict buf)
{
		return hf->apply(hf, n, t, indices, buf);
}

void sd_hfill_free(sd_hfill*hf)
{
	hf->free(hf);
}
