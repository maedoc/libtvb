/* Apache 2.0 INS-AMU 2015 */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "sk_malloc.h"

int sk_dat_read_square_matrix(char *fname, int *n, double **w)
{
	int nn;
	FILE *fd;
	double _, *wi;
	/* open file */
	fd = fopen(fname, "r");
	if (fd==NULL) {
		fprintf(stderr, "[sk_dat_read_square_matrix] failed to open file"
				" `%s'.\n", fname);
		return 1;
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
	*n = (int) sqrt(nn);
	wi = sk_malloc (sizeof(double)*nn);
	*w = wi;
	if (wi==NULL) {
		fclose(fd);
		return 1;
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
	return 0;
}
