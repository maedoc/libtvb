/* copyright 2016 Apache 2 sddekit authors */

#include "sddekit.h"

static int compare_int(const void *a, const void *b)
{
	if ( *(uint32_t*) a <  *(uint32_t*) b ) return -1;
	if ( *(uint32_t*) a == *(uint32_t*) b ) return  0;
	else /* a > b */ return  1;
}

enum sd_stat sd_util_uniqi(uint32_t n, uint32_t *ints, uint32_t *nuniq, uint32_t ** uints)
{ 
	uint32_t i, j, *ints_copy;

	if (n==0) return SD_OK;

	if (n==1) {
		*nuniq = 1;
		if ((*uints = sd_malloc (sizeof(uint32_t)))==NULL) {
			sd_err("failed to allocate memory for unique integers");
			return SD_ERR;
		}
		(*uints)[0] = ints[0];
		return SD_OK;
	}

	/* sort copy of input vector */
	if ((ints_copy = sd_malloc(sizeof(uint32_t) * n))==NULL) {
		sd_err("failed to allocate memory for ints copy.");
		return SD_ERR;
	}
	memcpy(ints_copy, ints, n*sizeof(uint32_t));

	qsort(ints_copy, n, sizeof(uint32_t), compare_int);

	/* count uniq */
	*nuniq = 1;
	for (i=0; i<(n-1); i++)
		if (ints_copy[i] != ints_copy[i+1])
			(*nuniq)++;

	if ((*uints = sd_malloc (sizeof(uint32_t) * *nuniq))==NULL) {
		sd_err("failed to allocate memory for unique integers.");
		sd_free(ints_copy);
		return SD_ERR;
	}

	/* copy unique into output array */
	j = 0;
	(*uints)[j++] = ints_copy[0];
	for (i=0; i<(n-1); i++)
		if (ints_copy[i] != ints_copy[i+1])
			(*uints)[j++] = ints_copy[i+1];

	sd_free(ints_copy);
	
	return SD_OK;
}
