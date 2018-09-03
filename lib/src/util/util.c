/* copyright 2016 Apache 2 libtvb authors */

#include "libtvb.h"

#include <stdlib.h>

static int compare_int(const void *a, const void *b)
{
	if ( *(uint32_t*) a <  *(uint32_t*) b ) return -1;
	if ( *(uint32_t*) a == *(uint32_t*) b ) return  0;
	else /* a > b */ return  1;
}

enum tvb_stat tvb_util_uniqi(uint32_t n, uint32_t *ints, uint32_t *nuniq, uint32_t ** uints)
{ 
	uint32_t i, j, *ints_copy;

	if (n==0) return TVB_OK;

	if (n==1) {
		*nuniq = 1;
		if ((*uints = tvb_malloc (sizeof(uint32_t)))==NULL) {
			tvb_err("failed to allocate memory for unique integers");
			return TVB_ERR;
		}
		(*uints)[0] = ints[0];
		return TVB_OK;
	}

	/* sort copy of input vector */
	if ((ints_copy = tvb_malloc(sizeof(uint32_t) * n))==NULL) {
		tvb_err("failed to allocate memory for ints copy.");
		return TVB_ERR;
	}
	memcpy(ints_copy, ints, n*sizeof(uint32_t));

	qsort(ints_copy, n, sizeof(uint32_t), compare_int);

	/* count uniq */
	*nuniq = 1;
	for (i=0; i<(n-1); i++)
		if (ints_copy[i] != ints_copy[i+1])
			(*nuniq)++;

	if ((*uints = tvb_malloc (sizeof(uint32_t) * *nuniq))==NULL) {
		tvb_err("failed to allocate memory for unique integers.");
		tvb_free(ints_copy);
		return TVB_ERR;
	}

	/* copy unique into output array */
	j = 0;
	(*uints)[j++] = ints_copy[0];
	for (i=0; i<(n-1); i++)
		if (ints_copy[i] != ints_copy[i+1])
			(*uints)[j++] = ints_copy[i+1];

	tvb_free(ints_copy);
	
	return TVB_OK;
}
