/* copyright 2016 Apache 2 sddekit authors */

#include "sddekit.h"

static int compare_int(const void *a, const void *b)
{
	if ( *(uint32_t*) a <  *(uint32_t*) b ) return -1;
	if ( *(uint32_t*) a == *(uint32_t*) b ) return  0;
	else /* a > b */ return  1;
}

sd_stat sd_util_uniqi(
	uint32_t n, 
	uint32_t * restrict ints, 
	uint32_t * restrict nuniq, 
	uint32_t ** uints)
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

sd_stat sd_util_read_square_matrix(const char *fname, uint32_t *n, double **w)
{
	uint32_t nn;
	FILE *fd;
	double _, *wi;
	/* open file */
	fd = fopen(fname, "r");
	if (fd==NULL) {
		sd_err("failed to open file");
		return SD_ERR;
	}
	/* count number of readable elements */
	nn = 0;
	{
		int count;
		while (1) {
			count = fscanf(fd, "%lg", &_);
			if (count < 1)
				break;
			nn++;
		}
	}
	rewind(fd);
	/* setup memory */
	*n = (uint32_t) sqrt(nn);
	wi = sd_malloc (sizeof(double)*nn);
	*w = wi;
	if (wi==NULL) {
		fclose(fd);
		return SD_ERR;
	}
	/* read data into memory this time */
	{
		int count;
		while (1) {
			count = fscanf(fd, "%lg", wi++);
			if (count < 1)
				break;
		}
	}
	fclose(fd);
	return SD_OK;
}
